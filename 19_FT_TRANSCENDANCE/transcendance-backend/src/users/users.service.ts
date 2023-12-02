import { Injectable } from '@nestjs/common';
import {
  BlockedUser,
  Contact,
  ContactRequest,
  GameEvent,
  Prisma,
  Profile,
  Session,
  Status,
  User,
} from '@prisma/client';
import { UsersRepository } from './users.repository';
import * as argon from 'argon2';
import { FriendsService } from '../friends/friends.service';
import { SchoolNetworkService } from './schoolNetwork.service';

export type UserWithData = User & {
  profile?: Profile;
  sessions: Session[];
  blockedUsers: BlockedUser[];
  blockedFrom: BlockedUser[];
  contacts: Contact[];
  contactedBy: Contact[];
  sentContactRequests: ContactRequest[];
  receivedContactRequests: ContactRequest[];
};

export type ShortBio = Pick<
  UserWithData,
  'id' | 'profile' | 'username' | 'email' | 'updatedAt'
>;

export function exclude<User, Key extends keyof User>(
  user: User,
  keys: Key[],
): Omit<User, Key> {
  for (const key of keys) {
    delete user[key];
  }
  return user;
}

export type UserWithoutSensitiveInfo = Omit<
  User,
  'password' | 'twoFactorEnabled' | 'twoFactorSecret'
>;

export enum BlockedStatus {
  Blocked = 'blocked',
  BlockedBy = 'blockedBy',
  Mutual = 'mutual',
  None = 'none',
}

export function getRandomAvatarUrl(): string {
  const serverBaseUrl = '/uploads';
  const list = [
    'randomAvatars/icons8-bart-simpson-500.png',
    'randomAvatars/icons8-batman-500.png',
    'randomAvatars/icons8-character-500.png',
    'randomAvatars/icons8-deadpool-500.png',
    'randomAvatars/icons8-dj-500.png',
    'randomAvatars/icons8-finn-500.png',
    'randomAvatars/icons8-futurama-bender-500.png',
    'randomAvatars/icons8-homer-simpson-500.png',
    'randomAvatars/icons8-lisa-simpson-500.png',
    'randomAvatars/icons8-marge-simpson-500.png',
    'randomAvatars/icons8-owl-500.png',
    'randomAvatars/icons8-unicorn-500.png',
  ];
  const image = list[Math.floor(Math.random() * list.length)];
  return `${serverBaseUrl}/${image}`;
}

@Injectable()
export class UsersService {
  constructor(
    private repository: UsersRepository,
    private friendsService: FriendsService,
    private readonly schoolNetworkService: SchoolNetworkService,
  ) {}

  // Create a simple user with no profile
  async createUser(params: {
    username: User[`username`];
    email: User[`email`];
    password: User[`password`];
  }) {
    const { email, password, username } = params;
    // hash password
    const hashedPassword = await argon.hash(password);
    // call repository layer
    return this.repository.createUser({
      data: {
        username,
        email,
        password: hashedPassword,
      },
    });
  }

  // Create a user with a profile
  async createUserWithProfile(params: {
    username: User[`username`];
    email: User[`email`];
    password: User[`password`];
    name: Profile[`name`];
    lastName: Profile[`lastname`];
    avatar?: Profile[`avatar`];
    bio?: Profile[`bio`];
    provider?: 'google' | 'facebook' | 'github' | '42';
    providerId?: string;
    data?: {
      accessToken: string;
      refreshToken: string;
    };
  }) {
    const oauthData = { ...params.data, coalitions: [] };
    const hashedPassword = await argon.hash(params.password);
    const providerChecker = (
      provider: 'google' | 'facebook' | 'github' | '42' | undefined,
      toCheck: 'google' | 'facebook' | 'github' | '42',
    ): string | null => {
      if (toCheck === provider) {
        return params.providerId ?? '';
      }
      return null;
    };
    if (params.provider === '42' && params.data.accessToken) {
      oauthData.coalitions = await this.schoolNetworkService.getCoalitions(
        params.data.accessToken,
        params.providerId,
      );
    }
    return this.repository.createUser({
      data: {
        username: params.username,
        email: params.email,
        password: hashedPassword,
        api42Id: providerChecker(params.provider, '42'),
        googleId: providerChecker(params.provider, 'google'),
        facebookId: providerChecker(params.provider, 'facebook'),
        profile: {
          create: {
            name: params.name,
            lastname: params.lastName,
            avatar: params.avatar ?? getRandomAvatarUrl(),
            bio: params.bio,
            oauth: oauthData,
          },
        },
      },
    });
  }

  async getUser(params: {
    id: User[`id`];
  }): Promise<User & { profile: Profile }> {
    const { id } = params;
    return this.repository.getUser({
      where: { id },
      include: { profile: true },
    });
  }

  async getUserProfile(user: User, id: number) {
    const otherProfile = await this.repository.getUserWithSelectedFields({
      where: { id },
      select: {
        id: true,
        username: true,
        email: true,
        role: true,
        googleId: true,
        facebookId: true,
        api42Id: true,
        createdAt: true,
        updatedAt: true,
        profile: true,
        gameHistories: true,
      },
    });
    return this.filterBlockedUsers([otherProfile], user);
  }

