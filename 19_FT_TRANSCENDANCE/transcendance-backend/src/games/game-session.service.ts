import {
  BadRequestException,
  Injectable,
  Logger,
  NotFoundException,
  UnauthorizedException,
} from '@nestjs/common';
import {
  GAME_EVENTS,
  GameMonitorState,
  Gamer,
  GameRules,
  GameSession,
  GameSessionType,
  WaitingGameSession,
} from './interfaces';
import { CreateGameSessionDto } from './dto';
import { Game, GameEvent, GameHistory } from '@prisma/client';
import { GamesService } from './games.service';
import { NotificationService } from '../notifications/notification.service';
import { UsersService, UserWithData } from '../users/users.service';
import { JwtService } from '@nestjs/jwt';
import { JwtPayload } from '../auth/auth.service';

export interface GameSessionShort
  extends Omit<
    GameSession,
    'score' | 'monitors' | 'eventsToPublishInRoom' | 'gameEngine'
  > {
  participants: Gamer[];
  observers: Gamer[];
}
function selectSessionDataForFrontend(
  gameSession: GameSession,
): GameSessionShort {
  return {
    gameId: gameSession.gameId,
    hostId: gameSession.hostId,
    type: gameSession.type,
    state: gameSession.state,
    participants: gameSession.participants.slice(),
    observers: gameSession.observers.slice(),
    rules: gameSession.rules,
  };
}

export interface GameSessionQResponse {
  matchFound: boolean;
  waitingSession?: WaitingGameSession;
  gameSession?: GameSessionShort;
}

@Injectable()
export class GameSessionService {
  private gameSessions: Map<number, GameSession> = new Map();
  private waitingRoomGame: WaitingGameSession | undefined = undefined;
  private waitingChallenge: Map<number, WaitingGameSession> = new Map();
  private readonly logger = new Logger(GameSessionService.name);

  constructor(
    private gameService: GamesService,
    private userRepository: UsersService,
    private notificationService: NotificationService,
    private jwtService: JwtService,
  ) {}

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

  // HTTP REQUESTS METHODS SERVICE FUNCTIONS
  async startGameSessionAgainstBot(
    data: CreateGameSessionDto,
    host: UserWithData,
  ): Promise<GameSessionShort> {
    const hostGamer = this.createGamer(
      host.id,
      host.username,
      host.profile.avatar ?? '',
      '',
      true,
    );
    const participants = [
      hostGamer,
      this.createGamer(0, 'Ai Bot', '/pong/ia_avatar.jpg', '', false),
    ];
    this.setAllUnfinishedGameSessionsToEnded(
      hostGamer.userId,
      GameSessionType.Bot,
    );
    return this.createGameSession(participants, GameSessionType.Bot);
  }

  async prepareOpponentGame(
    data: CreateGameSessionDto,
    host: UserWithData,
  ): Promise<WaitingGameSession> {
    if (!data.opponent) throw new NotFoundException('Adversaire non trouvé');
    const hostGamer = this.createGamer(
      host.id,
      host.username,
      host.profile.avatar ?? '',
      '',
      true,
    );
    const opponentUser = await this.userRepository.getUser({
      id: data.opponent,
    });
    if (!opponentUser) throw new NotFoundException('Adversaire non trouvé');
    const opponent = this.createGamer(
      opponentUser.id,
      opponentUser.username,
      opponentUser.profile.avatar ?? '',
      '',
      false,
    );
    const participants = [hostGamer, opponent];
    // get the biggest ids in keys of WaitingGameSession and use it to build id
    const waitingListIds = Array.from(this.waitingChallenge.keys());
    const r = Math.floor(Math.random() * 3);
    const id = waitingListIds.length > 0 ? Math.max(...waitingListIds) + r : 1;
    const waitingGameSession: WaitingGameSession = {
      waitingGameId: id,
      hostId: hostGamer.userId,
      type: GameSessionType.PrivateGame,
      participants: participants,
      rules: data.rules ?? { maxScore: 5, maxTime: 300 },
    };
    this.waitingChallenge.set(id, waitingGameSession);
    await this.notificationService.sendGameInvitation(
      host.username,
      opponentUser.id,
      id,
    );
    return waitingGameSession;
  }

