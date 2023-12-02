import { Injectable } from '@nestjs/common';
import {
  Prisma,
  ChatRoom,
  ChatRoomMessage,
  User,
  Role,
  ChatRoomMember,
  Profile,
  RoomType,
} from '@prisma/client';
import { PrismaService } from 'src/prisma/prisma.service';

export type ChatRoomWithMembers = ChatRoom & {
  members: ChatRoomMember[];
};

export type MemberRoomWithUserProfiles = ChatRoomMember & {
  member: User & {
    profile: Profile;
  };
};

@Injectable()
export class ChatRepository {
  constructor(private prisma: PrismaService) {}

  async getRooms(params: {
    skip?: number;
    take?: number;
    cursor?: Prisma.ChatRoomWhereUniqueInput;
    where?: Prisma.ChatRoomWhereInput;
    orderBy?: Prisma.ChatRoomOrderByWithRelationInput;
    include?: Prisma.ChatRoomInclude;
  }): Promise<ChatRoom[]> {
    const { skip, take, cursor, where, orderBy, include } = params;
    return this.prisma.chatRoom.findMany({
      skip,
      take,
      cursor,
      where,
      orderBy,
      include,
    });
  }

  async getPublicRooms(): Promise<ChatRoomWithMembers[]> {
    return this.prisma.chatRoom.findMany({
      where: {
        OR: [{ type: RoomType.PUBLIC }, { type: RoomType.PROTECTED }],
      },
      include: { members: true },
      orderBy: { members: { _count: 'desc' } },
    });
  }

  // Get a room, with its members
  async getRoom(params: {
    where: Prisma.ChatRoomWhereUniqueInput;
  }): Promise<ChatRoomWithMembers> {
    const { where } = params;
    return this.prisma.chatRoom.findUnique({
      where,
      include: {
        members: true,
      },
    });
  }

  async getSimpleRoom(params: {
    where: Prisma.ChatRoomWhereUniqueInput;
  }): Promise<ChatRoom> {
    const { where } = params;
    return this.prisma.chatRoom.findFirst({
      where,
    });
  }

  async getRoomByName(name: string): Promise<ChatRoom | null> {
    return this.prisma.chatRoom.findFirst({
      where: {
        name: name,
      },
    });
  }

  async createRoom(
    params: { data: Prisma.ChatRoomCreateInput },
    memberId: User[`id`],
  ): Promise<ChatRoomWithMembers> {
    const { data } = params;
    return this.prisma.chatRoom.create({
      data: {
        ...data,
        members: {
          create: {
            memberId: memberId,
            role: Role.OWNER,
          },
        },
      },
      include: {
        members: true,
      },
    });
  }

  async updateRoom(params: {
    where: Prisma.ChatRoomWhereUniqueInput;
    data: Prisma.ChatRoomUpdateInput;
  }): Promise<ChatRoomWithMembers> {
    return this.prisma.chatRoom.update({
      where: params.where,
      data: params.data,
      include: {
        members: true,
      },
    });
  }

  async getChatRoomMembers(
    roomId: ChatRoom[`id`],
  ): Promise<MemberRoomWithUserProfiles[]> {
    return this.prisma.chatRoomMember.findMany({
      where: {
        chatroomId: roomId,
      },
      include: {
        member: {
          include: {
            profile: true,
          },
        },
      },
    });
  }

  async getChatRoomMember(
    userId: User[`id`],
    roomId: ChatRoom[`id`],
  ): Promise<MemberRoomWithUserProfiles> {
    return this.prisma.chatRoomMember.findFirst({
      where: {
        memberId: userId,
        chatroomId: roomId,
      },
      include: {
        member: {
          include: {
            profile: true,
          },
        },
      },
    });
  }

  async getChatRoomOwner(
    roomId: ChatRoom[`id`],
  ): Promise<MemberRoomWithUserProfiles> {
    return this.prisma.chatRoomMember.findFirst({
      where: {
        chatroomId: roomId,
        role: Role.OWNER,
      },
      include: {
        member: {
          include: {
            profile: true,
          },
        },
      },
    });
  }

  // find admin and owners
  async getChatRoomAdmins(
    roomId: ChatRoom[`id`],
  ): Promise<MemberRoomWithUserProfiles[]> {
    return this.prisma.chatRoomMember.findMany({
      where: {
        chatroomId: roomId,
        OR: [{ role: Role.ADMIN }, { role: Role.OWNER }],
      },
      include: {
        member: {
          include: {
            profile: true,
          },
        },
      },
    });
  }

