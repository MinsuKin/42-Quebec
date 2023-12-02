import { Injectable } from '@nestjs/common';
import { User } from '@prisma/client';
import { UsersService } from '../users/users.service';
import { ChatService } from '../messages/chat.service';
import { ChatRoomWithMembers } from '../messages/chat.repository';

@Injectable()
export class FilesService {
  constructor(
    private usersService: UsersService,
    private chatService: ChatService,
  ) {}
  updateAvatarUrl(fileName: string, user: User) {
    const serverBaseUrl = '';
    const fileUrl = `${serverBaseUrl}/uploads/${fileName}`;
    return this.usersService.updateProfile({
      where: { userId: user.id },
      data: {
        avatar: fileUrl,
      },
      include: {
        awards: true,
      },
    });
  }
  updateChatRoomAvatar(
    fileName: string,
    roomId: number,
    source: User,
  ): Promise<ChatRoomWithMembers> {
    const serverBaseUrl = '';
    const fileUrl = `${serverBaseUrl}/uploads/room/${fileName}`;
    return this.chatService.changeChatAvatar(roomId, source.id, fileUrl);
  }

  deleteCurrentUserAvatar(user: User) {
    return this.usersService.updateProfile({
      where: {
        userId: user.id,
      },
      data: {
        avatar: this.getRandomAvatarUrl(),
      },
    });
  }

  getRandomAvatarUrl(): string {
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
}
