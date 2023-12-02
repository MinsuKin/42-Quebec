import {
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
  OnGatewayConnection,
  OnGatewayDisconnect,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { User, Notification as NotificationT } from '@prisma/client';
import { RealTimeNotification } from './notification.service';
import { Logger, UnauthorizedException } from '@nestjs/common';
import { JwtPayload } from '../auth/auth.service';
import { JwtService } from '@nestjs/jwt';

@WebSocketGateway({ namespace: 'notification' })
export class NotificationGateway
  implements OnGatewayConnection, OnGatewayDisconnect
{
  private readonly logger = new Logger(NotificationGateway.name);
  @WebSocketServer() server: Server;

  constructor(private jwtService: JwtService) {}

  async canConnect(token: string, userId: number): Promise<boolean> {
    try {
      const isValid = this.jwtService.verify(token) as JwtPayload;
      if (!isValid) {
        throw new UnauthorizedException('Invalid credentials');
      }
      // check if the user is the same as the one in the token
      if (isValid.sub.userId !== userId) {
        throw new UnauthorizedException('Invalid credentials');
      }
      return true;
    } catch (e) {
      return false;
    }
  }

  async handleConnection(client: Socket, ...args: any[]) {
    try {
      const userId = client.handshake.query.userId;
      if (!userId) throw new Error('User ID is required');
      const token = client.handshake.auth.token;
      if (!token) throw new Error('Token is required');
      const id = Number(userId) ?? 0;
      // check if jwt token is valid and if user is assign that jwt token
      await this.canConnect(token, id);
      this.logger.log(`Client connected on notification: ${client.id}`);
    } catch (e) {
      client.emit('failedToConnect', e.message);
      client.disconnect(true);
      return;
    }
  }

  handleDisconnect(client: Socket) {
    this.logger.log(`Client disconnected of notification: ${client.id}`);
  }

  @SubscribeMessage('join')
  handleJoin(client: Socket, userId: number) {
    const room = `notification:${userId}`;
    // check if client has already joined the room
    const rooms = Object.keys(client.rooms);
    if (!rooms.includes(room)) client.join(room);
  }

  @SubscribeMessage('join-room')
  handleJoinRoom(client: Socket, roomId: number) {
    const room = `room-notification:${roomId}`;
    // check if client has already joined the room
    const rooms = Object.keys(client.rooms);
    if (!rooms.includes(room)) client.join(room);
  }

  @SubscribeMessage('leave-room')
  handleLeaveRoom(client: Socket, roomId: number) {
    const room = `room-notification:${roomId}`;
    // check if client has already joined the room
    const rooms = Object.keys(client.rooms);
    if (rooms.includes(room)) client.leave(room);
  }

  sendNotificationToUser(userId: User[`id`], data: NotificationT) {
    const room = `notification:${userId}`;
    this.server.to(room).emit('notification', data);
  }

  sendRealTimeNotificationToUser(
    userId: User[`id`],
    notification: RealTimeNotification,
  ) {
    const room = `notification:${userId}`;
    this.server.to(room).emit('realtime-notification', notification);
  }

  sendGeneralRealTimeNotification(notification: RealTimeNotification) {
    this.server.emit('realtime-notification', notification);
  }

  sendRealTimeNotificationToRoomMembers(
    roomId: number,
    notification: RealTimeNotification,
  ) {
    const room = `room-notification:${roomId}`;
    this.server.to(room).emit('realtime-notification', notification);
  }
}
