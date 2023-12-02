// src/games/interfaces/game.interfaces.ts
import { GAME_EVENTS } from './events.interfaces';
import { PAD_DIRECTION } from './gameActions.interface';
import GameEngine from '../engine';

export interface Gamer {
  userId: number;
  username: string;
  clientId: string;
  avatar?: string;
  isHost?: boolean;
}

export enum GameMonitorState {
  Waiting,
  Preloading,
  Menu,
  Ready,
  Play,
  Pause,
  Ended,
}

export enum GameSessionType {
  Bot,
  QueListGame,
  CompetitionGame,
  PrivateGame,
}

export type ManagedTheme = 'Classic' | 'Arcade' | 'Soccer';
export interface GameRules {
  maxScore: number;
  maxTime: number;
  theme?: ManagedTheme;
}

export interface GameSession {
  gameId: number;
  hostId: number;
  type: GameSessionType;
  participants: Gamer[];
  observers: Gamer[];
  score: Map<number, number>;
  state: GameMonitorState;
  monitors: Array<GameMonitorState>;
  eventsToPublishInRoom: {
    event: GAME_EVENTS;
    data: { roomId: number; data: unknown };
  }[];
  gameEngine?: GameEngine;
  rules: GameRules;
}

export interface WaitingGameSession {
  waitingGameId: number;
  hostId: number;
  type: GameSessionType.PrivateGame | GameSessionType.QueListGame;
  participants: Gamer[];
  rules: GameRules;
  played?: boolean;
}
