import { Injectable } from '@nestjs/common';
import {
  Prisma,
  BlockedUser,
  Session,
  User,
  Profile,
  GameEvent,
} from '@prisma/client';
import { PrismaService } from 'src/prisma/prisma.service';

export interface BlockedUserWithProfiles extends BlockedUser {
  blockedUser: {
    id: number;
    username: string;
    password: string;
    profile: Profile;
  };
}
@Injectable()
export class UsersRepository {
  constructor(private prisma: PrismaService) {}

  async createUser(params: { data: Prisma.UserCreateInput }): Promise<User> {
    const { data } = params;
    return this.prisma.user.create({ data });
  }
  async getUsers(params: {
    skip?: number;
    take?: number;
    cursor?: Prisma.UserWhereUniqueInput;
    where?: Prisma.UserWhereInput;
    orderBy?: Prisma.UserOrderByWithRelationInput;
    include?: Prisma.UserInclude;
  }) {
    const { skip, take, cursor, where, orderBy, include } = params;
    return this.prisma.user.findMany({
      skip,
      take,
      cursor,
      where,
      orderBy,
      include,
    });
  }

  async getUsersWithSelected(params: {
    skip?: number;
    take?: number;
    cursor?: Prisma.UserWhereUniqueInput;
    where?: Prisma.UserWhereInput;
    orderBy?: Prisma.UserOrderByWithRelationInput;
    select?: Prisma.UserSelect;
  }) {
    const { skip, take, cursor, where, orderBy, select } = params;
    return this.prisma.user.findMany({
      skip,
      take,
      cursor,
      where,
      orderBy,
      select,
    });
  }

  async updateUser(params: {
    where: Prisma.UserWhereUniqueInput;
    data: Prisma.UserUpdateInput;
    include?: Prisma.UserInclude;
  }): Promise<User> {
    const { where, data, include } = params;
    return this.prisma.user.update({ where, data, include });
  }
  async updateProfile(params: {
    where: Prisma.ProfileWhereUniqueInput;
    data: Prisma.ProfileUpdateInput;
    include?: Prisma.ProfileInclude;
  }): Promise<Profile> {
    const { where, data } = params;
    return this.prisma.profile.update({ where, data });
  }

  async deleteUser(params: {
    where: Prisma.UserWhereUniqueInput;
    include?: Prisma.UserInclude;
  }): Promise<User> {
    const { where, include } = params;
    return this.prisma.user.delete({ where, include });
  }

  async getUser(params: {
    where: Prisma.UserWhereUniqueInput;
    include?: Prisma.UserInclude;
  }) {
    const { where, include } = params;
    return this.prisma.user.findUnique({ where, include });
  }

  getUserWithSelectedFields(params: {
    where: Prisma.UserWhereUniqueInput;
    select: Prisma.UserSelect;
  }) {
    const { where, select } = params;
    return this.prisma.user.findUnique({ where, select });
  }

  async getByID(id: User[`id`]): Promise<User | null> {
    return this.prisma.user.findUnique({ where: { id } });
  }

  async getByUserName(username: User[`username`]): Promise<User | null> {
    return this.prisma.user.findUnique({ where: { username } });
  }

  async getByEmail(email: User[`email`]): Promise<User | null> {
    return this.prisma.user.findUnique({ where: { email } });
  }

  // session
  async createSession(params: {
    data: Prisma.SessionCreateInput;
  }): Promise<Session> {
    const { data } = params;
    return this.prisma.session.create({ data });
  }

  async getSessions(params: {
    skip?: number;
    take?: number;
    cursor?: Prisma.SessionWhereUniqueInput;
    where?: Prisma.SessionWhereInput;
    orderBy?: Prisma.SessionOrderByWithRelationInput;
  }): Promise<Session[]> {
    const { skip, take, cursor, where, orderBy } = params;
    return this.prisma.session.findMany({ skip, take, cursor, where, orderBy });
  }

  async updateSession(params: {
    where: Prisma.SessionWhereUniqueInput;
    data: Prisma.SessionUpdateInput;
  }): Promise<Session> {
    const { where, data } = params;
    return this.prisma.session.update({ where, data });
  }

  async deleteSession(params: {
    where: Prisma.SessionWhereUniqueInput;
  }): Promise<Session> {
    const { where } = params;
    return this.prisma.session.delete({ where });
  }

  async getSession(params: {
    where: Prisma.SessionWhereUniqueInput;
  }): Promise<Session | null> {
    const { where } = params;
    return this.prisma.session.findUnique({ where });
  }
  async getUserWithBlocked(userId: number) {
    return this.prisma.user.findUnique({
      where: {
        id: userId,
      },
      include: {
        blockedUsers: true,
        blockedFrom: true,
      },
    });
  }
  async getBlockUser(userId: number, blockedUserId: number) {
    return this.prisma.blockedUser.findFirst({
      where: {
        userId: userId,
        blockedUserId: blockedUserId,
      },
    });
  }

  async blockUser(userId: number, blockedUserId: number) {
    return this.prisma.blockedUser.create({
      data: {
        userId: userId,
        blockedUserId: blockedUserId,
      },
    });
  }
  async unblockUser(userId: number, blockedUserId: number) {
    const relation = await this.getBlockUser(userId, blockedUserId);
    if (relation) {
      return this.prisma.blockedUser.delete({
        where: {
          id: relation.id,
        },
      });
    }
  }
  async getBlockedUsers(userId: number): Promise<BlockedUserWithProfiles[]> {
    return this.prisma.blockedUser.findMany({
      where: {
        userId: userId,
      },
      include: {
        blockedUser: {
          include: {
            profile: true,
          },
        },
      },
    });
  }
  async getUsersOrderedByWins(params: { skip: number; take: number }) {
    const { skip, take } = params;
    return this.prisma.user.findMany({
      include: {
        gameHistories: {
          where: {
            OR: [
              { event: GameEvent.MATCH_WON },
              { event: GameEvent.MATCH_LOST },
            ],
          },
          orderBy: {
            event: 'desc',
          },
        },
        profile: true,
      },
      take,
      skip,
    });
  }

  async getStats() {
    const totalUsers = await this.prisma.user.count();
    const activeUsers = await this.prisma.session.count({
      where: {
        createdAt: {
          gte: new Date(new Date().setDate(new Date().getDate() - 30)), // Last 30 days
        },
      },
    });
    const totalGamesPlayed = await this.prisma.game.count();
    const totalCompetitions = await this.prisma.competition.count();
    const totalNotificationsSent = 0; //await this.prisma.notification.count();
    const totalGames = await this.prisma.game.count();
    const averageGamesPerUser = totalGames / totalUsers;

    // This is a bit more complex, you'd need to group by game and count the participants or histories
    const mostActiveGame = await this.prisma.gameHistory.groupBy({
      by: ['gameId'],
      _count: {
        gameId: true,
      },
      orderBy: {
        _count: {
          gameId: 'desc',
        },
      },
      take: 1,
    });

    // Similarly, group by user and count the participations or histories
    const mostActiveUser = await this.prisma.gameParticipation.groupBy({
      by: ['userId'],
      _count: {
        userId: true,
      },
      orderBy: {
        _count: {
          userId: 'desc',
        },
      },
      take: 1,
    });

    return {
      totalUsers,
      activeUsers,
      totalGamesPlayed,
      totalCompetitions,
      totalNotificationsSent,
      averageGamesPerUser,
      mostActiveGame: mostActiveGame[0]?.gameId,
      mostActiveUser: mostActiveUser[0]?.userId,
    };
  }
}
