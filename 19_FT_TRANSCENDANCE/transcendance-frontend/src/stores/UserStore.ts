import { defineStore } from 'pinia'
import type { Profile, User } from '@/interfaces/User'
import { Status } from '@/interfaces/User'
import axios from '@/utils/axios'
import { isAxiosError } from 'axios'
import { ReceivedStatusUpdate, StatusSocket } from '@/utils/statusSocket'
import { GameSession } from '@/stores/GameStore'

export enum FriendshipStatus {
  Friends = 'friends',
  Pending = 'pending',
  NeedApproval = 'needApproval',
  None = 'none'
}

export enum BlockedStatus {
  Blocked = 'blocked',
  BlockedBy = 'blockedBy',
  Mutual = 'mutual',
  None = 'none'
}

export interface FriendRequest {
  id: number
  senderId: number
  receiverId: number
  createdAt: Date
}

export interface FriendRequestWithReceiver extends FriendRequest {
  receiver: {
    profile: Profile
  }
}
export interface FriendRequestWithSender extends FriendRequest {
  sender: {
    profile: Profile
  }
}

export interface Contact {
  id: number
  userId: number
  contactId: number
  createdAt: Date
}

export interface CheckFriendshipResponse {
  status: FriendshipStatus
  data: Contact | FriendRequestWithSender | FriendRequestWithReceiver | null
}

export interface BlockedUser {
  id: number
  userId: number
  blockedUserId: number
  createdAt: Date
  blockedUser?: {
    profile: Profile
  }
}

export interface UserWithScore extends User {
  score: number
  gameStatus: { status: 'playing' | 'inQueue' | 'free'; gameSession?: GameSession }
}

export interface AppStatData {
  totalUsers: number
  activeUsers: number
  totalGamesPlayed: number
  totalCompetitions: number
  totalNotificationsSent: number
  averageGamesPerUser: number
  mostActiveGame: number
  mostActiveUser: number
}

export interface UserStoreState {
  contacts: Array<User & { profile: Profile }>
  blockedUsers: BlockedUser[]
  stats: AppStatData
  statusSocketManager: StatusSocket | null
  usersStatus: Map<number, Status>
  shortProfiles: Map<number, ShortUserProfile>
}

type SortOrder = 'asc' | 'desc'
export interface userOrderBy {
  username?: SortOrder
  email?: SortOrder
  profile?: {
    name?: SortOrder
    lastname?: SortOrder
    status?: SortOrder
  }
  createdAt?: SortOrder
  updatedAt?: SortOrder
}

export type ShortUserProfile = Pick<
  User & { profile: Profile },
  'id' | 'profile' | 'username' | 'email' | 'updatedAt'
>

const aiProfile: ShortUserProfile = {
  id: 0,
  profile: {
    id: 0,
    userId: 0,
    name: 'AI',
    lastname: 'Bot',
    avatar: '/pong/ia_avatar.jpg',
    status: Status.Online
  },
  username: 'AI',
  email: 'ai',
  updatedAt: new Date().toISOString()
}

const roomWaiting: ShortUserProfile = {
  id: -1,
  profile: {
    id: 0,
    userId: -1,
    name: 'Game',
    lastname: 'Room',
    avatar: '/pong/ia_avatar.jpg',
    status: Status.Busy
  },
  username: 'GameRooom',
  email: 'ftmjr',
  updatedAt: new Date().toISOString()
}