  async prepareQueListGame(actor: UserWithData): Promise<GameSessionQResponse> {
    // check if the user has an unfinished game session
    if (this.hasUnfinishedGameSession(actor.id)) {
      // set all unfinished game sessions to ended
      this.setAllUnfinishedGameSessionsToEnded(actor.id);
    }
    const gamer = this.createGamer(
      actor.id,
      actor.username,
      actor.profile.avatar ?? '',
      '',
      true,
    );
    // check someone is not already waiting in the waiting room
    if (this.waitingRoomGame) {
      // check if one game session is already waiting for an opponent
      if (this.waitingRoomGame.hostId === actor.id) {
        return { matchFound: false, waitingSession: this.waitingRoomGame };
      } else {
        // create a new game session with the host and the new player
        gamer.isHost = false;
        const participants = [gamer, this.waitingRoomGame.participants[0]];
        // set all their games as ended
        participants.forEach((p) => {
          this.setAllUnfinishedGameSessionsToEnded(p.userId);
        });
        // remove the waiting game session
        this.waitingRoomGame = undefined;
        const gameSession = await this.createGameSession(
          participants,
          GameSessionType.QueListGame,
        );
        return { matchFound: true, gameSession };
      }
    } else {
      // create a new game session with the host
      const waitingListIds = Array.from(this.waitingChallenge.keys());
      const id =
        waitingListIds.length > 0 ? Math.max(...waitingListIds) + 1 : 1;
      this.waitingRoomGame = {
        waitingGameId: id,
        hostId: gamer.userId,
        type: GameSessionType.PrivateGame,
        participants: [gamer],
        rules: { maxScore: 5, maxTime: 300 },
      };
      this.notificationService.sendNewPlayerInQue(actor.id, actor.username);
      return { matchFound: false, waitingSession: this.waitingRoomGame };
    }
  }

  async acceptGameChallengeInvite(
    waitingGameId: number,
    actor: UserWithData,
  ): Promise<GameSessionShort> {
    const waitingGameSession = this.waitingChallenge.get(waitingGameId);
    if (!waitingGameSession) {
      throw new NotFoundException('Challenge not found');
    }
    // check if actor is a participant of the challenge
    const actorIsParticipant = waitingGameSession.participants.some(
      (p) => p.userId === actor.id,
    );
    if (!actorIsParticipant) {
      throw new BadRequestException(
        `Vous n'êtes pas un participant du challenge`,
      );
    }
    // check there is no participant already in a game session
    waitingGameSession.participants.forEach((p) => {
      if (this.hasUnfinishedGameSession(p.userId)) {
        throw new BadRequestException(
          `Un des participants est déjà dans une partie`,
        );
      }
    });
    // check if no one is a waiting player in the waiting room
    waitingGameSession.participants.forEach((p) => {
      if (this.waitingRoomGame?.hostId === p.userId) {
        throw new BadRequestException(
          `Un des participants est déjà dans une file d'attente`,
        );
      }
    });
    // set all unfinished game sessions to ended
    waitingGameSession.participants.forEach((p) => {
      this.setAllUnfinishedGameSessionsToEnded(p.userId);
    });
    // create a new game session with the host and the new player
    const participants = waitingGameSession.participants;
    waitingGameSession.played = true;
    return this.createGameSession(
      participants,
      GameSessionType.PrivateGame,
      waitingGameSession.rules,
    );
  }

  async rejectGameChallengeInvite(
    waitingGameId: number,
    actor: UserWithData,
  ): Promise<void> {
    const waitingGameSession = this.waitingChallenge.get(waitingGameId);
    if (!waitingGameSession) {
      throw new NotFoundException('Challenge not found');
    }
    // check if actor is a participant of the challenge
    const actorIsParticipant = waitingGameSession.participants.some(
      (p) => p.userId === actor.id,
    );
    if (!actorIsParticipant) {
      throw new BadRequestException(
        `Vous n'êtes pas un participant du challenge`,
      );
    }
    // remove the challenge from the waiting list
    this.waitingChallenge.delete(waitingGameId);
    // notify the host
    const host = waitingGameSession.participants.find((p) => p.isHost);
    if (host) {
      await this.notificationService.sendGameInvitationRejected(
        actor.username,
        host.userId,
        waitingGameId,
      );
    }
  }

  // allow a user to check if a waiting game session exists
  isValidChallenge(waitingGameId: number): { valid: boolean; played: boolean } {
    const waitingGameSession = this.waitingChallenge.get(waitingGameId);
    if (!waitingGameSession) {
      return { valid: false, played: false };
    }
    return { valid: true, played: waitingGameSession.played ?? false };
  }

