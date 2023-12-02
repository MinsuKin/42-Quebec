import { io, Socket } from 'socket.io-client'
import { PrivateMessage } from '@/stores/MessageStore'

export enum RoomType {
  PUBLIC = 'PUBLIC',
  PRIVATE = 'PRIVATE',
  PROTECTED = 'PROTECTED'
}

export enum ChatMemberRole {
  OWNER = 'OWNER',
  ADMIN = 'ADMIN',
  USER = 'USER',
  MUTED = 'MUTED',
  BAN = 'BAN'
}
export interface ChatRoomMember {
  id: number
  memberId: number
  chatroomId: number
  role: ChatMemberRole
  createdAt: string
  updatedAt: string
  unMuteAt: string;
}

export interface ChatRoom {
  id: number
  name: string
  type: RoomType
  password: string | null
  avatar: string | null
  createdAt: string
  members?: ChatRoomMember[]
}
export interface ChatMessage {
  id: number
  chatroomId: number
  userId: number
  content: string
  timestamp: string // date
}

// Événements reçus par le client
interface ListenEvents {
  newMessage: (message: ChatMessage) => void
  newMP: (message: PrivateMessage) => void
  receivedUserIsTypingInRoom: (typingInfo: {
    senderId: number
    roomId: number
    username: string
  }) => void
  reloadRoomMembers: (roomId: number) => void
  receivedUserIsTyping: (senderId: number) => void
  reloadMp: (senderId: number) => void
  failedToSendMessage: (error: string) => void
  connectionError: (error: string) => void
}

// Événements émis par le client
interface EmitEvents {
  sendMessage: (data: { senderId: number; roomId: number; content: string }) => void
  sendPrivateMessage: (
    data: { senderId: number; receiverId: number; content: string },
    callback: (res: PrivateMessage) => void
  ) => void
  userIsTypingInRoom: (data: { senderId: number; roomId: number; username: string }) => void
  reloadRoomMembers: (data: { roomId: number }) => void
  mpUserIsTyping: (data: { senderId: number; receiverId: number }) => void
  reloadMpConversation: (data: { senderId: number; receiverId: number }) => void
  joinRoom: (data: { roomId: number; userId: number }) => void
  joinMyRoom: () => void
}

export class ChatSocket {
  private static instance: ChatSocket
  socket: Socket<ListenEvents, EmitEvents> | undefined
  public operational: boolean = false
  public managedRoomIds: number[] = []
  private sendingMp = false

  private constructor(
    public userId: number,
    onConnectionError: (error: string) => void,
    onFailedToSendMessage: (error: string) => void,
    public onNewMessage: (message: ChatMessage) => void,
    onRoomMembersReload: (roomId: number) => void,
    onRoomMemberTyping: (typingInfo: {
      senderId: number
      roomId: number
      username: string
      timestamp: number
    }) => void,
    // Mp events
    public onNewMp: (message: PrivateMessage) => void,
    onConversationReload: (senderId: number) => void,
    onUserIsTyping: (senderId: number, timestamp: number) => void,
    token: string
  ) {
    this.userId = userId
    try {
      this.socket = io('/chat', {
        path: '/socket.io/',
        query: { userId },
        auth: { token: token }
      })
      this.socket.emit('joinMyRoom')
      this.socket.on('connect', () => {
        this.operational = true
      })
      this.socket.on('disconnect', () => {
        this.operational = false
      })
      this.socket.on('newMessage', (message) => {
        this.onNewMessage(message)
      })
      this.socket.on('newMP', (data) => {
        this.onNewMp(data)
      })
      this.socket.on('receivedUserIsTypingInRoom', (data) => {
        const timestamp = Date.now()
        onRoomMemberTyping({
          ...data,
          timestamp
        })
      })
      this.socket.on('reloadRoomMembers', onRoomMembersReload)
      this.socket.on('receivedUserIsTyping', (senderId) => {
        const timestamp = Date.now()
        onUserIsTyping(senderId, timestamp)
      })
      this.socket.on('reloadMp', onConversationReload)
      this.socket.on('failedToSendMessage', onFailedToSendMessage)
      this.socket.on('connectionError', (data) => {
        this.sendingMp = false
        onConnectionError(data)
      })
    } catch (e) {
      console.error(e)
    }
  }

  public static getInstance(
    userId: number,
    onNewMessage: (message: ChatMessage) => void,
    onNewMp: (message: PrivateMessage) => void,
    onFailedToSendMessage: (error: string) => void,
    onConnectionError: (error: string) => void,
    onRoomMembersReload: (roomId: number) => void,
    onRoomMemberTyping: (typingInfo: {
      senderId: number
      roomId: number
      username: string
      timestamp: number
    }) => void,
    onConversationReload: (senderId: number) => void,
    onMpContactTyping: (senderId: number, timestamp: number) => void,
    token: string
  ): ChatSocket {
    if (!ChatSocket.instance) {
      ChatSocket.instance = new ChatSocket(
        userId,
        onConnectionError,
        onFailedToSendMessage,
        onNewMessage,
        onRoomMembersReload,
        onRoomMemberTyping,
        onNewMp,
        onConversationReload,
        onMpContactTyping,
        token
      )
    }
    ChatSocket.instance.onNewMp = onNewMp
    ChatSocket.instance.onNewMessage = onNewMessage
    return ChatSocket.instance
  }

  disconnect() {
    if (this.socket) {
      this.socket.disconnect()
    }
    this.operational = false
  }

  static destroyInstance() {
    if (ChatSocket.instance) {
      ChatSocket.instance.disconnect()
      // @ts-expect-error - private property
      ChatSocket.instance = undefined
    }
  }

  connect() {
    if (this.socket) {
      this.socket.connect()
    }
    this.operational = true
  }

  sendMessage(roomId: number, content: string) {
    if (this.socket && this.operational) {
      this.socket.emit('sendMessage', {
        senderId: this.userId,
        roomId,
        content
      })
    }
  }

  sendPrivateMessage(receiverId: number, content: string) {
    if (this.socket && this.operational) {
      const data = {
        senderId: this.userId,
        receiverId,
        content
      }
      if (this.sendingMp) return
      this.sendingMp = true
      this.socket.emit('sendPrivateMessage', data, (res) => {
        this.sendingMp = false
        this.onNewMp(res)
      })
    }
  }

  userIsTypingInRoom(roomId: number, username: string) {
    if (this.socket && this.operational) {
      this.socket.emit('userIsTypingInRoom', {
        senderId: this.userId,
        roomId,
        username
      })
    }
  }

  mpUserIsTyping(receiverId: number) {
    if (this.socket && this.operational) {
      this.socket.emit('mpUserIsTyping', {
        senderId: this.userId,
        receiverId
      })
    }
  }

  reloadRoomMembers(roomId: number) {
    if (this.socket && this.operational) {
      this.socket.emit('reloadRoomMembers', { roomId })
    }
  }

  reloadMpConversation(receiverId: number) {
    if (this.socket && this.operational) {
      this.socket.emit('reloadMpConversation', {
        senderId: this.userId,
        receiverId
      })
    }
  }

  listenRoom(roomId: number) {
    if (this.socket && this.operational) {
      this.socket.emit('joinRoom', {
        roomId,
        userId: this.userId
      })
      this.managedRoomIds.push(roomId)
    }
  }
}
