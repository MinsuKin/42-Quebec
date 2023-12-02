import { defineStore } from 'pinia'
import {
  ChatMemberRole,
  ChatMessage,
  ChatRoom,
  ChatRoomMember,
  ChatSocket,
  RoomType
} from '@/utils/chatSocket'
import axios from '@/utils/axios'
import { Profile, User } from '@/interfaces/User'
import useMessageStore, { PrivateMessage } from '@/stores/MessageStore'
import { isAxiosError } from 'axios'
import useUserStore, { BlockedStatus } from '@/stores/UserStore'
import useNotificationStore from '@/stores/NotificationStore'

export interface JoinRoom {
  userId: number
  password?: string
}
export interface CreateRoom {
  ownerId: number
  name: string
  type: RoomType
  password?: string
  avatar?: string
}

export type ChatRoomWithMembers = ChatRoom & {
  members: ChatRoomMember[]
}

export type MemberRoomWithUserProfiles = ChatRoomMember & {
  member: User & {
    profile: Profile
  }
}

export interface UpdateRoomData {
  roomId: number
  roomType: RoomType
  oldPassword?: string
  password?: string // 6char min
}

export const rolePrint: Array<{
  role: ChatMemberRole
  printRole: string
  color?: string
  bgClass?: string
}> = [
  { role: ChatMemberRole.OWNER, printRole: 'Big Boss', color: 'success' },
  { role: ChatMemberRole.ADMIN, printRole: 'Administrateur', bgClass: 'info' },
  { role: ChatMemberRole.USER, printRole: 'Utilisateur', color: 'dark' },
  { role: ChatMemberRole.BAN, printRole: 'Ban', color: 'danger' }
]