  async quitWaitingRoom(actor: UserWithData): Promise<string> {
    if (this.waitingRoomGame) {
      if (this.waitingRoomGame.hostId === actor.id) {
        this.waitingRoomGame = undefined;
        this.notificationService.sendPlayerLeftQue(actor.id, actor.username);
      } else {
        return 'ok';
      }
    } else {
      return 'ok';
    }
  }

  gameSessionState(gameId: number): GameMonitorState {
    const gameSession = this.gameSessions.get(gameId);
    if (!gameSession) {
      throw new NotFoundException('Game session not found');
    }
    return gameSession.state;
  }

  // fetch user info of participants in the waiting room
  async showWaitingRoom() {
    const waitingRoomGame = this.waitingRoomGame;
    if (!waitingRoomGame) {
      return [];
    }
    const participantPromises = waitingRoomGame.participants.map((p) =>
      this.userRepository.getUser({ id: p.userId }),
    );
    const participants = await Promise.all(participantPromises);
    return participants.map((p) => ({
      userId: p.id,
      username: p.username,
      avatar: p.profile.avatar ?? '',
    }));
  }

  async addViewerToGameSessionHttp(
    gameId: number,
    viewer: UserWithData,
  ): Promise<GameSessionShort> {
    const gameSession = this.gameSessions.get(gameId);
    if (!gameSession) {
      throw new NotFoundException(
        `La session de jeu n'existe pas, ou le jeu est terminé`,
      );
    }
    // check if game session is ended
    if (gameSession.state === GameMonitorState.Ended) {
      throw new NotFoundException('La session de jeu est terminée');
    }
    const viewerGamer = this.createGamer(
      viewer.id,
      viewer.username,
      viewer.profile.avatar ?? '',
      '',
      false,
    );
    if (this.checkIfUserIsAnObserver(gameSession, viewer.id)) return;
    gameSession.observers.push(viewerGamer);
    // send to all participant that someone joined the game
    gameSession.participants.forEach((p) => {
      this.notificationService.sendJoinedGame(
        p.userId,
        viewerGamer.username,
        gameSession.gameId,
      );
    });
    return selectSessionDataForFrontend(gameSession);
  }

  async addViewerDataFromSocket(
    gameId: number,
    viewer: { userId: number; username: string; clientId: string },
  ): Promise<GameSession> {
    const gameSession = this.gameSessions.get(gameId);
    if (!gameSession) {
      throw new Error('Game session not found');
    }
    const viewerIndex = gameSession.observers.findIndex(
      (p) => p.userId === viewer.userId,
    );
    if (viewerIndex !== -1) {
      gameSession.observers[viewerIndex].clientId = viewer.clientId;
    }
    return gameSession;
  }

  async getUserGameSessions(
    userId: number,
  ): Promise<GameSessionShort[] | string> {
    const gameSessions: GameSessionShort[] = [];
    this.gameSessions.forEach((gameSession) => {
      if (
        this.checkIfUserIsAPlayer(gameSession, userId) &&
        gameSession.state !== GameMonitorState.Ended
      ) {
        gameSessions.push(selectSessionDataForFrontend(gameSession));
      }
    });
    if (gameSessions.length === 0) {
      return 'No game session found, for this user';
    }
    return gameSessions;
  }

  isSomeoneWaitingForAnOpponent(): boolean {
    return this.waitingRoomGame !== undefined;
  }

  getUserGameStatus(userId: number): {
    status: 'playing' | 'inQueue' | 'free';
    gameSession?: GameSessionShort;
  } {
    const hasUnfinishedGameSession = this.hasUnfinishedGameSession(userId);
    if (hasUnfinishedGameSession) {
      const ids = this.getNotEndedGameSessionsIds(userId);
      const gameSession = this.gameSessions.get(ids[ids.length - 1]);
      if (gameSession) {
        return {
          status: 'playing',
          gameSession: selectSessionDataForFrontend(gameSession),
        };
      }
    } else if (this.waitingRoomGame?.hostId === userId) {
      return { status: 'inQueue' };
    }
    return { status: 'free' };
  }

  getUserGameStatusForMany(userIds: number[]): {
    status: 'playing' | 'inQueue' | 'free';
    gameSession?: GameSessionShort;
  }[] {
    return userIds.map((userId) => this.getUserGameStatus(userId));
  }