  async getUserShortProfile(id: number): Promise<ShortBio> {
    return this.repository.getUserWithSelectedFields({
      where: { id },
      select: {
        id: true,
        username: true,
        email: true,
        profile: true,
        updatedAt: true,
      },
    });
  }

  async getUserWithFriends(userId: User[`id`]) {
    return this.repository.getUser({
      where: {
        id: userId,
      },
      include: {
        contacts: true,
        contactedBy: true,
      },
    });
  }

  async getBlockedUsers(userId: number) {
    const blockedUsers = await this.repository.getBlockedUsers(userId);
    const blockedUsersData = blockedUsers.map(
      (blockedUser) => blockedUser.blockedUser,
    );
    return blockedUsersData.map((blockedUser) =>
      exclude(blockedUser, ['password']),
    );
  }

  async checkBlocked(userId: number, friendId: number): Promise<BlockedStatus> {
    const userWithBlocked = await this.getUserWithBlocked(userId);
    const blocked = userWithBlocked.blockedUsers.find((b) => {
      return b.blockedUserId === friendId;
    });
    const blockedBy = userWithBlocked.blockedFrom.find((b) => {
      return b.userId === friendId;
    });
    if (blocked && blockedBy) {
      return BlockedStatus.Mutual;
    } else if (blocked) {
      return BlockedStatus.Blocked;
    } else if (blockedBy) {
      return BlockedStatus.BlockedBy;
    }
    return BlockedStatus.None;
  }

  async checkBlockedForMany(
    userId: number,
    ids: number[],
  ): Promise<BlockedStatus[]> {
    return await Promise.all(ids.map((id) => this.checkBlocked(userId, id)));
  }

  // Return a user without password if found
  async getUserWithData(params: Partial<User>): Promise<UserWithData | null> {
    const user = await this.repository.getUsers({
      where: params,
      take: 1,
      include: {
        profile: true,
        blockedUsers: true,
        blockedFrom: true,
        contacts: true,
        contactedBy: true,
        sentContactRequests: true,
        receivedContactRequests: true,
        // sessions: true,
      },
    });
    return user.length > 0 ? user[0] : null;
  }

  async updateUser(params: {
    where: Prisma.UserWhereUniqueInput;
    data: Prisma.UserUpdateInput;
    include?: Prisma.UserInclude;
  }): Promise<User | null> {
    return this.repository.updateUser(params);
  }
  async updateProfile(params: {
    where: Prisma.ProfileWhereUniqueInput;
    data: Prisma.ProfileUpdateInput;
    include?: Prisma.ProfileInclude;
  }): Promise<Profile | null> {
    return this.repository.updateProfile(params);
  }

  async updateUserProviderId(
    user: User,
    provider: 'google' | 'facebook' | 'github' | '42',
    providerId: string,
  ) {
    switch (provider) {
      case 'google':
        return this.repository.updateUser({
          where: { id: user.id },
          data: {
            googleId: providerId,
          },
        });
      case '42':
        return this.repository.updateUser({
          where: { id: user.id },
          data: {
            api42Id: providerId,
          },
        });
      default:
        return user;
    }
  }

  async getUserByEmail(email: User[`email`]) {
    return this.repository.getByEmail(email);
  }

  async getUserByUsername(username: User[`username`]) {
    return this.repository.getByUserName(username);
  }

  async getUserWithBlocked(userId: number) {
    return this.repository.getUserWithBlocked(userId);
  }
  async filterBlockedUsers(users: User[], currentUser: User) {
    const userBlocked = await this.getUserWithBlocked(currentUser.id);
    // const blockedUserIds = userBlocked.blockedUsers.map(
    //   (blockedUser) => blockedUser.blockedUserId,
    // );
    const blockedFromIds = userBlocked.blockedFrom.map(
      (blockedFrom) => blockedFrom.userId,
    );
    const blockedUsers = users.filter((user) => {
      return (
        // !blockedUserIds.includes(user.id) &&
        !blockedFromIds.includes(user.id)
      );
    });
    return blockedUsers.map((user) => exclude(user, ['password']));
  }

  // return users, but not blocked ones
  async getUsers(
    params: {
      skip?: number;
      take?: number;
      cursor?: Prisma.UserWhereUniqueInput;
      where?: Prisma.UserWhereInput;
      orderBy?: Prisma.UserOrderByWithRelationInput;
      include?: Prisma.UserInclude;
    },
    user: User,
  ) {
    const users = await this.repository.getUsers(params);
    return this.filterBlockedUsers(users, user);
  }

  // return all users, even blocked ones
  async getAllUsers(params: {
    skip?: number;
    take?: number;
    cursor?: Prisma.UserWhereUniqueInput;
    where?: Prisma.UserWhereInput;
    orderBy?: Prisma.UserOrderByWithRelationInput;
    include?: Prisma.UserInclude;
  }) {
    const users = await this.repository.getUsers(params);
    return users.map((user) => exclude(user, ['password']));
  }

