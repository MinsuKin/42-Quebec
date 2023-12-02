import { Logger } from '@nestjs/common';
import {
  WebSocketGateway,
  WebSocketServer,
  OnGatewayConnection,
  OnGatewayDisconnect,
  ConnectedSocket,
  MessageBody,
  SubscribeMessage,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import {
  ServerToClientEvents,
  ClientToServerEvents,
} from './interfaces/chat.interface';
import { ChatService } from './chat.service';
import { MessageService } from './message.service';

@WebSocketGateway({ namespace: 'chat' })
export class ChatGateway implements OnGatewayConnection, OnGatewayDisconnect {
  @WebSocketServer() server: Server = new Server<
    ServerToClientEvents,
    ClientToServerEvents
  >();
  private readonly logger = new Logger(ChatGateway.name);

  constructor(
    private chatService: ChatService,
    private privateMessageService: MessageService,
  ) {}

  async handleConnection(client: Socket, ...args: any[]) {
    try {
      const userId = client.handshake.query.userId;
      if (!userId) throw new Error('User ID is required');
      const token = client.handshake.auth.token;
      if (!token) throw new Error('Token is required');
      const id = Number(userId) ?? 0;
      // check if jwt token is valid and if user is assign that jwt token
      await this.chatService.canConnect(token, id);
      this.logger.log(
        `Client connected on chat: ${client.id} and with token ${token}`,
      );
    } catch (e) {
      client.emit('failedToConnect', e.message);
      client.disconnect(true);
      return;
    }
  }

  async handleDisconnect(client: Socket): Promise<void> {
    // empty
  }

  @SubscribeMessage('joinRoom')
  async handleJoinRoom(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: { roomId: number; userId: number },
  ): Promise<void> {
    try {
      const { roomId, userId } = data;
      // check if client has already joined the room
      const rooms = Object.keys(client.rooms);
      if (!rooms.includes(`chat-room:${roomId}`)) {
        await this.chatService.canListenToRoom(userId, roomId);
        client.join(`chat-room:${roomId}`);
      }
    } catch (e) {
      client.emit('failedToJoinRoom', e.message);
    }
  }

  @SubscribeMessage('joinMyRoom')
  async handleJoinMyRoom(@ConnectedSocket() client: Socket): Promise<void> {
    try {
      const userId = client.handshake.query.userId;
      if (!userId) return;
      const rooms = Object.keys(client.rooms);
      if (!rooms.includes(`mp:${userId}`)) {
        client.join(`mp:${userId}`);
      }
    } catch (e) {
      client.emit('failedToJoinMyRoom', e.message);
    }
  }

  // Handle sending chat message
  @SubscribeMessage('sendMessage')
  async handleMessage(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: { senderId: number; roomId: number; content: string },
  ): Promise<void> {
    const { roomId, content, senderId } = data;
    try {
      const message = await this.chatService.sendMessageToRoom(
        roomId,
        content,
        senderId,
      );
      this.server.to(`chat-room:${roomId}`).emit('newMessage', message);
    } catch (e) {
      this.server
        .to(`chat-room:${roomId}`)
        .emit('failedToSendMessage', e.message);
    }
  }

  // Handle sending user is typing a message
  @SubscribeMessage('userIsTypingInRoom')
  async handleUserIsTypingInRoom(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: { senderId: number; roomId: number; username: string },
  ): Promise<void> {
    const { roomId, senderId, username } = data;
    try {
      client.broadcast
        .to(`chat-room:${roomId}`)
        .emit('receivedUserIsTypingInRoom', {
          senderId,
          roomId,
          username,
        });
    } catch (e) {
      this.server
        .to(`chat-room:${roomId}`)
        .emit('failedToSendMessage', e.message);
    }
  }

  // Handle sending a call to reload room members and roles
  @SubscribeMessage('reloadRoomMembers')
  async handleReloadRoomMembers(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: { roomId: number },
  ): Promise<void> {
    const { roomId } = data;
    try {
      this.server.to(`chat-room:${roomId}`).emit('reloadRoomMembers', roomId);
    } catch (e) {
      this.server
        .to(`chat-room:${roomId}`)
        .emit('failedToSendMessage', e.message);
    }
  }

  // handle sending private message
  @SubscribeMessage('sendPrivateMessage')
  async handlePrivateMessage(
    @ConnectedSocket() client: Socket,
    @MessageBody()
    data: { senderId: number; receiverId: number; content: string },
  ): Promise<{
    id: number;
    text: string;
    senderId: number;
    receiverId: number;
    timestamp: Date;
  }> {
    const { senderId, receiverId, content } = data;
    try {
      const message = await this.privateMessageService.createPrivateMessage(
        { content, receiverId },
        senderId,
      );
      this.server.to(`mp:${receiverId}`).emit('newMP', message);
      return message;
    } catch (e) {
      this.server.to(`mp:${senderId}`).emit('failedToSendMessage', e.message);
    }
  }

  // handle sending user is typing a private message
  @SubscribeMessage('mpUserIsTyping')
  async handleUserIsTyping(
    @ConnectedSocket() client: Socket,
    @MessageBody()
    data: { senderId: number; receiverId: number },
  ): Promise<void> {
    const { senderId, receiverId } = data;
    try {
      client.broadcast
        .to(`mp:${receiverId}`)
        .emit('receivedUserIsTyping', senderId);
    } catch (e) {
      this.server.to(`mp:${senderId}`).emit('failedToSendMessage', e.message);
    }
  }

  // Handle sending a call to reload room members and roles
  @SubscribeMessage('reloadMpConversation')
  async handleRefreshConversation(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: { senderId: number; receiverId: number },
  ): Promise<void> {
    const { senderId, receiverId } = data;
    try {
      client.broadcast.to(`mp:${receiverId}`).emit('reloadMp', senderId);
    } catch (e) {
      this.server.to(`mp:${senderId}`).emit('failedToSendMessage', e.message);
    }
  }
}