  async quitGameSession(gameId: number, userId: number): Promise<string> {
    const gameSession = this.gameSessions.get(gameId);
    if (!gameSession) return 'No game session found, with this id';
    if (gameSession.state === GameMonitorState.Ended) {
      this.cleanGameSessions();
      return 'Game Ended';
    }
    const gamer = gameSession.participants.find((p) => p.userId === userId);
    if (!gamer) return 'No game session found, with this id';
    gameSession.eventsToPublishInRoom.push({
      event: GAME_EVENTS.GameMonitorStateChanged,
      data: { roomId: gameId, data: GameMonitorState.Ended },
    });
    gameSession.state = GameMonitorState.Ended;
    this.logger.log(
      `Quit Game - stopping engine loop, and destroying engine for session: ${gameSession.gameId}`,
    );
    gameSession.gameEngine?.stopLoop();
    this.cleanGameSessions();
    return 'Game session ended';
  }

  // Utils for http request methods
  async createGameSession(
    participants: Gamer[],
    type: GameSessionType,
    rules: GameRules = { maxScore: 5, maxTime: 300 },
  ): Promise<GameSessionShort> {
    const monitors = Array<GameMonitorState>(participants.length).fill(
      GameMonitorState.Waiting,
    );
    const participantsIds = participants
      .map((p) => p.userId)
      .filter((id) => id !== 0); // remove the bot id
    const game = await this.createAGame(participantsIds, type);
    // fill the score map with 0 for each participant
    const score = new Map<number, number>();
    participants.forEach((p) => {
      score.set(p.userId, 0);
    });
    const gameSession: GameSession = {
      gameId: game.id,
      hostId: participants[0].userId,
      type,
      participants: participants,
      observers: [],
      score,
      state: GameMonitorState.Waiting,
      monitors: monitors,
      eventsToPublishInRoom: [],
      rules,
    };
    this.gameSessions.set(game.id, gameSession);
    await this.notifyGameSessionParticipants(gameSession);
    return selectSessionDataForFrontend(gameSession);
  }

  // Notification utils
  async notifyGameSessionParticipants(gameSession: GameSession): Promise<void> {
    gameSession.participants.forEach((p) => {
      if (p.userId === 0) return;
      const adversary = gameSession.participants.find(
        (participant) => participant.userId !== p.userId,
      );
      if (gameSession.type === GameSessionType.QueListGame) {
        this.notificationService.sendMatchedGame(
          p.userId,
          p.username,
          adversary.userId,
          adversary.username,
          gameSession.gameId,
        );
      } else {
        this.notificationService.sendGameStarted(
          p.userId,
          p.username,
          adversary.userId,
          gameSession.gameId,
        );
      }
    });
  }

  // utils function for the service
  createGamer(
    userId: number,
    username = '',
    avatar = '',
    clientId = '',
    isHost = false,
  ): Gamer {
    return {
      userId,
      username,
      clientId,
      avatar,
      isHost,
    };
  }

  checkIfUserIsAPlayer(gameSession: GameSession, userId: number): boolean {
    return gameSession.participants.some((player) => player.userId === userId);
  }
  checkIfUserIsAPlayerByClient(
    gameSession: GameSession,
    clientId: string,
  ): boolean {
    return gameSession.participants.some(
      (player) => player.clientId === clientId,
    );
  }
  checkIfUserIsAnObserver(gameSession: GameSession, userId: number): boolean {
    return gameSession.observers.some((player) => player.userId === userId);
  }

  checkIfSessionIsEnded(gameSessionId: number): boolean {
    const gameSession = this.gameSessions.get(gameSessionId);
    if (!gameSession) return true;
    return gameSession.state === GameMonitorState.Ended;
  }

  // get The Bot Session Games Ids for a user or all
  getBotSessionGamesIds(userId: number): number[] {
    const botSessionsGamesIds: number[] = [];
    this.gameSessions.forEach((gameSession) => {
      if (gameSession.type === GameSessionType.Bot) {
        if (this.checkIfUserIsAPlayer(gameSession, userId)) {
          botSessionsGamesIds.push(gameSession.gameId);
        }
      }
    });
    return botSessionsGamesIds;
  }

  // get the not ended game sessions for a user
  getNotEndedGameSessionsIds(userId: number): number[] {
    const notEndedGameSessionsIds: number[] = [];
    this.gameSessions.forEach((gameSession) => {
      if (gameSession.state !== GameMonitorState.Ended) {
        if (this.checkIfUserIsAPlayer(gameSession, userId)) {
          notEndedGameSessionsIds.push(gameSession.gameId);
        }
      }
    });
    return notEndedGameSessionsIds;
  }