  async blockUser(user: User, blockedUserId: number): Promise<BlockedUser> {
    return this.friendsService.blockUser(user, blockedUserId);
  }

  async unblockUser(user: User, blockedUserId: number): Promise<BlockedUser> {
    return this.friendsService.unblockUser(user, blockedUserId);
  }

  async getUsersWithProfiles() {
    const users = await this.repository.getUsers({
      include: { profile: true },
    });
    return users.map((user) => exclude(user, ['password']));
  }

  // take 1 because we only want one user
  async getUserBySessionId(sessionId: Session[`id`]) {
    return this.repository.getUsers({
      where: { sessions: { some: { id: sessionId } } },
      take: 1,
    });
  }

  async searchUsers(queryParams: {
    query: string;
    skip: number;
    take: number;
    orderBy?: Prisma.UserOrderByWithRelationInput;
  }) {
    const { query, skip, take, orderBy } = queryParams;
    const users = await this.repository.getUsers({
      where: {
        OR: [
          { username: { contains: query } },
          { email: { contains: query } },
          { profile: { name: { contains: query } } },
          { profile: { lastname: { contains: query } } },
        ],
      },
      include: {
        profile: true,
      },
      skip: skip ?? 0,
      take: take ?? 10,
      orderBy: orderBy ?? { username: 'asc' },
    });
    return users.map((user) => exclude(user, ['password']));
  }

  // session management

  createSession(params: {
    user: User;
    token: Session[`token`];
    ipAddress?: Session[`ipAddress`];
    userAgent?: Session[`userAgent`];
    expiresAt: Session[`expiresAt`];
  }) {
    const { user, token, ipAddress, userAgent, expiresAt } = params;
    return this.repository.createSession({
      data: {
        token,
        ipAddress,
        userAgent,
        expiresAt,
        user: { connect: { id: user.id } },
      },
    });
  }

  async getSession(params: { id: Session[`id`] }) {
    const { id } = params;
    return this.repository.getSessions({ where: { id } });
  }

  async getSessionById(id: Session[`id`]) {
    return this.repository.getSession({ where: { id } });
  }

  async updateSession(
    sessionId: Session[`id`],
    refreshToken: Session[`token`],
    expiresAt: Session[`expiresAt`],
  ) {
    return this.repository.updateSession({
      where: { id: sessionId },
      data: { token: refreshToken, expiresAt },
    });
  }

  async deleteSession(params: { id: Session[`id`] }) {
    const { id } = params;
    return this.repository.deleteSession({ where: { id } });
  }

  // get all sessions for a user
  getAllUserSessions(params: { userId: User[`id`]; limit?: number }) {
    const { userId, limit } = params;
    return this.repository.getSessions({
      where: { userId },
      take: limit,
      orderBy: { expiresAt: 'desc' },
    });
  }

  // util function to remove the hashed password field on the user object
  removePassword(user: User) {
    return exclude(user, ['password']);
  }

  // util function to remove all the hashed password fields on users
  removesPasswords(users: User[]) {
    return users.map((user) => exclude(user, ['password']));
  }

  async setTwoFactorAuthenticationSecret(secret: string, id: number) {
    return this.repository.updateUser({
      where: { id: id },
      data: {
        twoFactorSecret: secret,
      },
    });
  }

  async turnOnTwoFactorAuthentication(id: number) {
    return this.repository.updateUser({
      where: { id: id },
      data: {
        twoFactorEnabled: true,
      },
    });
  }

  async turnOffTwoFactorAuthentication(id: number) {
    return this.repository.updateUser({
      where: { id: id },
      data: {
        twoFactorEnabled: false,
        twoFactorSecret: null,
      },
    });
  }
  async changeStatus(userId: number, status: Status) {
    try {
      await this.repository.updateProfile({
        where: {
          userId: userId,
        },
        data: {
          status: status,
        },
      });
    } catch (e) {
      console.log(`Can't change status for user: ${userId} to ${status}`);
    }
  }

  async getUsersOrderedByWins(params: { skip: number; take: number }) {
    const users = await this.repository.getUsersOrderedByWins(params);
    const usersNoPasswords = users.map((user) => exclude(user, ['password']));
    const usersWithScore = usersNoPasswords.map((user) => {
      const wins = user.gameHistories.filter(
        (history) => history.event === GameEvent.MATCH_WON,
      ).length;
      const loss = user.gameHistories.filter(
        (history) => history.event === GameEvent.MATCH_LOST,
      ).length;
      const score = { wins, loss };
      return { ...user, score };
    });

    return usersWithScore.sort((a, b) => {
      // Sort by wins, and if tied, then by fewer losses
      if (b.score.wins !== a.score.wins) {
        return b.score.wins - a.score.wins; // Sort by wins
      } else {
        return a.score.loss - b.score.loss; // If wins are tied, sort by fewer losses
      }
    });
  }

  async getAppStatistics() {
    const stats = await this.repository.getStats();
    return stats;
  }
}
