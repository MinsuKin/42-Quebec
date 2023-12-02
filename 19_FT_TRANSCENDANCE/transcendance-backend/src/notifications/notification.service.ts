import { Injectable, Logger } from '@nestjs/common';
import { NotificationRepository } from './notification.repository';
import { Notification, NotificationType, User, Game } from '@prisma/client';
import { NotificationGateway } from './notification.gateway';

export enum NotificationTitle {
  // Game Events
  JoinedGame = 'Joined Game', // new viewer joined the game
  GameInvitation = 'Game Invitation', // player invited another player to a game, challenge
  GameInvitationRejected = 'Challenge Rejected', // player rejected the invitation
  FriendRequest = 'Friend Request', // player sent a friend request to another player
  FriendRequestAccepted = 'Friend Request Accepted', // player accepted the friend request
  FriendRequestRejected = 'Friend Request Rejected', // player rejected the friend request
  MemberJoinedChatRoom = 'Member Joined Chat Room', // new member joined the chat room
  RemovedFromChatRoom = 'Removed From Chat Room', // player kicked from a chat room
  PromotedToAdmin = 'Promoted To Admin', // player promoted to admin in a chat room
  PrivateChatInvitation = 'Private Chat Invitation', // player invited another player to a join
}

// Notification Types for real time notifications
export enum RealTimeNotificationType {
  Game = 'Game',
  GameWaitingQue = 'GameWaitingQue',
  ChatRoom = 'ChatRoom',
  PrivateMessage = 'PrivateMessage',
}

export enum RealTimeNotificationTitle {
  GameStarted = 'Game Started',
  GameEnded = 'Game Ended',
  GameMatched = 'Game Matched', // player left the que and is matched with another player
  NewPlayerInQue = 'New Player In Que', // player joined the que
  PlayerLeftQue = 'Player Left Que', // player left the que
  NewMemberInChatRoom = 'New Member In Chat Room', // new member joined the chat room
  NewRolesInChatRoom = 'New Roles In Chat Room', // new roles assigned to chat room
  RemovedFromChatRoom = 'Removed From Chat Room', // player kicked from a chat room
  ChatRoomDeleted = 'Chat Room Deleted', // chat room deleted
  ChatRoomSettingsUpdated = 'Chat Room Settings Updated', // chat room settings updated
  NewMpMessage = 'New Mp-Message', // first message between two contacts
  BlockedContactMessage = 'Blocked Contact', // One of the contacts blocked or unblocked the other
  BrokenFriendship = 'Broken Friendship', // One of the contacts unfriended the other, or blocked
}

export interface RealTimeNotification {
  mode: 'general' | 'private';
  sourceUserId?: number; // Optional: Only required for 'private' type
  userId?: number; // Optional: Only required for 'private' type
  roomId?: number; // Optional: Only required for 'private' type
  gameId?: number; // Optional: Only required for 'game' type
  waitingGameId?: number; // Optional: Only required for invitation to games
  type: RealTimeNotificationType;
  title: RealTimeNotificationTitle;
  message: string;
  timestamp: number;
}

@Injectable()
export class NotificationService {
  private readonly logger = new Logger(NotificationService.name);
  constructor(
    private readonly notificationRepository: NotificationRepository,
    private readonly notificationGateway: NotificationGateway,
  ) {}

  // for normal notifications (with persistence in database)
  private async createNotification(
    userId: User['id'], // person to send notification to
    type: NotificationType,
    title: NotificationTitle,
    message: string,
    referenceId: number,
    expiresAt?: Date,
  ): Promise<void> {
    const notificationData = {
      user: { connect: { id: userId } },
      type,
      title,
      message,
      referenceId,
      expiresAt,
    };
    this.notificationRepository
      .createNotification(notificationData)
      .then((notification) => {
        this.notificationGateway.sendNotificationToUser(userId, notification);
      })
      .catch((e) => {
        this.logger.log("Notification couldn't be created", e);
      });
  }