  getNotEndedGameSessionsIdsByClient(clientId: string): number[] {
    const notEndedGameSessionsIds: number[] = [];
    this.gameSessions.forEach((gameSession) => {
      if (gameSession.state !== GameMonitorState.Ended) {
        if (this.checkIfUserIsAPlayerByClient(gameSession, clientId)) {
          notEndedGameSessionsIds.push(gameSession.gameId);
        }
      }
    });
    return notEndedGameSessionsIds;
  }

  hasUnfinishedGameSession(userId: number): boolean {
    const notEndedGameSessions = this.getNotEndedGameSessionsIds(userId);
    return notEndedGameSessions.length > 0;
  }

  setAllUnfinishedGameSessionsToEnded(
    userId: number,
    type?: GameSessionType,
  ): void {
    const checkForType = type !== undefined;
    const notEndedGameSessionsIds = this.getNotEndedGameSessionsIds(userId);
    notEndedGameSessionsIds.forEach((gameSessionId) => {
      const gameSession = this.gameSessions.get(gameSessionId);
      if (
        gameSession &&
        (!checkForType || (checkForType && gameSession.type === type))
      ) {
        gameSession.state = GameMonitorState.Ended;
        gameSession.eventsToPublishInRoom.push({
          event: GAME_EVENTS.GameMonitorStateChanged,
          data: { roomId: gameSessionId, data: GameMonitorState.Ended },
        });
        this.logger.log(
          `try stopping engine loop, if exist for gameSession: ${gameSessionId}`,
        );
        gameSession.gameEngine?.stopLoop();
      }
    });
  }

  cleanGameSessions(): void {
    const toDelete = [];
    this.logger.log('cleaning game sessions');
    for (const gameSession of this.gameSessions.values()) {
      if (gameSession.state === GameMonitorState.Ended) {
        this.logger.log(
          `cleaning - stopping engine loop, and destroying engine for session: ${gameSession.gameId}`,
        );
        gameSession.gameEngine?.stopLoop();
        // wait for 40ms to be sure the game engine is stopped
        delete gameSession.gameEngine;
        toDelete.push(gameSession.gameId);
      }
    }
    for (const gameId of toDelete) {
      this.logger.log(`deleting game session in memory ${gameId}`);
      this.notificationService.sendGameEnded(gameId);
      this.gameSessions.delete(gameId);
    }
  }

  deleteGameSession(gameId: number): void {
    const gameSession = this.gameSessions.get(gameId);
    if (!gameSession) {
      throw new NotFoundException("Game session doesn't exist");
    }
    gameSession.gameEngine?.stopLoop();
    setTimeout(() => {
      delete gameSession.gameEngine;
      this.gameSessions.delete(gameId);
    }, 40);
  }

  getGameSession(gameId: number): GameSession | undefined {
    return this.gameSessions.get(gameId);
  }

  // utils with database  connection
  async createAGame(
    participants: number[],
    type: GameSessionType,
    competitionId?: number,
  ): Promise<Game> {
    let name = 'Challenge Game';
    let description = 'Challenge Game';
    switch (type) {
      case GameSessionType.Bot:
        name = 'Bot Game';
        description = 'Bot Game';
        break;
      case GameSessionType.QueListGame:
        name = 'QueList Game';
        description = 'A game created by a player waiting for an opponent';
        break;
      case GameSessionType.PrivateGame:
      default:
        name = 'Challenge Game';
        description = 'A challenge game between two players';
        break;
    }
    return await this.gameService.createGame({
      name: name,
      description: description,
      participants: {
        createMany: {
          data: participants.map((id) => ({ userId: id })),
        },
      },
      competition: competitionId
        ? { connect: { id: competitionId } }
        : undefined,
    });
  }

  setTheWinner(gameSession: GameSession, winnerId: number) {
    if (winnerId === 0) return;
    this.gameService.updateGame({
      where: { id: gameSession.gameId },
      data: { winner: { connect: { id: winnerId } } },
    });
  }

  writeGameHistory(
    event: GameEvent,
    userId: GameHistory[`userId`],
    gameId: number,
  ) {
    if (userId === 0) return;
    this.gameService.addHistoryToGame({
      event: event,
      user: {
        connect: {
          id: userId,
        },
      },
      game: {
        connect: {
          id: gameId,
        },
      },
    });
  }
}