const useRoomsStore = defineStore({
  id: 'roomsStore',
  state: (): {
    userId: number
    socketManager: ChatSocket | null
    currentRoomStatus: { state: boolean; role: ChatMemberRole | null; room?: ChatRoom }
    isLeftNavOpen: boolean
    isRightNavOpen: boolean
    roomsMembersTyping: Map<number, { senderId: number; username: string; timestamp: number }>
    currentRoomMembers: MemberRoomWithUserProfiles[]
    rooms: ChatRoomWithMembers[]
    publicRooms: ChatRoomWithMembers[]
    searchTerm: string
    messages: Map<number, ChatMessage[]>
    roomsBlockedStatus: Map<number, BlockedStatus>
    contactTyping: Map<number, number>
  } => {
    return {
      userId: 0,
      socketManager: null,
      currentRoomStatus: { state: false, role: null },
      isLeftNavOpen: false,
      isRightNavOpen: false,
      roomsMembersTyping: new Map<
        number,
        { senderId: number; username: string; timestamp: number }
      >(),
      currentRoomMembers: [],
      rooms: [],
      publicRooms: [],
      searchTerm: '',
      messages: new Map<number, ChatMessage[]>(),
      roomsBlockedStatus: new Map<number, BlockedStatus>(),
      contactTyping: new Map<number, number>()
    }
  },
  getters: {
    socketOperational(): boolean {
      return this.socketManager?.operational ?? false
    },
    currentRoom(): ChatRoom | undefined {
      return this.currentRoomStatus.room
    },
    // if current User is member of current room
    isMemberOfRoom(): boolean {
      return this.currentRoomStatus.state
    },
    currentRoomRole(): ChatMemberRole | null {
      return this.currentRoomStatus.role
    },
    isOwner(): boolean {
      return this.currentRoomStatus.role === ChatMemberRole.OWNER
    },
    isAdmin(): boolean {
      return this.currentRoomStatus.role === ChatMemberRole.ADMIN
    },
    isUser(): boolean {
      return this.currentRoomStatus.role === ChatMemberRole.USER
    },
    isBanned(): boolean {
      return this.currentRoomStatus.role === ChatMemberRole.BAN
    },
    isMuted(): boolean {
      return this.currentRoomStatus.role === ChatMemberRole.MUTED
    },
    isPublic(): boolean {
      return this.currentRoomStatus.room?.type === RoomType.PUBLIC
    },
    isProtected(): boolean {
      return this.currentRoomStatus.room?.type === RoomType.PROTECTED
    },
    isPrivate(): boolean {
      return this.currentRoomStatus.room?.type === RoomType.PRIVATE
    },
    isPasswordProtected(): boolean {
      if (!this.currentRoomStatus.room) return false
      if (!this.currentRoomStatus.room.password) return false
      return this.currentRoomStatus.room.password.trim().length > 0
    },
    roomMembers(): MemberRoomWithUserProfiles[] {
      return this.currentRoomMembers
    },
    allBlockedStatus(): Map<number, BlockedStatus> {
      return this.roomsBlockedStatus
    },
    myRooms(): ChatRoomWithMembers[] {
      return this.rooms
    },
    filteredRooms(): ChatRoomWithMembers[] {
      if (!this.searchTerm.trim()) return this.rooms
      const term = this.searchTerm.toLowerCase()
      return this.rooms.filter((room: ChatRoomWithMembers) => {
        return room.name.toLowerCase().includes(term)
      })
    },
    publicButNotJoined(): ChatRoomWithMembers[] {
      return this.publicRooms.filter(
        (room: ChatRoomWithMembers) =>
          !this.rooms.find((r: ChatRoomWithMembers) => r.id === room.id)
      )
    },
    filteredPublic(): ChatRoomWithMembers[] {
      if (!this.searchTerm.trim()) return this.publicButNotJoined
      const term = this.searchTerm.toLowerCase()
      return this.publicButNotJoined.filter((room: ChatRoomWithMembers) => {
        return room.name.toLowerCase().includes(term)
      })
    },
    getCurrentRoomMessages(): ChatMessage[] {
      if (!this.currentRoom) return []
      return this.messages.get(this.currentRoom.id) ?? []
    },
    getSearchTerm(): string {
      return this.searchTerm
    },
    getContactTyping(): Map<number, number> {
      return this.contactTyping
    },
    getRoomMembersTyping(): Map<number, { senderId: number; username: string; timestamp: number }> {
      return this.roomsMembersTyping
    },
    getIsLeftNavOpen(): boolean {
      return this.isLeftNavOpen
    },
    getIsRightNavOpen(): boolean {
      return this.isRightNavOpen
    }
  },
  actions: {
    async init(userId: number) {
      this.userId = userId
      await this.getAllMyRooms()
      const messageStore = useMessageStore()
      const token = localStorage.getItem('__token__') as string
      this.socketManager = ChatSocket.getInstance(
        userId,
        (message: ChatMessage) => {
          // if the message chatRoomId among the rooms the user is member of we add
          if (this.rooms.some((room) => room.id === message.chatroomId)) {
            const messages = this.messages.get(message.chatroomId)
            if (messages) {
              messages.push(message)
              this.messages.set(message.chatroomId, messages)
            } else {
              this.messages.set(message.chatroomId, [message])
            }
          }
        },
        (message: PrivateMessage) => {
          messageStore.handleReceivedMessage(message)
        },
        (error: string) => {
          console.log('message packet not sent')
        },
        (error: string) => {
          console.log('chat socket connection error', error)
        },
        (roomId: number) => {
          // if room is the current room, reload members
          if (roomId === this.currentRoom?.id) {
            this.selectRoom(roomId)
          }
        },
        (typingInfo: { senderId: number; roomId: number; username: string; timestamp: number }) => {
          this.roomsMembersTyping.set(typingInfo.roomId, typingInfo)
        },
        (senderId: number) => {
          // no more
        },
        (senderId: number, timestamp: number) => {
          this.contactTyping.set(senderId, timestamp)
        },
        token
      )
      if (!this.socketManager) return
      if (!this.socketManager.operational) {
        this.socketManager.connect()
      }
      messageStore.setSocketManager(this.socketManager as ChatSocket)
    },
    resetStore() {
      // reset store
      this.userId = 0
      this.disconnect()
      this.currentRoomStatus = { state: false, role: null }
      this.isLeftNavOpen = false
      this.isRightNavOpen = false
      this.roomsMembersTyping.clear()
      this.currentRoomMembers = []
      this.rooms.splice(0, this.rooms.length)
      this.publicRooms.splice(0, this.publicRooms.length)
      this.searchTerm = ''
      this.messages.clear()
      this.roomsBlockedStatus.clear()
      this.contactTyping.clear()
    },
    setSearchTerm(term: string) {
      this.searchTerm = term
    },
    sendMessage(roomId: number, content: string) {
      if (!this.socketManager) return
      this.socketManager.sendMessage(roomId, content)
    },
    sendUserIsTypingInRoom(roomId: number, username: string) {
      if (!this.socketManager) return
      this.socketManager.userIsTypingInRoom(roomId, username)
    },
    async selectRoom(roomId: number): Promise<void> {
      this.currentRoomStatus = await this.checkRoomRole(roomId)
      this.currentRoomMembers.splice(0, this.currentRoomMembers.length)
      const isPublic = this.currentRoomStatus.room?.type === RoomType.PUBLIC
      if (this.currentRoomStatus.state || isPublic) {
        const currentRoomMembers = await this.getRoomMembersData(roomId)
        if (Array.isArray(currentRoomMembers)) {
          this.currentRoomMembers = currentRoomMembers
        }
      }
    },
    resetSelect() {
      this.currentRoomStatus = { state: false, role: null }
      this.currentRoomMembers.splice(0, this.currentRoomMembers.length)
    },
    /*
     * Join a room
     * @param roomId the id of the room to join
     * @param info the info to join the room (userId, password)
     * @returns ChatRoomMember if success, string if error
     */
    async createRoom(info: CreateRoom): Promise<'success' | 'failed'> {
      try {
        const { data } = await axios.post<ChatRoomWithMembers>('/chat/create-room', info)
        this.rooms.unshift(data)
        await this.selectRoom(data.id)
        return 'success'
      } catch (error) {
        return 'failed'
      }
    },
    async joinRoom(roomId: number, info: JoinRoom): Promise<ChatRoomMember | string> {
      let errorMessage = `Vous n'êtes pas autorisé à rejoindre cette salle`
      try {
        const { data } = await axios.post<ChatRoomMember>(`/chat/join-room/${roomId}`, info)
        await this.getAllMyRooms()
        await this.selectRoom(data.chatroomId)
        await this.loadCurrentRoomMessages({ skip: 0, take: 100 })
        return data
      } catch (error) {
        if (isAxiosError(error)) {
          errorMessage =
            error.response?.data.message ?? `Vous n'êtes pas autorisé à rejoindre cette salle`
        }
      }
      return errorMessage
    },
    async cleanAfterLeaving(roomId: number) {
      this.resetSelect()
      this.rooms = this.rooms.filter((room) => room.id !== roomId)
      if (!this.currentRoom) return
      if (this.currentRoom.id === roomId) {
        const index = this.rooms.findIndex((room) => room.id === roomId)
        if (index !== -1) {
          const nextRoom = this.rooms[index + 1] ?? this.rooms[index - 1] ?? null
          if (nextRoom) {
            await this.selectRoom(nextRoom.id)
          }
        }
      }
    },
    async quitRoom(roomId: number): Promise<'success' | 'failed' | string> {
      try {
        await axios.get(`/chat/leave-room/${roomId}`)
        await this.cleanAfterLeaving(roomId)
        return 'success'
      } catch (error) {
        if (isAxiosError(error)) {
          return error.response?.data.message ?? 'failed'
        }
      }
      return 'failed'
    },
    async deleteRoom(roomId: number): Promise<'success' | 'failed' | string> {
      try {
        await axios.delete<ChatRoom>(`/chat/delete-room/${roomId}`)
        await this.cleanAfterLeaving(roomId)
        return 'success'
      } catch (error) {
        if (isAxiosError(error)) {
          return error.response?.data.message ?? 'failed'
        }
      }
      return 'failed'
    },
    async changeMemberRole(
      roomId: number,
      member: ChatRoomMember,
      promoteTo: ChatMemberRole,
      expireAt?: number // timestamp for the end of MUTED role if needed
    ): Promise<'success' | 'failed'> {
      try {
        // cannot chnage role of owner
        if (member.role === ChatMemberRole.OWNER) {
          return 'failed'
        }
        await axios.post(`/chat/promote/${roomId}`, {
          userId: member.memberId,
          role: promoteTo,
          expireAt
        })
        this.sendReloadRoomMembers(roomId)
        return 'success'
      } catch (error) {
        console.error(error)
        return 'failed'
      }
    },

    /**
     * @name updateAvatar
     * @param roomId
     * @param avatar
     * @description Update avatar
     * @returns
     */
    async updateAvatar(roomId: number, avatar: File): Promise<'success' | 'error'> {
      try {
        if (!this.currentRoom) return 'error'
        const formData = new FormData()
        formData.append('file', avatar)
        await axios.post(`/files/chatRoomAvatar/${roomId}`, formData, {
          headers: {
            'Content-Type': 'multipart/form-data'
          }
        })
        return 'success'
      } catch (e) {
        return 'error'
      }
    },

    async updateRoomPassword(
      roomId: number,
      newPassword: string,
      currentRole: ChatMemberRole
    ): Promise<'success' | 'failed'> {
      if (currentRole !== ChatMemberRole.OWNER && currentRole !== ChatMemberRole.ADMIN) {
        return 'failed'
      }
      try {
        await axios.patch(`/chat/update-password`, { roomId, password: newPassword })
        return 'success'
      } catch (error) {
        console.error(error)
        return 'failed'
      }
    },
    async updateRoom(roomId: number, info: UpdateRoomData): Promise<'success' | 'failed' | string> {
      try {
        const { data } = await axios.patch<ChatRoomWithMembers>(`/chat/update-room-info`, info)
        const roomIndex = this.rooms.findIndex((room) => room.id === roomId)
        if (roomIndex !== -1) {
          this.rooms.splice(roomIndex, 1, data)
        }
        return 'success'
      } catch (e) {
        if (isAxiosError(e)) {
          const axiosE = e.response?.data.message ?? 'failed'
          if (Array.isArray(axiosE)) {
            return axiosE[0]
          }
          return axiosE
        }
      }
      return 'failed'
    },
    // main function work for any valid room and return details about it
    async checkRoomRole(
      roomId: number
    ): Promise<{ state: boolean; role: ChatMemberRole | null; room?: ChatRoom }> {
      try {
        const { data } = await axios.get<{
          state: boolean
          role: ChatMemberRole | null
          room?: ChatRoom
        }>(`/chat/room-role/${roomId}`)
        return data
      } catch (error) {
        console.log('Failed to check room role')
      }
      return { state: false, role: null }
    },

    // get all members of a room
    async getRoomMembersData(roomId: number): Promise<MemberRoomWithUserProfiles[]> {
      try {
        const { data } = await axios.get<MemberRoomWithUserProfiles[]>(`/chat/room/${roomId}`)
        if (Array.isArray(data)) {
          await this.setBlockedStatusForMembers(data)
        }
        return data
      } catch (error) {
        return []
      }
    },
    async reloadCurrentRoomMembers(): Promise<'success' | 'failed'> {
      if (!this.currentRoom) return 'failed'
      try {
        const members = await this.getRoomMembersData(this.currentRoom.id)
        if (Array.isArray(members)) {
          this.currentRoomMembers = members
          return 'success'
        } else {
          return 'failed'
        }
      } catch (error) {
        return 'failed'
      }
    },
    async loadCurrentRoomMessages(info: { skip: number; take: number }): Promise<void> {
      const { skip, take } = info
      if (!this.currentRoom) return
      if (!this.currentRoomStatus.state) return
      try {
        const { data } = await axios.get<ChatMessage[]>(`/chat/messages/${this.currentRoom.id}`, {
          params: {
            skip,
            take
          }
        })
        this.listenToRoom(this.currentRoom.id)
        this.messages.set(this.currentRoom.id, data)
      } catch (error) {
        console.log('Failed to load room messages')
      }
    },
    // fetch PUBLIC and PROTECTED rooms
    async fetchPublicRooms() {
      try {
        const { data } = await axios.get<ChatRoomWithMembers[]>('/chat/public')
        if (Array.isArray(data)) {
          this.publicRooms = data
        } else {
          this.publicRooms.splice(0, this.publicRooms.length)
        }
      } catch (error) {
        this.publicRooms.splice(0, this.publicRooms.length)
      }
    },
    // get all rooms where user is a member and start listening to them
    async getAllMyRooms() {
      try {
        const { data } = await axios.get<ChatRoomWithMembers[]>('/chat/rooms')
        // start listening to all rooms
        data.forEach((room) => {
          // avoid listening to room if user is banned from it
          const member = room.members.find((member) => member.id === this.userId)
          if (member && member.role === ChatMemberRole.BAN) return
          this.listenToRoom(room.id)
        })
        this.rooms = data
      } catch (error) {
        // console.log(error)
      }
    },
    // start listening to a room via socket
    listenToRoom(roomId: number) {
      const notificationStore = useNotificationStore()
      notificationStore.listenToRoomNotifications(roomId)
      if (!this.socketManager) return
      if (!this.socketManager.operational) return
      this.socketManager.listenRoom(roomId)
    },
    // reload room members
    sendReloadRoomMembers(roomId: number) {
      if (!this.socketManager) return
      if (!this.socketManager.operational) return
      this.socketManager.reloadRoomMembers(roomId)
    },
    disconnect() {
      ChatSocket.destroyInstance()
      this.socketManager = null
    },
    toggleLeftNav() {
      this.isLeftNavOpen = !this.isLeftNavOpen
    },
    toggleRightNav() {
      this.isRightNavOpen = !this.isRightNavOpen
    },
    async setBlockedStatusForMembers(members: MemberRoomWithUserProfiles[]) {
      const userStore = useUserStore()
      try {
        const ids = members.map((member) => member.memberId)
        const blockedStatus = await userStore.checkBlockedForMany(ids)
        blockedStatus.forEach((status) => {
          this.roomsBlockedStatus.set(status.userId, status.status)
        })
      } catch (error) {
        // nothing
      }
    },
    async setUserBlockedStatus(userId: number) {
      const userStore = useUserStore()
      try {
        const status = await userStore.checkBlocked(userId)
        this.roomsBlockedStatus.set(userId, status)
      } catch (error) {
        // nothing
      }
    },

    /**
     * @name kickMember
     * @description kick a member from a room
     * @param roomId the id of the room
     * @param userId the id of the user to kick
     * @returns 'success' if success, 'failed' if failed
     */
    async kickMember(roomId: number, userId: number): Promise<'success' | 'failed'> {
      try {
        const data = { roomId: roomId, userId: userId }
        await axios.post(`/chat/remove-member/${roomId}`, data)
        // Mise à jour du store après avoir kické un membre
        await this.reloadCurrentRoomMembers()
        return 'success'
      } catch (error) {
        return 'failed'
      }
    },
    async inviteUser(roomId: number, userId: number): Promise<'success' | 'failed'> {
      try {
        const data = { roomId: roomId, userId: userId }
        await axios.post(`/chat/invite`, data)
        return 'success'
      } catch (error) {
        return 'failed'
      }
    }
  }
})

export default useRoomsStore