  async getNotificationsForUser(userId: number): Promise<Notification[]> {
    return this.notificationRepository.getNotificationsForUser(userId);
  }

  async markNotificationAsRead(notificationId: number): Promise<Notification> {
    return this.notificationRepository.markNotificationAsRead(notificationId);
  }

  async deleteNotification(notificationId: number): Promise<Notification> {
    return this.notificationRepository.deleteNotification(notificationId);
  }

  private createRealTimeNotification(
    mode: 'general' | 'private',
    type: RealTimeNotificationType,
    title: RealTimeNotificationTitle,
    message: string,
    sourceUserId?: number,
    userId?: number,
    roomId?: number,
    gameId?: number,
  ): RealTimeNotification {
    return {
      mode,
      sourceUserId,
      userId,
      roomId,
      gameId,
      type,
      title,
      message,
      timestamp: Date.now(),
    };
  }

  private sendRealTimeNotificationToUser(
    userId: number,
    notification: RealTimeNotification,
  ): void {
    this.notificationGateway.sendRealTimeNotificationToUser(
      userId,
      notification,
    );
  }

  private sendRealTimeNotificationToRoomMembers(
    roomId: number,
    notification: RealTimeNotification,
  ): void {
    this.notificationGateway.sendRealTimeNotificationToRoomMembers(
      roomId,
      notification,
    );
  }

  private sendGeneralRealTimeNotification(
    notification: RealTimeNotification,
  ): void {
    this.notificationGateway.sendGeneralRealTimeNotification(notification);
  }

  async sendFriendRequest(sender: User, receiverId: User[`id`]): Promise<void> {
    const message = `Tu as reçu une demande d'ami de  @${sender.username}`;
    return this.createNotification(
      receiverId,
      NotificationType.FRIEND_REQUEST,
      NotificationTitle.FriendRequest,
      message,
      sender.id,
    );
  }

  async sendFriendRequestApproved(
    sender: User,
    receiverId: User[`id`],
  ): Promise<void> {
    const message = `Ta demande d'amis à @${sender.username} été accepter`;
    return this.createNotification(
      receiverId,
      NotificationType.FRIEND_REQUEST,
      NotificationTitle.FriendRequestAccepted,
      message,
      sender.id,
    );
  }

  async sendFriendRequestRejected(
    sender: User,
    receiverId: User[`id`],
  ): Promise<void> {
    const message = `Ta demande d'amis à @${sender.username} été rejeter`;
    return this.createNotification(
      receiverId,
      NotificationType.FRIEND_REQUEST,
      NotificationTitle.FriendRequestRejected,
      message,
      sender.id,
    );
  }

  async sendBrokenFriendship(
    sender: User,
    receiverId: User[`id`],
  ): Promise<void> {
    const message = `Tu n'est plus amis avec @${sender.username}`;
    const realTimeNotification = this.createRealTimeNotification(
      'private',
      RealTimeNotificationType.PrivateMessage,
      RealTimeNotificationTitle.BrokenFriendship,
      message,
      sender.id,
      receiverId,
    );
    this.sendRealTimeNotificationToUser(receiverId, realTimeNotification);
  }

  async sendBlockedStatusChanged(
    sender: User,
    receiverId: User[`id`],
    blocked: boolean,
  ): Promise<void> {
    const message = `Tu ${blocked ? 'as bloqué' : 'as débloqué'} @${
      sender.username
    }`;
    const realTimeNotification = this.createRealTimeNotification(
      'private',
      RealTimeNotificationType.PrivateMessage,
      RealTimeNotificationTitle.BlockedContactMessage,
      message,
      sender.id,
      receiverId,
    );
    this.sendRealTimeNotificationToUser(receiverId, realTimeNotification);
    this.sendRealTimeNotificationToUser(sender.id, realTimeNotification);
  }

