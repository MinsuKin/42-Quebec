import {
  ConnectedSocket,
  MessageBody,
  OnGatewayConnection,
  OnGatewayDisconnect,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { GameRealtimeService } from './gameRealtime.service';
import {
  BallServedData,
  GAME_EVENTS,
  GameMonitorState,
  GameSession,
  GameUserType,
  PadMovedData,
} from './interfaces';
import { GameUser, JoinGameEvent } from './dto';
import { GameSessionService } from './game-session.service';
import { GameStateDataPacket } from './engine';
import { Logger } from '@nestjs/common';

@WebSocketGateway({ namespace: 'game' })
export class GameGateway implements OnGatewayConnection, OnGatewayDisconnect {
  @WebSocketServer() server: Server;
  private readonly logger = new Logger(GameGateway.name);

  constructor(
    private gameRealtimeService: GameRealtimeService,
    private gameSessionService: GameSessionService,
  ) {}

  async handleConnection(client: Socket, ...args: any[]) {
    try {
      const userId = client.handshake.query.userId;
      if (!userId) throw new Error('User ID is required');
      const token = client.handshake.auth.token;
      if (!token) throw new Error('Token is required');
      const id = Number(userId) ?? 0;
      // check if jwt token is valid and if user is assign that jwt token
      await this.gameSessionService.canConnect(token, id);
      this.logger.log(`Client connected to game socket: ${client.id}`);
    } catch (e) {
      client.emit('failedToConnect', e.message);
      client.disconnect(true);
      return;
    }
  }

  handleDisconnect(@ConnectedSocket() client: Socket): any {
    try {
      const gameSessions = this.gameRealtimeService.handleSocketDisconnection(
        client.id,
      );
      if (!gameSessions) return;
      for (const gameSession of gameSessions) {
        this.handleGameEvents(gameSession);
      }
      this.gameSessionService.cleanGameSessions();
    } catch (e) {
      console.log(e);
    }
  }

  @SubscribeMessage(GAME_EVENTS.JoinGame)
  async handleJoinGame(
    @MessageBody() joinData: JoinGameEvent,
    @ConnectedSocket() client: Socket,
  ): Promise<{ worked: boolean; roomId: number }> {
    if (joinData.userType === GameUserType.Player) {
      const gameSession = this.gameRealtimeService.clientPlayerConnected(
        joinData.roomId,
        joinData.user.userId,
        client.id,
        this,
      );
      const roomName = `${joinData.roomId}`;
      const rooms = Object.keys(client.rooms);
      if (!rooms.includes(roomName)) {
        client.join(roomName);
      }
      setTimeout(() => {
        this.handleGameEvents(gameSession);
      }, 35);
      return {
        worked: true,
        roomId: gameSession.gameId,
      };
    } else {
      const gameSession = await this.gameRealtimeService.clientViewerConnected(
        joinData,
        client.id,
      );
      const roomName = `${joinData.roomId}`;
      const rooms = Object.keys(client.rooms);
      if (!rooms.includes(roomName)) {
        client.join(roomName);
      }
      setTimeout(() => {
        this.handleGameEvents(gameSession);
      }, 35);
      return {
        worked: true,
        roomId: gameSession.gameId,
      };
    }
  }

  @SubscribeMessage(GAME_EVENTS.reloadPlayersList)
  async handleReloadPlayersList(
    @ConnectedSocket() client: Socket,
    @MessageBody() received: { roomId: number },
  ) {
    const { roomId } = received;
    const gameSession = this.gameSessionService.getGameSession(roomId);
    if (!gameSession) return;
    this.gameRealtimeService.reloadPlayersList(gameSession);
    this.handleGameEvents(gameSession);
  }

  @SubscribeMessage(GAME_EVENTS.reloadViewersList)
  async handleReloadViewersList(
    @ConnectedSocket() client: Socket,
    @MessageBody() received: { roomId: number },
  ) {
    const { roomId } = received;
    const gameSession = this.gameSessionService.getGameSession(roomId);
    if (!gameSession) return;
    this.gameRealtimeService.reloadViewersList(gameSession);
    this.handleGameEvents(gameSession);
  }

  @SubscribeMessage(GAME_EVENTS.GameStateChanged)
  async handleGameStateChanged(
    @ConnectedSocket() client: Socket,
    @MessageBody()
    received: {
      roomId: number;
      user: GameUser;
      gameState: GameMonitorState;
    },
  ) {
    const { roomId, gameState, user } = received;
    const gameSession = this.gameSessionService.getGameSession(roomId);
    if (!gameSession) return;
    this.gameRealtimeService.handleClientGameStateChanged(
      gameSession,
      user.userId,
      gameState,
    );
    this.handleGameEvents(gameSession);
  }

  @SubscribeMessage(GAME_EVENTS.PadMoved)
  async handlePadMoved(
    @ConnectedSocket() client: Socket,
    @MessageBody()
    received: {
      roomId: number;
      data: PadMovedData;
    },
  ) {
    const { roomId, data } = received;
    const gameSession = this.gameSessionService.getGameSession(roomId);
    if (!gameSession) return;
    this.gameRealtimeService.handlePadMoved(gameSession, data);
    this.handleGameEvents(gameSession);
  }

  @SubscribeMessage(GAME_EVENTS.BallServed)
  async handleBallServed(
    @ConnectedSocket() client: Socket,
    @MessageBody()
    received: {
      roomId: number;
      data: BallServedData;
    },
  ) {
    const { roomId, data } = received;
    const gameSession = this.gameSessionService.getGameSession(roomId);
    if (!gameSession) return;
    this.gameRealtimeService.handleBallServed(gameSession, data);
    this.handleGameEvents(gameSession);
  }

  private handleGameEvents(gameSession: GameSession) {
    if (!gameSession) return;
    const roomName = `${gameSession.gameId}`;
    gameSession.eventsToPublishInRoom.forEach((eventObj) => {
      const { event, data } = eventObj;
      this.server.to(roomName).emit(event, data);
    });
    gameSession.eventsToPublishInRoom.splice(
      0,
      gameSession.eventsToPublishInRoom.length,
    );
  }

  public sendGameObjectState(data: GameStateDataPacket, roomId: number) {
    const roomName = `${roomId}`;
    this.server.to(roomName).emit(GAME_EVENTS.GameObjectState, {
      roomId,
      data,
    });
  }

  public sendScored(
    roomId: number,
    scores: Array<{ userId: number; score: number }>,
  ) {
    const roomName = `${roomId}`;
    this.server.to(roomName).emit(GAME_EVENTS.ScoreChanged, {
      roomId,
      data: scores,
    });
    const gameSession = this.gameSessionService.getGameSession(roomId);
    this.handleGameEvents(gameSession);
  }

  public sendBallPaddleCollision(paddleUserId: number, roomId: number) {
    const roomName = `${roomId}`;
    this.server.to(roomName).emit(GAME_EVENTS.BallPaddleCollision, {
      roomId,
      data: paddleUserId,
    });
    const gameSession = this.gameSessionService.getGameSession(roomId);
    this.handleGameEvents(gameSession);
  }
}
