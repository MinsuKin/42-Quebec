import { ForbiddenException, Injectable } from '@nestjs/common';
import { User, PrivateMessage } from '@prisma/client';
import { MessageRepository } from './message.repository';
import { UsersService, UserWithoutSensitiveInfo } from '../users/users.service';
import { CreateMessageDto } from './dto';

@Injectable()
export class MessageService {
  constructor(
    private readonly messageRepository: MessageRepository,
    private readonly userService: UsersService,
  ) {}

  async createPrivateMessage(
    data: CreateMessageDto,
    senderId: number,
  ): Promise<PrivateMessage> {
    try {
      await this.canListenToPrivateMessages(senderId, data.receiverId);
      return this.messageRepository.createPrivateMessage({
        text: data.content,
        receiver: {
          connect: {
            id: data.receiverId,
          },
        },
        sender: {
          connect: {
            id: senderId,
          },
        },
      });
    } catch (error) {
      throw error;
    }
  }

  async canListenToPrivateMessages(userId: number, friendId: number) {
    const blockedStatus = await this.userService.checkBlocked(userId, friendId);
    // blocked or mutually blocked
    if (blockedStatus === 'blockedBy') {
      throw new ForbiddenException('You are blocked by this user');
    } else if (blockedStatus === 'blocked' || blockedStatus === 'mutual') {
      throw new ForbiddenException('You blocked this user');
    }
  }

  async getPrivateMessages(
    userOneId: User[`id`],
    userTwoId: User[`id`],
    params: { skip: number; take: number },
  ): Promise<PrivateMessage[]> {
    return this.messageRepository.getPrivateMessages(
      userOneId,
      userTwoId,
      params,
    );
  }

  async getUniqueConversations(
    userId: User[`id`],
  ): Promise<UserWithoutSensitiveInfo[]> {
    return this.messageRepository.getUniqueConversations(userId);
  }
}
