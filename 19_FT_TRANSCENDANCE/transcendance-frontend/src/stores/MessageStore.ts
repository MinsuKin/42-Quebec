import { defineStore } from 'pinia'
import type { Profile, User } from '@/interfaces/User'
import axios from '@/utils/axios'
import useUserStore, { ShortUserProfile } from '@/stores/UserStore'
import { ChatSocket } from '@/utils/chatSocket'
import { isAxiosError } from 'axios'

export interface MessageState {
  currentContactId: number
  currentContact: ShortUserProfile | undefined
  conversationsUsers: ShortUserProfile[]
  searchTerm: string
  socketManager: ChatSocket | null
  messages: Map<number, PrivateMessage[]>
  isLeftSidebarOpen: boolean
}

export interface MPData {
  receiverId: number
  content: string
}

export interface PrivateMessage {
  id: number
  text: string
  senderId: number
  receiverId: number
  timestamp: string
}

const useMessageStore = defineStore({
  id: 'message',
  state: (): MessageState => ({
    currentContactId: 0,
    currentContact: undefined as ShortUserProfile | undefined,
    conversationsUsers: [],
    searchTerm: '',
    socketManager: null,
    messages: new Map<number, PrivateMessage[]>(),
    isLeftSidebarOpen: false
  }),
  getters: {
    isSidebarOpen(): boolean {
      return this.isLeftSidebarOpen
    },
    currentContactMessages(): PrivateMessage[] {
      return this.messages.get(this.currentContactId) || []
    },
    conversationWith(): ShortUserProfile | undefined {
      return this.currentContact
    },
    getSearchTerm(): string {
      return this.searchTerm
    },
    conversationsUsersFiltered(): Array<ShortUserProfile> {
      if (!this.searchTerm.trim()) return this.conversationsUsers
      const term = this.searchTerm.toLowerCase()
      return this.conversationsUsers.filter((user) => {
        return (
          user.username.toLowerCase().includes(term) ||
          user.email.toLowerCase().includes(term) ||
          (user.profile && user.profile.name.toLowerCase().includes(term)) ||
          (user.profile && user.profile.lastname.toLowerCase().includes(term))
        )
      })
    },
    contacts(): Array<User & { profile: Profile }> {
      const userStore = useUserStore()
      return userStore.contacts
    },
    contactsWithoutConversations(): Array<User & { profile: Profile }> {
      return this.contacts.filter((contact: User) => {
        return !this.conversationsUsers.some((user) => user.id === contact.id)
      })
    }
  },
  actions: {
    clearStore() {
      this.currentContactId = 0
      this.currentContact = undefined
      this.conversationsUsers.splice(0, this.conversationsUsers.length)
      this.searchTerm = ''
      this.socketManager = null
      this.messages.clear()
      this.isLeftSidebarOpen = false
    },
    setSidebarOpen(isOpen: boolean) {
      this.isLeftSidebarOpen = isOpen
    },
    setSearchTerm(term: string) {
      this.searchTerm = term
    },
    setSocketManager(socketManager: ChatSocket) {
      this.socketManager = socketManager
    },
    async setCurrentConversationWith(contactId: number) {
      const foundUser = this.conversationsUsers.find((user) => user.id === contactId)
      if (foundUser) {
        this.currentContact = foundUser
        this.currentContactId = foundUser.id
        return
      }
      const contactFound = this.contacts.find((user) => user.id === contactId)
      if (contactFound) {
        // add it to conversation   only if not already in
        const found = this.conversationsUsers.find((user) => user.id === contactFound.id)
        if (!found) {
          this.conversationsUsers.unshift(contactFound)
        }
        this.currentContact = { ...contactFound }
        this.currentContactId = contactFound.id
        return
      }
      const userStore = useUserStore()
      try {
        const shortProfile = await userStore.getShortUserProfile(contactId)
        if (shortProfile) {
          this.currentContact = { ...shortProfile }
          this.currentContactId = shortProfile.id
          this.conversationsUsers.unshift(shortProfile)
        }
      } catch (e) {
        this.currentContact = undefined
        this.currentContactId = 0
      }
    },
    // called at unMount
    async resetCurrentConversationWith() {
      this.currentContact = undefined
      this.currentContactId = 0
    },
    async getUniqueConversations() {
      try {
        const { data } = await axios.get<Array<User & { profile: Profile }>>('/messages', {
          headers: {
            'Content-Type': 'application/json'
          }
        })
        if (Array.isArray(data)) {
          // set new conversation users without loosing reactivity
          this.conversationsUsers = data
        } else {
          this.conversationsUsers.splice(0, this.conversationsUsers.length)
        }
      } catch (error) {
        if (isAxiosError(error)) {
          if (error.response) {
            console.log('Failed to load conversations:', error.response.data.message)
          }
        }
        this.conversationsUsers.splice(0, this.conversationsUsers.length)
      }
    },
    async getPrivateMessageBetween(info: {
      userTwoId: number
      skip: number
      take: number
    }): Promise<void> {
      const { userTwoId, skip, take } = info
      try {
        const { data } = await axios.get(`/messages/${userTwoId}`, {
          params: {
            skip,
            take
          }
        })
        this.messages.set(userTwoId, data)
      } catch (e) {}
    },
    async sendPrivateMessageViaHttp(message: MPData): Promise<PrivateMessage | null> {
      try {
        const { data } = await axios.post('/messages', message, {
          headers: {
            'Content-Type': 'application/json'
          }
        })
        return data as PrivateMessage
      } catch (error) {
        console.error('Failed to send private message:', error)
      }
      return null
    },
    sendPrivateMessage(friendId: number, content: string) {
      if (!this.socketManager || !this.socketManager.operational) return
      this.socketManager.sendPrivateMessage(friendId, content)
    },
    sendUserTyping(receiverId: number) {
      if (!this.socketManager || !this.socketManager.operational) return
      this.socketManager.mpUserIsTyping(receiverId)
    },
    sendUserReload(receiverId: number) {
      if (!this.socketManager || !this.socketManager.operational) return
      this.socketManager.reloadMpConversation(receiverId)
    },
    async handleReceivedMessage(message: PrivateMessage) {
      const contactId =
        message.senderId === this.socketManager?.userId ? message.receiverId : message.senderId
      // we check if the contact among the conversationsUsers
      const foundUser = this.conversationsUsers.find((user) => user.id === contactId)
      if (!foundUser) {
        // we add him to the conversationsUsers
        const userStore = useUserStore()
        const shortProfile = await userStore.getShortUserProfile(contactId)
        if (shortProfile) {
          this.conversationsUsers.unshift(shortProfile)
        }
      }
      const userMessages = this.messages.get(contactId)
      if (userMessages) {
        userMessages.unshift(message)
        return
      } else {
        this.messages.set(contactId, [message])
      }
    },
    getLastMessageBetween(userId: number): PrivateMessage | null {
      const userMessages = this.messages.get(userId) || []
      if (userMessages.length === 0) {
        return null
      }
      // search for message with max timestamp
      let maxTimestamp = userMessages[0].timestamp
      let maxIndex = 0
      for (let i = 1; i < userMessages.length; i++) {
        if (userMessages[i].timestamp > maxTimestamp) {
          maxTimestamp = userMessages[i].timestamp
          maxIndex = i
        }
      }
      return userMessages[maxIndex]
    }
  }
})

export default useMessageStore
