import { BadRequestException, Injectable } from '@nestjs/common';
import {
  ContactRequestWithReceiver,
  ContactRequestWithSender,
  FriendsRepository,
} from './friends.repository';
import { Contact, User } from '@prisma/client';
import { NotificationService } from '../notifications/notification.service';

export enum FriendshipStatus {
  Friends = 'friends',
  Pending = 'pending',
  NeedApproval = 'needApproval',
  None = 'none',
}

@Injectable()
export class FriendsService {
  constructor(
    private repository: FriendsRepository,
    private notificationService: NotificationService,
  ) {}
  async getFriends(userId: number) {
    return this.repository.getFriends(userId);
  }

  async checkFriend(
    userId: number,
    friendId: number,
  ): Promise<{
    status: FriendshipStatus;
    data:
      | Contact
      | ContactRequestWithSender
      | ContactRequestWithReceiver
      | null;
  }> {
    const friend = await this.repository.getFriend(userId, friendId);
    if (!friend) {
      // check for pending request userId sent to friendId
      const requestSent = await this.checkIfRequestWasSent(userId, friendId);
      if (requestSent) {
        return {
          status: FriendshipStatus.Pending,
          data: requestSent,
        };
      }
      // check for pending request friendId sent to userId
      const requestReceived = await this.checkIfRequestWasReceived(
        userId,
        friendId,
      );
      if (requestReceived) {
        return {
          status: FriendshipStatus.NeedApproval,
          data: requestReceived,
        };
      }
      return {
        status: FriendshipStatus.None,
        data: null,
      };
    }
    return {
      status: FriendshipStatus.Friends,
      data: friend,
    };
  }

  async checkIfRequestWasSent(
    userId: number,
    friendId: number,
  ): Promise<ContactRequestWithReceiver | null> {
    const allRequestSent = await this.repository.getSentFriendRequests(userId);
    return allRequestSent.find((r) => r.receiverId === friendId);
  }

  async checkIfRequestWasReceived(
    userId: number,
    friendId: number,
  ): Promise<ContactRequestWithSender | null> {
    const requestReceived = await this.repository.getReceivedFriendRequests(
      userId,
    );
    return requestReceived.find((r) => r.senderId === friendId);
  }

  async getSentFriendRequests(userId: number) {
    return this.repository.getSentFriendRequests(userId);
  }
  async getReceivedFriendRequests(userId: number) {
    return this.repository.getReceivedFriendRequests(userId);
  }
  async removeFriend(user: User, friendId: number) {
    await this.repository.removeFriend(user.id, friendId);
    await this.notificationService.sendBrokenFriendship(user, friendId);
  }
  async removeRequest(userId: number, friendId: number) {
    return this.repository.removeRequest(userId, friendId);
  }
  async addFriendRequest(user: User, friendId: number) {
    const friend = await this.repository.getFriend(user.id, friendId);
    if (friend) throw new BadRequestException('Already friends');
    const contactRequest = await this.repository.addFriendRequest(
      user.id,
      friendId,
    );
    await this.notificationService.sendFriendRequest(user, friendId);
    return contactRequest;
  }
  async cancelFriendRequest(requestId: number) {
    return this.repository.cancelFriendRequest(requestId);
  }
  async approveFriendRequest(user: User, requestId: number) {
    const request = await this.repository.approveFriendRequest(requestId);
    await this.notificationService.sendFriendRequestApproved(
      user,
      request.userId,
    );
    return request;
  }
  async rejectFriendRequest(user: User, requestId: number) {
    const request = await this.repository.rejectFriendRequest(requestId);
    await this.notificationService.sendFriendRequestRejected(
      user,
      request.senderId,
    );
    return request;
  }

  async blockUser(user: User, blockedUserId: User['id']) {
    try {
      await this.removeRequest(user.id, blockedUserId);
      await this.removeFriend(user, blockedUserId);
      return this.repository.blockUser(user.id, blockedUserId);
    } catch (e) {
      throw new BadRequestException("Can't block user");
    }
  }
  async unblockUser(user: User, blockedUserId: number) {
    return this.repository.unblockUser(user.id, blockedUserId).then((res) => {
      if (res) {
        this.notificationService.sendBlockedStatusChanged(
          user,
          blockedUserId,
          false,
        );
        return res;
      } else {
        throw new BadRequestException("Can't unblock user");
      }
    });
  }
}
