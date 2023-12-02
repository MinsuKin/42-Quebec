import { Injectable } from '@nestjs/common';
import { Prisma, User, PrivateMessage } from '@prisma/client';
import { PrismaService } from 'src/prisma/prisma.service';
import { UserWithoutSensitiveInfo } from '../users/users.service';

@Injectable()
export class MessageRepository {
  constructor(private readonly prisma: PrismaService) {}

  async createPrivateMessage(
    data: Prisma.PrivateMessageCreateInput,
  ): Promise<PrivateMessage> {
    return this.prisma.privateMessage.create({ data });
  }

  async getPrivateMessages(
    userOneId: User[`id`],
    userTwoId: User[`id`],
    { skip, take }: { skip: number; take: number },
  ): Promise<PrivateMessage[]> {
    return this.prisma.privateMessage.findMany({
      where: {
        OR: [
          { senderId: userOneId, receiverId: userTwoId },
          { senderId: userTwoId, receiverId: userOneId },
        ],
      },
      skip,
      take,
      orderBy: { timestamp: 'desc' }, // Optionally order by timestamp to get the latest messages first
    });
  }

  async getUniqueConversations(
    userId: User[`id`],
  ): Promise<Array<UserWithoutSensitiveInfo>> {
    const privateMessages = await this.prisma.privateMessage.findMany({
      where: {
        OR: [{ senderId: userId }, { receiverId: userId }],
      },
      select: { senderId: true, receiverId: true },
      orderBy: { timestamp: 'desc' },
    });
    const distinctUserIds = Array.from(
      new Set(
        privateMessages.flatMap((message) => [
          message.senderId,
          message.receiverId,
        ]),
      ),
    ).filter((id) => id !== userId);

    // Fetch the details of all these unique users, including their profiles.
    return this.prisma.user.findMany({
      where: { id: { in: distinctUserIds } },
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
      },
    });
  }
}
