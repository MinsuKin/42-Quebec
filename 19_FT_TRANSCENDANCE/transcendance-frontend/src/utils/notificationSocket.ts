import { io, Socket } from 'socket.io-client'

export enum NotificationType {
  GAME_INVITE = 'GAME_INVITE',
  FRIEND_REQUEST = 'FRIEND_REQUEST',
  GAME_EVENT = 'GAME_EVENT',
  PRIVATE_MESSAGE = 'PRIVATE_MESSAGE'
}
export enum NotificationStatus {
  UNREAD = 'UNREAD',
  READ = 'READ'
}

export enum NotificationTitle {
  JoinedGame = 'Joined Game', // new viewer joined the game
  GameInvitation = 'Game Invitation', // player invited another player to a game, challenge
  GameInvitationRejected = 'Challenge Rejected', // player rejected the invitation
  FriendRequest = 'Friend Request', // player sent a friend request to another player
  FriendRequestAccepted = 'Friend Request Accepted', // player accepted the friend request
  FriendRequestRejected = 'Friend Request Rejected', // player rejected the friend request
  MemberJoinedChatRoom = 'Member Joined Chat Room', // new member joined the chat room
  RemovedFromChatRoom = 'Removed From Chat Room', // player kicked from a chat room
  PromotedToAdmin = 'Promoted To Admin', // player promoted to admin in a chat room
  PrivateChatInvitation = 'Private Chat Invitation' // player invited another player to a join
}

// Notification Types for real time notifications
export enum RealTimeNotificationType {
  Game = 'Game',
  GameWaitingQue = 'GameWaitingQue',
  ChatRoom = 'ChatRoom',
  PrivateMessage = 'PrivateMessage'
}

export enum RealTimeNotificationTitle {
  GameStarted = 'Game Started',
  GameEnded = 'Game Ended',
  GameMatched = 'Game Matched', // player left the que and is matched with another player
  NewPlayerInQue = 'New Player In Que', // player joined the que
  PlayerLeftQue = 'Player Left Que', // player left the que
  NewMemberInChatRoom = 'New Member In Chat Room', // new member joined the chat room
  NewRolesInChatRoom = 'New Roles In Chat Room', // new roles assigned to chat room
  RemovedFromChatRoom = 'Removed From Chat Room',
  ChatRoomDeleted = 'Chat Room Deleted', // chat room deleted
  ChatRoomSettingsUpdated = 'Chat Room Settings Updated', // chat room settings updated
  NewMpMessage = 'New Mp-Message', // first message between two contacts
  BlockedContactMessage = 'Blocked Contact', // One of the contacts blocked or unblocked the other
  BrokenFriendship = 'Broken Friendship' // One of the contacts unfriended the other, or blocked
}

export interface Notification {
  id: number
  userId: number
  type: NotificationType
  status: NotificationStatus
  title: NotificationTitle
  message: string
  referenceId: number
  createdAt: string
  updatedAt: string
  expiresAt: string
}

export interface RealTimeNotification {
  mode: 'general' | 'private'
  sourceUserId?: number
  userId?: number
  roomId?: number
  gameId?: number
  waitingGameId?: number
  type: RealTimeNotificationType
  title: RealTimeNotificationTitle
  message: string
  timestamp: number
}

interface ListenEvents {
  notification: (data: Notification) => void
  'realtime-notification': (data: RealTimeNotification) => void
}

interface EmitEvents {
  join: (room: string) => void
  'join-room': (roomId: number) => void
  'leave-room': (roomId: number) => void
}
export class NotificationSocket {
  private static instance: NotificationSocket
  socket: Socket<ListenEvents, EmitEvents> | undefined
  public operational: boolean = false
  private constructor(
    userId: number,
    public onNotification: (data: Notification) => void,
    public onRealTimeNotification: (data: RealTimeNotification) => void,
    token: string
  ) {
    try {
      this.socket = io('/notification', {
        path: '/socket.io/',
        query: { userId },
        auth: { token: token }
      })
      this.socket.on('connect', () => {
        this.socket?.emit('join', userId.toString())
      })
      this.socket.on('notification', this.onNotification)
      this.socket.on('realtime-notification', this.onRealTimeNotification)
    } catch (e) {
      console.error(e)
    } finally {
      this.operational = true
    }
  }
  public static getInstance(
    userId: number,
    onNotification: (data: Notification) => void,
    onRealTimeNotification: (data: RealTimeNotification) => void,
    token: string
  ): NotificationSocket {
    if (!NotificationSocket.instance) {
      NotificationSocket.instance = new NotificationSocket(
        userId,
        onNotification,
        onRealTimeNotification,
        token
      )
    }
    NotificationSocket.instance.onNotification = onNotification
    NotificationSocket.instance.onRealTimeNotification = onRealTimeNotification
    return NotificationSocket.instance
  }

  listenToRoomNotifications(roomId: number) {
    this.socket?.emit('join-room', roomId)
  }
  leaveRoomNotifications(roomId: number) {
    this.socket?.emit('leave-room', roomId)
  }

  disconnect() {
    if (this.socket) {
      this.socket.disconnect()
    }
    this.operational = false
  }

  static destroyInstance() {
    if (NotificationSocket.instance) {
      NotificationSocket.instance.disconnect()
      // @ts-expect-error - private property
      NotificationSocket.instance = undefined
    }
  }

  connect() {
    if (this.socket) {
      if (this.socket.disconnected) {
        this.socket.connect()
      }
    }
    this.operational = true
  }
}
