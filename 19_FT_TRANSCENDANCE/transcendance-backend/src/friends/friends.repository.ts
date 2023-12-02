import { Injectable } from '@nestjs/common';
import { PrismaService } from '../prisma/prisma.service';
import { Contact, ContactRequest, Profile, User } from '@prisma/client';
import { UserWithoutSensitiveInfo } from '../users/users.service';

export interface ContactRequestWithReceiver extends ContactRequest {
  receiver: {
    profile: Profile;
  };
}
export interface ContactRequestWithSender extends ContactRequest {
  sender: {
    profile: Profile;
  };
}

@Injectable()
export class FriendsRepository {
  constructor(private prisma: PrismaService) {}

  async getFriend(userId: User[`id`], friendId: User[`id`]): Promise<Contact> {
    return this.prisma.contact.findFirst({
      where: {
        OR: [
          {
            userId: userId,
            contactId: friendId,
          },
          {
            userId: friendId,
            contactId: userId,
          },
        ],
      },
    });
  }
  async getFriends(id: number): Promise<UserWithoutSensitiveInfo[]> {
    const relations = await this.prisma.contact.findMany({
      where: {
        OR: [
          {
            userId: id,
          },
          {
            contactId: id,
          },
        ],
      },
      include: {
        user: {
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
        },
        contact: {
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
        },
      },
    });
    if (!relations) {
      return []; // No friends found
    }
    return relations.map((relation) => {
      if (relation.userId === id) {
        return relation.contact;
      } else {
        return relation.user;
      }
    });
  }
  async removeFriend(userId: number, friendId: number) {
    return this.prisma.contact.deleteMany({
      where: {
        OR: [
          {
            userId: userId,
            contactId: friendId,
          },
          {
            userId: friendId,
            contactId: userId,
          },
        ],
      },
    });
  }
  async addFriendRequest(userId: number, targetId: number) {
    return this.prisma.contactRequest.create({
      data: {
        senderId: userId,
        receiverId: targetId,
      },
    });
  }
  async getSentFriendRequests(
    id: number,
  ): Promise<ContactRequestWithReceiver[]> {
    return this.prisma.contactRequest.findMany({
      where: {
        senderId: id,
      },
      include: {
        receiver: {
          include: {
            profile: true,
          },
        },
      },
    });
  }
  async getReceivedFriendRequests(
    id: number,
  ): Promise<ContactRequestWithSender[]> {
    return this.prisma.contactRequest.findMany({
      where: {
        receiverId: id,
      },
      include: {
        sender: {
          include: {
            profile: true,
          },
        },
      },
    });
  }
  async cancelFriendRequest(requestId: number) {
    return await this.prisma.contactRequest.delete({
      where: {
        id: requestId,
      },
    });
  }
  async approveFriendRequest(requestId: number) {
    const request = await this.prisma.contactRequest.findUnique({
      where: {
        id: requestId,
      },
    });
    const relation = await this.prisma.contact.create({
      data: {
        userId: request.senderId,
        contactId: request.receiverId,
      },
    });
    if (relation) {
      await this.prisma.contactRequest.delete({
        where: {
          id: requestId,
        },
      });
    }
    return relation;
  }
  async rejectFriendRequest(requestId: number) {
    return this.prisma.contactRequest.delete({
      where: {
        id: requestId,
      },
    });
  }
  async removeRequest(userId: number, otherId: number) {
    const request = await this.prisma.contactRequest.findFirst({
      where: {
        OR: [
          {
            senderId: userId,
            receiverId: otherId,
          },
          {
            senderId: otherId,
            receiverId: userId,
          },
        ],
      },
    });
    if (request) {
      return this.prisma.contactRequest.delete({
        where: {
          id: request.id,
        },
      });
    }
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
}