  async sendNewMemberInRoom(
    senderId: User[`id`],
    roomId: number,
    roomName: string,
  ): Promise<void> {
    const message = `Vous avez été ajouté à la salle de chat ${roomName}`;
    const realTimeNotification = this.createRealTimeNotification(
      'private',
      RealTimeNotificationType.ChatRoom,
      RealTimeNotificationTitle.NewMemberInChatRoom,
      message,
      senderId,
      undefined,
      roomId,
    );
    this.sendRealTimeNotificationToRoomMembers(roomId, realTimeNotification);
    await this.createNotification(
      senderId,
      NotificationType.PRIVATE_MESSAGE,
      NotificationTitle.MemberJoinedChatRoom,
      message,
      roomId,
    );
  }
  async sendPromotedToAdmin(
    senderId: User[`id`],
    promotedUserId: User[`id`],
    roomId: number,
    roomName: string,
  ) {
    const realTimeNotification = this.createRealTimeNotification(
      'private',
      RealTimeNotificationType.ChatRoom,
      RealTimeNotificationTitle.NewRolesInChatRoom,
      `${promotedUserId} a été promu administrateur de la salle de chat ${roomName}`,
      senderId,
      promotedUserId,
      roomId,
    );
    this.sendRealTimeNotificationToRoomMembers(roomId, realTimeNotification);
    await this.createNotification(
      senderId,
      NotificationType.PRIVATE_MESSAGE,
      NotificationTitle.PromotedToAdmin,
      `Vous avez été promu administrateur de la salle de chat ${roomName}`,
      roomId,
    );
  }

  sendRoomRolesUpdated(
    senderId: User[`id`],
    targetUserId: User[`id`],
    roomId: number,
    roomName: string,
  ) {
    const message = `Les rôles de la salle de chat ${roomName} ont été mis à jour`;
    const realTimeNotification = this.createRealTimeNotification(
      'private',
      RealTimeNotificationType.ChatRoom,
      RealTimeNotificationTitle.NewRolesInChatRoom,
      message,
      senderId,
      targetUserId,
      roomId,
    );
    this.sendRealTimeNotificationToRoomMembers(roomId, realTimeNotification);
  }

  async sendRemovedFromRoom(
    senderId: User[`id`],
    removedUserId: User[`id`],
    roomId: number,
    roomName: string,
  ) {
    const realTimeNotification = this.createRealTimeNotification(
      'private',
      RealTimeNotificationType.ChatRoom,
      RealTimeNotificationTitle.RemovedFromChatRoom,
      `${removedUserId} été retiré de la salle de chat ${roomName}`,
      senderId,
      removedUserId,
      roomId,
    );
    this.sendRealTimeNotificationToRoomMembers(roomId, realTimeNotification);
    await this.createNotification(
      removedUserId,
      NotificationType.PRIVATE_MESSAGE,
      NotificationTitle.RemovedFromChatRoom,
      `Vous avez été retiré de la salle de chat ${roomName}`,
      roomId,
    );
  }

  sendRoomDeleted(senderId: User[`id`], roomId: number, roomName: string) {
    const message = `La salle de chat ${roomName} a été supprimée`;
    const realTimeNotification = this.createRealTimeNotification(
      'private',
      RealTimeNotificationType.ChatRoom,
      RealTimeNotificationTitle.ChatRoomDeleted,
      message,
      senderId,
      undefined,
      roomId,
    );
    this.sendRealTimeNotificationToRoomMembers(roomId, realTimeNotification);
  }

  sendRoomSettingsUpdated(roomId: number, roomName: string) {
    const message = `Les paramètres de la salle de chat ${roomName} ont été mis à jour`;
    const realTimeNotification = this.createRealTimeNotification(
      'general',
      RealTimeNotificationType.ChatRoom,
      RealTimeNotificationTitle.ChatRoomSettingsUpdated,
      message,
      undefined,
      undefined,
      roomId,
    );
    this.sendGeneralRealTimeNotification(realTimeNotification);
  }

  async sendRoomInvitation(
    sender: User,
    receiverId: User[`id`],
    roomId: number,
    roomName: string,
  ) {
    const message = `Tu as été invité par ${sender.username} à rejoindre la salle de chat ${roomName}`;
    await this.createNotification(
      receiverId,
      NotificationType.PRIVATE_MESSAGE,
      NotificationTitle.PrivateChatInvitation,
      message,
      roomId,
    );
  }

