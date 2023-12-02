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
import { Status } from '@prisma/client';
import { Logger } from '@nestjs/common';
import { UsersService } from '../users/users.service';
import { AuthService } from './auth.service';

interface ServerToClientEvents {
  statusUpdate: (e: { userId: number; status: Status }) => void;
}

// Interface for when clients emit events to the server.
interface ClientToServerEvents {
  updateStatus: (e: { userId: number; status: Status }) => void;
}
@WebSocketGateway({ namespace: 'auth' })
export class StatusGateway implements OnGatewayConnection, OnGatewayDisconnect {
  @WebSocketServer() server: Server = new Server<
    ServerToClientEvents,
    ClientToServerEvents
  >();
  private logger = new Logger('StatusGateway');
  constructor(
    private usersService: UsersService,
    private authService: AuthService,
  ) {}
  async handleConnection(client: Socket, ...args: any[]) {
    try {
      const userId = client.handshake.query.userId;
      if (!userId) throw new Error('User ID is required');
      const id = Number(userId);
      const token = client.handshake.auth.token;
      if (!token) throw new Error('Token is required');
      this.authService.canListenStatus(token, id);
      await this.usersService.changeStatus(id, Status.Online);
      this.server.emit('statusUpdate', {
        userId: id,
        status: Status.Online,
      });
    } catch (e) {
      client.disconnect();
    }
  }

  async handleDisconnect(client: Socket): Promise<void> {
    try {
      const userId = client.handshake.query.userId;
      if (userId) {
        const id = Number(userId);
        await this.usersService.changeStatus(id, Status.Offline);
        this.server.emit('statusUpdate', {
          userId: id,
          status: Status.Offline,
        });
      }
    } catch (e) {
      this.logger.error(`Failed to handle disconnect: ${e.message}`);
    }
  }

  @SubscribeMessage('updateStatus')
  async handleUpdateStatus(
    @ConnectedSocket() client: Socket,
    @MessageBody() newStatus: Status,
  ): Promise<void> {
    try {
      const userId = client.handshake.query.userId;
      if (!userId) return;
      const id = Number(userId);
      await this.usersService.changeStatus(id, newStatus);
      this.server.emit('statusUpdate', {
        userId: id,
        status: newStatus,
      });
    } catch (e) {
      this.logger.error(`Failed to handle updateStatus: ${e.message}`);
    }
  }
}