const useUserStore = defineStore({
  id: 'userStore',
  state: (): UserStoreState => {
    const stats: AppStatData = {
      totalUsers: 0,
      activeUsers: 0,
      totalGamesPlayed: 0,
      totalCompetitions: 0,
      totalNotificationsSent: 0,
      averageGamesPerUser: 0,
      mostActiveGame: 0, //gameId
      mostActiveUser: 0 //userId
    }
    const usersStatus = new Map<number, Status>()
    usersStatus.set(-1, Status.Busy)
    usersStatus.set(0, Status.Online)
    return {
      contacts: [],
      blockedUsers: [],
      stats,
      statusSocketManager: null,
      usersStatus,
      shortProfiles: new Map<number, ShortUserProfile>()
    }
  },
  getters: {
    getStats(): AppStatData {
      return this.stats
    },
    getContact(): Array<User & { profile: Profile }> {
      return this.contacts
    },
    getBlockedUsers(): BlockedUser[] {
      return this.blockedUsers
    },
    socketOperational(): boolean {
      return this.statusSocketManager?.operational ?? false
    },
    getUsersStatus(): Map<number, Status> {
      return this.usersStatus
    }
  },
  actions: {
    /* Friendship section */
    resetStore() {
      this.contacts.splice(0, this.contacts.length)
      this.blockedUsers.splice(0, this.blockedUsers.length)
      this.disconnectStatusSocket()
      this.usersStatus.clear()
      this.usersStatus.set(-1, Status.Busy)
      this.usersStatus.set(0, Status.Online)
      this.shortProfiles.clear()
    },
    async askFriendRequest(targetId: number): Promise<'success' | 'already' | 'error'> {
      let message: 'success' | 'already' | 'error' = 'success'
      try {
        await axios.post(`/friends/request-friendship-with/${targetId}`)
      } catch (error) {
        if (isAxiosError(error)) {
          if (error.response && error.response.status === 409) {
            message = 'already'
          }
        } else {
          message = 'error'
        }
      }
      return message
    },
    async cancelFriendRequest(requestId: number): Promise<'success' | 'error'> {
      try {
        await axios.delete(`/friends/sent/${requestId}`)
        return 'success'
      } catch (e) {
        return 'error'
      }
    },
    async approveFriendRequest(requestId: number): Promise<'success' | 'error'> {
      try {
        await axios.post(`/friends/approve-friendship-request-for/${requestId}`)
        await this.loadAllMyFriends()
        return 'success'
      } catch (e) {
        return 'error'
      }
    },
    async rejectFriendRequest(requestId: number): Promise<'success' | 'error'> {
      try {
        await axios.delete(`/friends/reject/${requestId}`)
        return 'success'
      } catch (e) {
        return 'error'
      }
    },
    async unFriend(friendId: number): Promise<'success' | 'error'> {
      try {
        await axios.delete(`/friends/${friendId}`)
        await this.loadAllMyFriends()
        return 'success'
      } catch (e) {
        return 'error'
      }
    },
    async loadAllMyFriends(): Promise<'success' | 'error'> {
      try {
        const { data } = await axios.get<Array<User & { profile: Profile }>>('/friends')
        this.contacts = data
        return 'success'
      } catch (e) {
        return 'error'
      }
    },
    async getSentRequests(): Promise<FriendRequestWithReceiver[]> {
      try {
        const { data } = await axios.get<FriendRequestWithReceiver[]>('/friends/sent')
        return data
      } catch (e) {
        console.log('Failed to load sent request', e)
      }
      return []
    },
    async getReceivedRequests(): Promise<FriendRequestWithSender[]> {
      try {
        const { data } = await axios.get<FriendRequestWithSender[]>('/friends/received')
        return data
      } catch (e) {
        console.log('Failed to load received request', e)
      }
      return []
    },
    async checkFriendShip(userId: number): Promise<CheckFriendshipResponse> {
      try {
        const { data } = await axios.get<CheckFriendshipResponse>(`/friends/check/${userId}`)
        return data
      } catch (error) {
        console.log('failed to check friendship status')
      }
      return { status: FriendshipStatus.None, data: null }
    },

    /* Blocked users */
    async loadBlockedUsers(): Promise<'success' | 'error'> {
      try {
        const { data } = await axios.get<BlockedUser[]>('/users/block', {
          headers: {
            'Content-Type': 'application/json'
          }
        })
        this.blockedUsers = data
        return 'success'
      } catch (e) {
        return 'error'
      }
    },
    async checkBlocked(friendId: number): Promise<BlockedStatus> {
      try {
        const isInLocal = this.blockedUsers.find((user) => user.blockedUserId === friendId)
        if (isInLocal) {
          return BlockedStatus.Blocked
        }
        const { data } = await axios.get<BlockedStatus>(`/users/check-blocked/${friendId}`)
        return data
      } catch (e) {
        console.log('failed to check blocked status')
      }
      return BlockedStatus.None
    },
    async checkBlockedForMany(
      userIds: number[]
    ): Promise<{ userId: number; status: BlockedStatus }[]> {
      try {
        const { data } = await axios.post<BlockedStatus[]>(`/users/check-blocked/`, { userIds })
        return userIds.map((id, index) => {
          return {
            userId: id,
            status: data[index]
          }
        })
      } catch (e) {
        return userIds.map(() => {
          return {
            userId: 0,
            status: BlockedStatus.None
          }
        })
      }
    },
    async blockUser(userId: number): Promise<'success' | 'error'> {
      try {
        const { data } = await axios.post<BlockedUser>(`/users/block/${userId}`)
        this.blockedUsers.push(data)
        await this.loadAllMyFriends()
        return 'success'
      } catch (error) {
        return 'error'
      }
    },
    async unblockUser(userId: number): Promise<'success' | 'error'> {
      try {
        await axios.delete(`/users/unblock/${userId}`)
        await this.loadBlockedUsers()
        await this.loadAllMyFriends()
        return 'success'
      } catch (e) {
        return 'error'
      }
    },

    /* User section */
    async getProfile(userId: number): Promise<User | null> {
      try {
        const { data } = await axios.get<User>(`/users/profile/${userId}`)
        return data
      } catch (e) {
        console.log(e)
      }
      return null
    },
    async getShortUserProfile(userId: number): Promise<ShortUserProfile> {
      try {
        if (userId === -1) return roomWaiting
        if (userId === 0) return aiProfile
        if (!userId) return roomWaiting
        // check if the user is in the map
        const profile = this.shortProfiles.get(userId)
        if (profile) return profile
        const { data } = await axios.get<ShortUserProfile>(`/users/short-profile/${userId}`)
        this.usersStatus.set(userId, data.profile.status)
        this.shortProfiles.set(userId, data)
        return data
      } catch (e) {
        console.log(e)
      }
      return roomWaiting
    },
    async getPaginatedUser(params: {
      currentPage: number
      perPage: number
      orderBy?: userOrderBy
    }): Promise<User[]> {
      const { currentPage, perPage, orderBy } = params
      const skip = (currentPage - 1) * perPage
      const take = perPage
      try {
        const { data } = await axios.get<User[]>('/users/all', {
          params: {
            skip,
            take,
            orderBy
          }
        })
        return data
      } catch (e) {
        console.log(e)
      }
      return []
    },
    async getPaginatedUsersWithScore(params: {
      skip?: number
      take?: number
    }): Promise<UserWithScore[]> {
      const { skip, take } = params
      try {
        const { data } = await axios.get<UserWithScore[]>('/users/leaderboard', {
          params: {
            skip,
            take
          }
        })
        return data
      } catch (e) {
        console.log(e)
      }
      return []
    },
    async searchUsers(params: {
      searchTerm: string
      currentPage: number
      perPage: number
    }): Promise<Array<User & { profile: Profile }>> {
      const { currentPage, perPage, searchTerm } = params
      const skip = (currentPage - 1) * perPage
      try {
        const { data } = await axios.get<Array<User & { profile: Profile }>>('users/search', {
          params: {
            query: searchTerm,
            skip: skip ?? 0,
            take: perPage ?? 100
          }
        })
        return data
      } catch (e) {
        console.log(e)
      }
      return []
    },
    /* Statistics */
    async getAppStatistics(): Promise<'success' | 'error'> {
      try {
        const { data } = await axios.get<AppStatData>('/users/stats')
        this.stats = data
        return 'success'
      } catch (e) {
        console.log(e)
        return 'error'
      }
    },

    /* Status*/
    initStatusSocket(userId: number) {
      const token = localStorage.getItem('__token__') as string
      this.statusSocketManager = StatusSocket.getInstance(userId, (data: ReceivedStatusUpdate) => {
        this.usersStatus.set(data.userId, data.status)
      }, token)
      if (!this.statusSocketManager.operational) {
        this.statusSocketManager.reconnect()
      }
    },
    disconnectStatusSocket() {
      StatusSocket.destroyInstance()
      this.statusSocketManager = null
    },
    async getStatus(userId: number): Promise<Status> {
      // check if the user is in the map
      const status = this.usersStatus.get(userId)
      if (status) {
        return status
      }
      // if not, fetch the status from the server
      try {
        const shortProfile = await this.getShortUserProfile(userId)
        if (!shortProfile) {
          return Status.Offline
        }
        this.usersStatus.set(userId, shortProfile.profile.status)
        return shortProfile.profile.status
      } catch (e) {
        console.log(e)
      }
      return Status.Offline
    },
    async updateMyStatus(status: Status) {
      if (this.statusSocketManager) {
        this.statusSocketManager.updateMyStatus(status)
      }
    }
  }
})

export default useUserStore