  // two players have been matched and removed from the que
  sendMatchedGame(
    senderId: User[`id`],
    senderUsername: User[`username`],
    receiverId: User[`id`],
    receiverUsername: User[`username`],
    gameId: Game[`id`],
  ) {
    const message = `File d'attente, ${receiverUsername} a été matché avec @${senderUsername}`;
    const realTimeNotification = this.createRealTimeNotification(
      'general',
      RealTimeNotificationType.GameWaitingQue,
      RealTimeNotificationTitle.GameMatched,
      message,
      senderId,
      receiverId,
      undefined,
      gameId,
    );
    this.sendGeneralRealTimeNotification(realTimeNotification);
  }

  sendNewPlayerInQue(senderId: User[`id`], senderUsername: User[`username`]) {
    const message = `File d'attente, ${senderUsername} a rejoint la file d'attente`;
    const realTimeNotification = this.createRealTimeNotification(
      'general',
      RealTimeNotificationType.GameWaitingQue,
      RealTimeNotificationTitle.NewPlayerInQue,
      message,
      senderId,
      undefined,
      undefined,
      undefined,
    );
    this.sendGeneralRealTimeNotification(realTimeNotification);
  }

  sendPlayerLeftQue(senderId: User[`id`], senderUsername: User[`username`]) {
    const message = `File d'attente, ${senderUsername} a quitté la file d'attente`;
    const realTimeNotification = this.createRealTimeNotification(
      'general',
      RealTimeNotificationType.GameWaitingQue,
      RealTimeNotificationTitle.PlayerLeftQue,
      message,
      senderId,
      undefined,
      undefined,
      undefined,
    );
    this.sendGeneralRealTimeNotification(realTimeNotification);
  }

  sendGameStarted(
    senderId: User[`id`],
    senderUsername: User[`username`],
    receiverId: User[`id`],
    gameId: Game[`id`],
  ) {
    const message = `Le jeu a commencé, contre ${senderUsername}`;
    const realTimeNotification = this.createRealTimeNotification(
      'general',
      RealTimeNotificationType.Game,
      RealTimeNotificationTitle.GameStarted,
      message,
      senderId,
      receiverId,
      undefined,
      gameId,
    );
    this.sendGeneralRealTimeNotification(realTimeNotification);
  }

  async sendGameInvitation(
    senderUsername: User[`username`],
    receiverId: User[`id`],
    waitingGameId: number,
  ) {
    const message = `Tu as été invité à jouer par ${senderUsername}`;
    await this.createNotification(
      receiverId,
      NotificationType.GAME_INVITE,
      NotificationTitle.GameInvitation,
      message,
      waitingGameId,
    );
  }

  async sendGameInvitationRejected(
    senderUsername: User[`username`],
    receiverId: User[`id`],
    waitingGameId: number,
  ) {
    const message = `${senderUsername} a refusé ton invitation`;
    await this.createNotification(
      receiverId,
      NotificationType.GAME_INVITE,
      NotificationTitle.GameInvitationRejected,
      message,
      waitingGameId,
    );
  }

  async sendJoinedGame(
    receiverId: User[`id`],
    senderUsername: User[`username`],
    gameId: number,
  ) {
    const message = `${senderUsername} a rejoint votre jeu`;
    await this.createNotification(
      receiverId,
      NotificationType.GAME_EVENT,
      NotificationTitle.JoinedGame,
      message,
      gameId,
    );
  }

  sendGameEnded(gameId: number) {
    const realTimeNotification = this.createRealTimeNotification(
      'general',
      RealTimeNotificationType.Game,
      RealTimeNotificationTitle.GameEnded,
      `La partie est terminé`,
      undefined,
      undefined,
      undefined,
      gameId,
    );
    this.sendGeneralRealTimeNotification(realTimeNotification);
  }
}
