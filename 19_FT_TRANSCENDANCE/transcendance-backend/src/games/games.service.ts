import { Injectable } from '@nestjs/common';
import {
  Game as PrismaGame,
  GameObservation,
  GameParticipation,
  GameHistory,
  Prisma,
  Competition,
} from '@prisma/client';
import { GamesRepository } from './games.repository';

export interface Game extends PrismaGame {
  competition?: Competition;
}

export interface CompleteGameHistory {
  gameId: number;
  gameName: string;
  winnerId: number;
  histories: Record<number, GameHistory[]>; // {opponentId: GameHistory[]}
}

@Injectable()
export class GamesService {
  constructor(private gamesRepository: GamesRepository) {}
  async createGame(data: Prisma.GameCreateInput): Promise<Game> {
    return this.gamesRepository.createGame({
      data,
      include: { competition: true },
    });
  }

  async addParticipant(gameId: number, userId: number): Promise<Game> {
    return this.gamesRepository.createParticipant({ gameId, userId });
  }

  async removeParticipant(gameId: number, userId: number): Promise<void> {
    await this.gamesRepository.removeParticipant({ gameId, userId });
  }

  async addObserver(gameId: number, userId: number): Promise<Game> {
    return this.gamesRepository.createObserver({ gameId, userId });
  }

  async removeObserver(gameId: number, userId: number): Promise<void> {
    await this.gamesRepository.removeObserver({ gameId, userId });
  }

  async addGameToCompetition(
    gameId: number,
    competitionId: number,
  ): Promise<Game> {
    return this.gamesRepository.addGameToCompetition({ gameId, competitionId });
  }

  async removeGameFromCompetition(gameId: number): Promise<Game> {
    return this.gamesRepository.removeGameFromCompetition(gameId);
  }

  async findOneGame(where: Prisma.GameWhereUniqueInput): Promise<Game | null> {
    return this.gamesRepository.getGame({ where });
  }

  async getGameObservers(gameId: number): Promise<GameObservation[]> {
    return this.gamesRepository.getObservers(gameId);
  }

  async getGameParticipants(gameId: number): Promise<GameParticipation[]> {
    return this.gamesRepository.getParticipants(gameId);
  }

  async getCompetitionFromGame(gameId: number): Promise<Competition | null> {
    const game = (await this.gamesRepository.getGame({
      where: { id: gameId },
      include: { competition: true },
    })) as Game;
    return game?.competition || null;
  }

  async getGamesFromCompetition(competitionId: number): Promise<Game[]> {
    return this.gamesRepository.getGames({ where: { competitionId } });
  }

  async getUserGameHistories(userId: number): Promise<GameHistory[]> {
    return this.gamesRepository.getGameHistories({ where: { userId } });
  }

  async getGameHistories(gameId: number): Promise<GameHistory[]> {
    return this.gamesRepository.getGameHistories({ where: { gameId } });
  }

  async getCompleteUserGameHistories(
    userId: number,
  ): Promise<CompleteGameHistory[]> {
    const participationWithGame =
      await this.gamesRepository.getUserParticipationWithGameHistories(userId);
    return participationWithGame.map((participation) => {
      const { game } = participation;
      const { histories } = game;
      const opponentHistories = this.groupOpponentsHistories(histories);
      return {
        gameId: game.id,
        gameName: game.name,
        winnerId: game.winnerId,
        histories: opponentHistories,
      };
    });
  }

  private groupOpponentsHistories(
    gameHistories: GameHistory[],
  ): Record<number, GameHistory[]> {
    const opponentsHistories = {} as Record<number, GameHistory[]>;
    const allOpponents = gameHistories.map((history) => history.userId);
    const uniqueOpponents = [...new Set(allOpponents)];
    uniqueOpponents.forEach((opponentId) => {
      opponentsHistories[opponentId] = gameHistories.filter(
        (history) => history.userId === opponentId,
      );
    });
    return opponentsHistories;
  }

  async addHistoryToGame(
    data: Prisma.GameHistoryCreateInput,
  ): Promise<GameHistory> {
    return this.gamesRepository.createGameHistory({ data });
  }

  async updateGame(params: {
    where: Prisma.GameWhereUniqueInput;
    data: Prisma.GameUpdateInput;
  }): Promise<Game> {
    return this.gamesRepository.updateGame(params);
  }
}
