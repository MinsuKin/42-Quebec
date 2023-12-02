import { Injectable } from '@nestjs/common';
import {
  Game,
  GameHistory,
  GameObservation,
  GameParticipation,
  Prisma,
} from '@prisma/client';
import { PrismaService } from 'src/prisma/prisma.service';

interface ParticipationWithGameHistory extends GameParticipation {
  game: Game & {
    histories: GameHistory[];
  };
}

@Injectable()
export class GamesRepository {
  constructor(private prisma: PrismaService) {}

  async createGame(params: {
    data: Prisma.GameCreateInput;
    include?: Prisma.GameInclude;
  }): Promise<Game> {
    const { data, include } = params;
    return this.prisma.game.create({ data, include });
  }

  createParticipant(params: { gameId: number; userId: number }): Promise<Game> {
    const { gameId, userId } = params;
    return this.prisma.game.update({
      where: { id: gameId },
      data: {
        participants: {
          create: {
            userId,
          },
        },
      },
      include: {
        participants: true,
        observers: true,
        competition: true,
      },
    });
  }

  async removeParticipant(params: {
    gameId: number;
    userId: number;
  }): Promise<GameParticipation> {
    const { gameId, userId } = params;
    return this.prisma.gameParticipation.delete({
      where: { gameId_userId: { gameId, userId } },
    });
  }

  createObserver(params: { gameId: number; userId: number }): Promise<Game> {
    const { gameId, userId } = params;
    return this.prisma.game.update({
      where: { id: gameId },
      data: {
        observers: {
          create: {
            userId,
          },
        },
      },
      include: {
        participants: true,
        observers: true,
        competition: true,
      },
    });
  }

  async removeObserver(params: {
    gameId: number;
    userId: number;
  }): Promise<GameObservation> {
    const { gameId, userId } = params;
    return this.prisma.gameObservation.delete({
      where: { gameId_userId: { gameId, userId } },
    });
  }

  async getParticipants(gameId: number): Promise<GameParticipation[]> {
    return this.prisma.gameParticipation.findMany({
      where: { gameId },
    });
  }

  async getObservers(gameId: number): Promise<GameObservation[]> {
    return this.prisma.gameObservation.findMany({
      where: { gameId },
    });
  }

  async getGames(params: {
    skip?: number;
    take?: number;
    cursor?: Prisma.GameWhereUniqueInput;
    where?: Prisma.GameWhereInput;
    orderBy?: Prisma.GameOrderByWithRelationInput;
    include?: Prisma.GameInclude;
  }): Promise<Game[]> {
    const { skip, take, cursor, where, orderBy, include } = params;
    return this.prisma.game.findMany({
      skip,
      take,
      cursor,
      where,
      orderBy,
      include,
    });
  }

  async updateGame(params: {
    where: Prisma.GameWhereUniqueInput;
    data: Prisma.GameUpdateInput;
  }): Promise<Game> {
    const { where, data } = params;
    return this.prisma.game.update({ where, data });
  }

  async deleteGame(params: {
    where: Prisma.GameWhereUniqueInput;
  }): Promise<Game> {
    const { where } = params;
    return this.prisma.game.delete({ where });
  }

  async getGame(params: {
    where: Prisma.GameWhereUniqueInput;
    include?: Prisma.GameInclude;
  }): Promise<Game | null> {
    const { where, include } = params;
    return this.prisma.game.findUnique({ where, include: include });
  }

  getGameHistories(params: {
    skip?: number;
    take?: number;
    cursor?: Prisma.GameHistoryWhereUniqueInput;
    where?: Prisma.GameHistoryWhereInput;
    orderBy?: Prisma.GameHistoryOrderByWithRelationInput;
    include?: Prisma.GameHistoryInclude;
  }): Promise<GameHistory[]> {
    const { skip, take, cursor, where, orderBy, include } = params;
    return this.prisma.gameHistory.findMany({
      skip,
      take,
      cursor,
      where,
      orderBy,
      include,
    });
  }

  getParticipation(params: {
    where: Prisma.GameParticipationWhereInput;
    include?: Prisma.GameParticipationInclude;
  }): Promise<GameParticipation[]> {
    const { where, include } = params;
    return this.prisma.gameParticipation.findMany({ where, include });
  }

  getGameHistory(params: {
    where: Prisma.GameHistoryWhereUniqueInput;
    include?: Prisma.GameHistoryInclude;
  }): Promise<GameHistory | null> {
    const { where, include } = params;
    return this.prisma.gameHistory.findUnique({ where, include });
  }

  getUserParticipationWithGameHistories(
    userId: number,
  ): Promise<ParticipationWithGameHistory[]> {
    return this.prisma.gameParticipation.findMany({
      where: { userId },
      include: {
        game: {
          include: {
            histories: true,
          },
        },
      },
      orderBy: {
        game: {
          id: 'desc',
        },
      },
    });
  }

  createGameHistory(params: {
    data: Prisma.GameHistoryCreateInput;
  }): Promise<GameHistory> {
    const { data } = params;
    return this.prisma.gameHistory.create({ data });
  }

  getGameCompetition(params: {
    where: Prisma.CompetitionWhereUniqueInput;
    include?: Prisma.CompetitionInclude;
  }) {
    const { where, include } = params;
    return this.prisma.competition.findUnique({ where, include: include });
  }

  async addGameToCompetition(params: {
    gameId: number;
    competitionId: number;
  }): Promise<Game> {
    const { gameId, competitionId } = params;
    return this.prisma.game.update({
      where: { id: gameId },
      data: {
        competitionId,
      },
    });
  }

  async removeGameFromCompetition(gameId: number): Promise<Game> {
    return this.prisma.game.update({
      where: { id: gameId },
      data: {
        competitionId: null,
      },
    });
  }
}