  async updateChatRoomMember(params: {
    where: Prisma.ChatRoomMemberWhereUniqueInput;
    data: Prisma.ChatRoomMemberUpdateInput;
  }): Promise<ChatRoomMember> {
    const { data, where } = params;
    return this.prisma.chatRoomMember.update({ data, where });
  }

  async updateManyChatRoomMembers(params: {
    where: Prisma.ChatRoomMemberWhereInput;
    data: Prisma.ChatRoomMemberUpdateInput;
  }) {
    const { data, where } = params;
    return this.prisma.chatRoomMember.updateMany({ data, where });
  }

  /*
   * First, try to find an ADMIN from the messages room.
   * Or any member who is not banned.
   * return null when no other member is found.
   */
  async findPotentialNewOwner(
    roomId: ChatRoom['id'],
  ): Promise<ChatRoomMember | null> {
    const potentialAdminOwner = await this.prisma.chatRoomMember.findFirst({
      where: {
        chatroomId: roomId,
        role: Role.ADMIN,
      },
    });
    if (potentialAdminOwner) {
      return potentialAdminOwner;
    }
    const potentialRegularOwner = await this.prisma.chatRoomMember.findFirst({
      where: {
        chatroomId: roomId,
        NOT: {
          OR: [{ role: Role.OWNER }, { role: Role.BAN }],
        },
      },
    });
    if (potentialRegularOwner) {
      return potentialRegularOwner;
    }
    return null;
  }

  async deleteMemberFromRoom(id: ChatRoomMember[`id`]) {
    return this.prisma.chatRoomMember.delete({
      where: {
        id: id,
      },
    });
  }

  async deleteRoom(roomId: ChatRoom[`id`]): Promise<ChatRoom> {
    return this.prisma.chatRoom.delete({
      where: {
        id: roomId,
      },
    });
  }

  async joinRoom(userId: User[`id`], roomId: ChatRoom[`id`], role: Role) {
    return this.prisma.chatRoomMember.create({
      data: {
        memberId: userId,
        chatroomId: roomId,
        role: role,
      },
    });
  }

  async findUserRoomsData(
    userId: User[`id`],
    whereMember?: Prisma.ChatRoomMemberWhereInput,
    whereRoom?: Prisma.ChatRoomWhereInput,
  ): Promise<ChatRoomMember[]> {
    const chatRoomWhere = {
      ...whereRoom,
    };
    return this.prisma.chatRoomMember.findMany({
      where: {
        ...whereMember,
        memberId: userId,
        chatroom: chatRoomWhere,
      },
    });
  }

  async getMemberRooms(userId: User[`id`]): Promise<ChatRoomWithMembers[]> {
    return this.prisma.chatRoom.findMany({
      where: {
        members: {
          some: {
            memberId: userId,
          },
        },
      },
      include: {
        members: true,
      },
    });
  }

  async createRoomMessage(params: {
    data: Prisma.ChatRoomMessageCreateInput;
  }): Promise<ChatRoomMessage> {
    const { data } = params;
    return this.prisma.chatRoomMessage.create({
      data,
    });
  }

  async getRoomMessages(
    roomId: ChatRoom[`id`],
    params: { skip: number; take: number },
  ): Promise<ChatRoomMessage[]> {
    return this.prisma.chatRoomMessage.findMany({
      where: {
        chatroomId: roomId,
      },
      orderBy: {
        timestamp: 'asc',
      },
      skip: params.skip,
      take: params.take,
    });
  }

  /* Utilities */
  async isOwnerOrAdmin(
    roomId: ChatRoom[`id`],
    userId: User[`id`],
  ): Promise<boolean> {
    const member = await this.prisma.chatRoomMember.findFirst({
      where: {
        chatroomId: roomId,
        memberId: userId,
        OR: [{ role: Role.OWNER }, { role: Role.ADMIN }],
      },
    });
    return !!member;
  }

  async updateRoomPassword(
    roomId: ChatRoom[`id`],
    hashedPassword: string,
  ): Promise<ChatRoom> {
    return this.prisma.chatRoom.update({
      where: { id: roomId },
      data: { password: hashedPassword },
    });
  }
}
