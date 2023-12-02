import {
  BadRequestException,
  ForbiddenException,
  Injectable,
  NotFoundException,
  UnauthorizedException,
} from '@nestjs/common';
import { ChatRepository, ChatRoomWithMembers } from './chat.repository';
import * as argon from 'argon2';
import { getRandomAvatarUrl, UserWithData } from '../users/users.service';
import { ChatRoom, ChatRoomMember, Role, RoomType } from '@prisma/client';
import {
  CreateRoomDto,
  UpdatePasswordDto,
  UpdateRoomInfoDto,
  UpdateRoleDto,
} from './dto';
import { NotificationService } from '../notifications/notification.service';
import { JwtService } from '@nestjs/jwt';
import { JwtPayload } from '../auth/auth.service';

@Injectable()
export class ChatService {
  constructor(
    private repository: ChatRepository,
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

  async createRoom(info: CreateRoomDto) {
    if (info.type === RoomType.PROTECTED || info.type === RoomType.PRIVATE) {
      if (!info.password) {
        throw new BadRequestException(
          'Password is required, for protected room',
        );
      }
    }
    // check if there is no other room with same name
    const room = await this.repository.getSimpleRoom({
      where: { name: info.name },
    });
    if (room) {
      throw new BadRequestException('Une salle avec ce nom existe déjà');
    }
    let hashedPassword = '';
    if (info.password) {
      hashedPassword = await argon.hash(info.password);
    }
    const data = {
      name: info.name,
      type: info.type,
      avatar: info.avatar ?? getRandomAvatarUrl(),
      password: info.type === RoomType.PUBLIC ? null : hashedPassword,
    };
    const ownerId = info.ownerId;
    return this.repository.createRoom({ data }, ownerId);
  }
  async addUserToARoom(info: {
    roomId: number;
    userId: number;
    password?: string;
  }) {
    const room = await this.getRoom({ roomId: info.roomId });
    if (!room) {
      throw new NotFoundException(`Salle de chat introuvable`);
    }

    // // private room can only be joined by invited user
    // if (room.type === RoomType.PRIVATE) {
    //   // only admin and owner can add member to private room
    //   this.checkIfCanActInTheRoom(actorId, room, [Role.OWNER, Role.ADMIN]);
    // }

    // need to provide the password if a room as a password
    if (room.password && !info.password) {
      throw new ForbiddenException(`Mot de passe requis`);
    } else if (room.password && info.password) {
      if (!(await argon.verify(room.password, info.password))) {
        throw new ForbiddenException(`Mot de passe incorrect`);
      }
    }
    // check if user is already a member
    room.members.forEach((member) => {
      if (member.memberId === info.userId) {
        throw new BadRequestException(`Vous êtes déjà membre de cette salle`);
      }
    });
    return this.addMemberToRoom(info.roomId, info.userId, Role.USER, room.name);
  }

  async addMemberToRoom(
    roomId: number,
    userId: number,
    role: Role,
    roomName: string,
  ): Promise<ChatRoomMember> {
    return this.repository
      .joinRoom(userId, roomId, role)
      .then((member) => {
        this.notificationService.sendNewMemberInRoom(userId, roomId, roomName);
        return member;
      })
      .catch(() => {
        throw new BadRequestException('Failed to add member to  room');
      });
  }

  // return true or throw error
  async canListenToRoom(roomId: number, userId: number) {
    try {
      const room = await this.getRoom({ roomId });
      if (room.type === RoomType.PRIVATE || room.type === RoomType.PROTECTED) {
        this.checkIfCanActInTheRoom(userId, room, [
          Role.OWNER,
          Role.ADMIN,
          Role.USER,
          Role.MUTED,
          Role.BAN,
        ]);
      }
      return true;
    } catch (e) {
      return false;
    }
  }

  // Return PUBLIC and PROTECTED rooms
  async getPublicRooms(): Promise<ChatRoomWithMembers[]> {
    return this.repository.getPublicRooms();
  }

  async sendMessageToRoom(roomId: number, content: string, senderId: number) {
    const room = await this.getRoom({ roomId });
    this.checkIfCanActInTheRoom(senderId, room, [
      Role.OWNER,
      Role.ADMIN,
      Role.USER,
    ]);
    return this.repository.createRoomMessage({
      data: {
        content,
        user: { connect: { id: senderId } },
        chatroom: { connect: { id: roomId } },
      },
    });
  }

  async setUserAsAdmin(roomId: number, userId: number, actorId: number) {
    const room = await this.getRoom({ roomId });
    const owner = this.checkIfCanActInTheRoom(actorId, room, [Role.OWNER]);
    if (owner.memberId === userId) {
      throw new BadRequestException('You cannot promote yourself');
    }
    const member = this.checkIfCanActInTheRoom(userId, room, [
      Role.MUTED,
      Role.BAN,
      Role.USER,
      Role.ADMIN,
    ]);

    return this.repository
      .updateChatRoomMember({
        where: { id: member.id },
        data: { role: Role.ADMIN },
      })
      .then((adminMember) => {
        this.notificationService.sendPromotedToAdmin(
          actorId,
          adminMember.memberId,
          roomId,
          room.name,
        );
        return adminMember;
      });
  }

  // actorId is the user who is trying to act
  async setUserAsMuted(
    roomId: number,
    userId: number,
    actorId: number,
  ): Promise<ChatRoomMember> {
    try {
      const room = await this.getRoom({ roomId });
      this.checkIfCanActInTheRoom(actorId, room, [Role.OWNER, Role.ADMIN]);
      const member = this.checkIfCanActInTheRoom(userId, room, [
        Role.MUTED,
        Role.BAN,
        Role.USER,
        Role.ADMIN,
      ]);
      return this.repository
        .updateChatRoomMember({
          where: { id: member.id },
          data: { role: Role.MUTED },
        })
        .then((mutedMember) => {
          this.notificationService.sendRoomRolesUpdated(
            actorId,
            mutedMember.memberId,
            roomId,
            room.name,
          );
          return mutedMember;
        });
    } catch (e) {
      throw new BadRequestException('Failed to mute user');
    }
  }

  async setUserAsMutedWithTime(
    roomId: number,
    userId: number,
    actorId: number,
    expireAt: number, // expiration time
  ): Promise<ChatRoomMember> {
    try {
      const room = await this.getRoom({ roomId });
      this.checkIfCanActInTheRoom(actorId, room, [Role.OWNER, Role.ADMIN]);
      const member = this.checkIfCanActInTheRoom(userId, room, [
        Role.MUTED,
        Role.BAN,
        Role.USER,
        Role.ADMIN,
      ]);
      return this.repository
        .updateChatRoomMember({
          where: { id: member.id },
          data: { role: Role.MUTED, unMuteAt: new Date(expireAt) },
        })
        .then((mutedMember) => {
          this.notificationService.sendRoomRolesUpdated(
            actorId,
            mutedMember.memberId,
            roomId,
            room.name,
          );
          return mutedMember;
        });
    } catch (e) {
      throw new BadRequestException('Failed to mute user');
    }
  }

  async setUserAsBanned(roomId: number, userId: number, actorId: number) {
    const room = await this.getRoom({ roomId });
    this.checkIfCanActInTheRoom(actorId, room, [Role.OWNER, Role.ADMIN]);
    const member = this.checkIfCanActInTheRoom(userId, room, [
      Role.MUTED,
      Role.BAN,
      Role.USER,
    ]);
    return this.repository
      .updateChatRoomMember({
        where: { id: member.id },
        data: { role: Role.BAN },
      })
      .then((bannedMember) => {
        this.notificationService.sendRoomRolesUpdated(
          actorId,
          bannedMember.memberId,
          roomId,
          room.name,
        );
        return bannedMember;
      });
  }

  // Failed if user is not a member, if not owner/admin acting, or owner try to set himself as user
  async setUserAsUser(roomId: number, userId: number, actorId: number) {
    try {
      const room = await this.getRoom({ roomId });
      this.checkIfCanActInTheRoom(actorId, room, [Role.OWNER, Role.ADMIN]);
      const member = this.checkIfCanActInTheRoom(userId, room, [
        Role.MUTED,
        Role.BAN,
        Role.USER,
        Role.ADMIN,
      ]);
      this.notificationService.sendRoomRolesUpdated(
        actorId,
        member.memberId,
        roomId,
        room.name,
      );
      return this.repository.updateChatRoomMember({
        where: { id: member.id },
        data: { role: Role.USER },
      });
    } catch (e) {
      throw new Error('Failed to set user as user');
    }
  }

  async changeMemberRole(roomId: number, info: UpdateRoleDto, actorId: number) {
    switch (info.role) {
      case Role.USER:
        return this.setUserAsUser(roomId, info.userId, actorId);
      case Role.ADMIN:
        return this.setUserAsAdmin(roomId, info.userId, actorId);
      case Role.MUTED:
        if (info.expireAt) {
          return this.setUserAsMutedWithTime(
            roomId,
            info.userId,
            actorId,
            info.expireAt,
          );
        }
        return this.setUserAsMuted(roomId, info.userId, actorId);
      case Role.BAN:
        return this.setUserAsBanned(roomId, info.userId, actorId);
      default:
        throw new BadRequestException('Invalid role');
    }
  }

  async removeUserFromRoom(roomId: number, userId: number, actorId: number) {
    const room = await this.getRoom({ roomId });
    const owner = this.checkIfCanActInTheRoom(actorId, room, [
      Role.OWNER,
      Role.ADMIN,
    ]);
    if (owner.memberId === userId) {
      throw new ForbiddenException('You cannot remove yourself');
    }
    const member = this.checkIfCanActInTheRoom(userId, room, [
      Role.MUTED,
      Role.BAN,
      Role.USER,
      Role.ADMIN,
    ]);
    return this.repository
      .deleteMemberFromRoom(member.id)
      .then((deletedMember) => {
        this.notificationService.sendRemovedFromRoom(
          userId,
          deletedMember.memberId,
          roomId,
          room.name,
        );
        return deletedMember;
      });
  }

  async removeMyselfFromRoom(roomId: number, userId: number) {
    const room = await this.getRoom({ roomId });
    const member = this.checkIfCanActInTheRoom(userId, room, [
      Role.ADMIN,
      Role.OWNER,
      Role.USER,
      Role.MUTED,
      Role.BAN,
    ]);
    if (member.role === Role.OWNER) {
      return this.specialSelfDeleteForOwner(roomId, member, room);
    }
    return this.repository
      .deleteMemberFromRoom(member.id)
      .then((deletedMember) => {
        this.notificationService.sendRemovedFromRoom(
          userId,
          deletedMember.memberId,
          roomId,
          room.name,
        );
        return deletedMember;
      });
  }

  async specialSelfDeleteForOwner(
    roomId: number,
    owner: ChatRoomMember,
    room: ChatRoomWithMembers,
  ) {
    // check if any admin is in the room first, then a regular user left to promote as owner
    const newOwner = await this.repository.findPotentialNewOwner(roomId);
    // if no other member is found, delete the room
    if (!newOwner) return this.deleteRoom(roomId, owner.memberId, room);
    await this.repository.deleteMemberFromRoom(owner.id);
    await this.repository
      .updateChatRoomMember({
        where: { id: newOwner.id },
        data: { role: Role.OWNER },
      })
      .then((newOwner) => {
        this.notificationService.sendPromotedToAdmin(
          owner.memberId,
          newOwner.memberId,
          roomId,
          room.name,
        );
      });
    return owner;
  }

  async deleteRoom(roomId: number, userId: number, room?: ChatRoomWithMembers) {
    if (!room) {
      room = await this.getRoom({ roomId });
    }
    this.checkIfCanActInTheRoom(userId, room, [Role.OWNER]);
    this.notificationService.sendRoomDeleted(userId, roomId, room.name);
    return this.repository.deleteRoom(roomId);
  }

  // Return all messages of a room, only if the user is a member, Banned can't see messages
  async getRoomMessages(
    roomId: number,
    userId: number,
    info: { skip?: number; take?: number },
  ) {
    const room = await this.getRoom({ roomId });
    if (room.type === RoomType.PUBLIC) {
      return this.repository.getRoomMessages(roomId, {
        skip: info.skip,
        take: info.take,
      });
    }
    this.checkIfCanActInTheRoom(userId, room, [
      Role.OWNER,
      Role.ADMIN,
      Role.USER,
      Role.MUTED,
    ]);
    return this.repository.getRoomMessages(roomId, {
      skip: info.skip,
      take: info.take,
    });
  }

  //  Return all members of a room (including banned and muted), for private only if the user is a member
  async getRoomMembers(roomId: number, userId: number) {
    const room = await this.getRoom({ roomId });
    if (room.type === RoomType.PRIVATE) {
      this.checkIfCanActInTheRoom(userId, room, [
        Role.OWNER,
        Role.ADMIN,
        Role.USER,
        Role.MUTED,
        Role.BAN,
      ]);
    }
    await this.unMuteAllWaitingMutedUsers(room);
    return this.repository.getChatRoomMembers(roomId);
  }

  async checkUserMembership(
    roomId: number,
    userId: number,
  ): Promise<{ state: boolean; role: Role | null; room?: ChatRoom }> {
    const room = await this.repository.getSimpleRoom({ where: { id: roomId } });
    const member = await this.repository.getChatRoomMember(userId, roomId);
    if (member) {
      return { state: true, role: member.role, room };
    } else {
      return { state: false, role: null, room };
    }
  }

  async getUserRooms(userId: number) {
    return this.repository.getMemberRooms(userId);
  }

  async changeChatAvatar(roomId: number, userId: number, url: string) {
    const room = await this.getRoom({ roomId });
    this.checkIfCanActInTheRoom(userId, room, [Role.OWNER, Role.ADMIN]);
    this.notificationService.sendRoomSettingsUpdated(roomId, room.name);
    return this.repository.updateRoom({
      where: { id: roomId },
      data: { avatar: url },
    });
  }

  async updateRoomPassword(data: UpdatePasswordDto, userId: number) {
    const { roomId, password } = data;
    const room = await this.getRoom({ roomId });
    this.checkIfCanActInTheRoom(userId, room, [Role.OWNER, Role.ADMIN]);
    const hashedPassword = await argon.hash(password);
    return this.repository.updateRoom({
      where: { id: roomId },
      data: { password: hashedPassword },
    });
  }

  async updateRoomInfo(data: UpdateRoomInfoDto, userId: number) {
    const { roomId, roomType } = data;
    const room = await this.getRoom({ roomId });
    this.checkIfCanActInTheRoom(userId, room, [Role.OWNER, Role.ADMIN]);
    if (roomType === RoomType.PROTECTED || roomType === RoomType.PRIVATE) {
      return this.updateToPrivateOrProtected(room, data);
    } else {
      return this.updateToPublic(room, data);
    }
  }
  async updateToPublic(room: ChatRoomWithMembers, data: UpdateRoomInfoDto) {
    // const { oldPassword } = data;
    // can be move if we don't want to check old
    // if (room.password?.length && oldPassword) {
    //   if (!(await argon.verify(room.password, oldPassword))) {
    //     throw new ForbiddenException(`Mot de passe incorrect`);
    //   }
    // }
    return this.repository.updateRoom({
      where: { id: room.id },
      data: {
        type: RoomType.PUBLIC,
        password: null,
      },
    });
  }
  async updateToPrivateOrProtected(
    room: ChatRoomWithMembers,
    data: UpdateRoomInfoDto,
  ) {
    const { roomType, password } = data;
    let hashedPassword = '';
    // if (!oldPassword && room.password?.length > 0) {
    //   throw new BadRequestException('Mot de passe requis');
    // }

    // can be move if we don't want to check old
    // if (room.password?.length && oldPassword) {
    //   if (!(await argon.verify(room.password, oldPassword))) {
    //     throw new ForbiddenException(`Mot de passe incorrect`);
    //   }
    // }

    if (!password) {
      throw new BadRequestException('Mot de passe requis pour ce type de room');
    }
    hashedPassword = await argon.hash(password);
    return this.repository.updateRoom({
      where: { id: room.id },
      data: {
        type: roomType,
        password: hashedPassword,
      },
    });
  }

  async inviteUserToRoom(roomId: number, userId: number, actor: UserWithData) {
    const room = await this.getRoom({ roomId });
    this.checkIfCanActInTheRoom(actor.id, room, [
      Role.OWNER,
      Role.ADMIN,
      Role.USER,
      Role.MUTED,
    ]);
    // check if user is already a member
    room.members.forEach((member) => {
      if (member.memberId === userId) {
        throw new BadRequestException(`Il est déjà membre de cette salle`);
      }
    });
    this.notificationService.sendRoomInvitation(
      actor,
      userId,
      roomId,
      room.name,
    );
  }

  /* utility functions */

  /*
   * Try to find a room by id or name
   */
  async getRoom(info: {
    roomId?: number;
    name?: string;
  }): Promise<ChatRoomWithMembers> {
    try {
      return await this.repository.getRoom({
        where: {
          id: info.roomId,
          name: info.name,
        },
      });
    } catch (e) {
      throw new NotFoundException('Room not found');
    }
  }

  // unMute all users that are muted and the time is up
  async unMuteAllWaitingMutedUsers(room: ChatRoomWithMembers) {
    const now = new Date().getTime();
    const toUnMuteMembers = room.members.filter((member) => {
      if (member.role === Role.MUTED && member.unMuteAt) {
        return member.unMuteAt.getTime() < now;
      }
    });
    if (toUnMuteMembers.length > 0) {
      await this.repository.updateManyChatRoomMembers({
        where: { id: { in: toUnMuteMembers.map((m) => m.id) } },
        data: { role: Role.USER, unMuteAt: new Date() },
      });
      toUnMuteMembers.forEach((member) => {
        this.notificationService.sendRoomRolesUpdated(
          member.memberId,
          member.memberId,
          member.chatroomId,
          'room',
        );
      });
    }
  }

  /*
   * Check if the user can act in the room, if not throw error
   * return the member object
   * @param actorId the user who is trying to act
   * @param chatRoom the room where the user is trying to act
   * @param grantedRoles the roles that are allowed to act
   */
  checkIfCanActInTheRoom(
    actorId: number,
    chatRoom: ChatRoomWithMembers,
    grantedRoles: Role[],
  ) {
    const member = chatRoom.members.find((m) => m.memberId === actorId);
    if (!member) {
      throw new BadRequestException(`Vous n'êtes pas membre de cette salle`);
    }
    if (!grantedRoles.includes(member.role)) {
      throw new ForbiddenException(`Vous n'avez pas la permission, ou le rôle`);
    }
    return member;
  }
}
