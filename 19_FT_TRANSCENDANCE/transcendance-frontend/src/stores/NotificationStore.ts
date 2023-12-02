import { defineStore } from 'pinia'
import { Notification, NotificationSocket, RealTimeNotification } from '@/utils/notificationSocket'
import axios from '@/utils/axios'

export interface NotificationState {
  notifications: Notification[]
  realTimeNotifications: RealTimeNotification[]
  socketManager: NotificationSocket | null
}

const useNotificationStore = defineStore({
  id: 'notification',
  state: (): NotificationState => {
    return {
      notifications: [],
      realTimeNotifications: [],
      socketManager: null
    }
  },
  getters: {
    allNotifications(): Notification[] {
      return this.notifications
    },
    unreadNotifications(): Notification[] {
      return this.notifications.filter(
        (notification: Notification) => notification.status === 'UNREAD'
      )
    },
    unreadNotificationsCount(): number {
      return this.unreadNotifications.length
    },
    socketOperational(): boolean {
      return this.socketManager?.operational ?? false
    },
    allRealTimeNotifications(): RealTimeNotification[] {
      return this.realTimeNotifications
    }
  },
  actions: {
    clearStore() {
      this.notifications.splice(0, this.notifications.length)
      this.realTimeNotifications.splice(0, this.realTimeNotifications.length)
      this.disconnect()
    },
    async init(userId: number) {
      await this.getNotifications()
      const token = localStorage.getItem('__token__') as string
      this.socketManager = NotificationSocket.getInstance(
        userId,
        (notification) => {
          this.notifications.unshift(notification)
        },
        (realTimeNotification) => {
          this.realTimeNotifications.unshift(realTimeNotification)
        },
        token
      )
      if (!this.socketManager.operational) {
        this.socketManager.connect()
      }
    },
    disconnect() {
      NotificationSocket.destroyInstance()
      this.socketManager = null
    },
    listenToRoomNotifications(roomId: number) {
      this.socketManager?.listenToRoomNotifications(roomId)
    },
    leaveRoomNotifications(roomId: number) {
      this.socketManager?.leaveRoomNotifications(roomId)
    },
    async getNotifications() {
      try {
        const { data } = await axios.get<Notification[]>('notifications/')
        this.notifications = data
      } catch (e) {
        console.error(e)
      }
    },
    async deleteNotification(notificationId: number) {
      try {
        await axios.delete<Notification>(`notifications/${notificationId}`)
        const index = this.notifications.findIndex(
          (notification) => notification.id === notificationId
        )
        if (index === -1) return
        this.notifications.splice(index, 1)
      } catch (e) {
        console.error(e)
      }
    },
    async markNotificationAsRead(notificationId: number) {
      try {
        const { data } = await axios.post<Notification>(`notifications/${notificationId}`)
        const index = this.notifications.findIndex(
          (notification) => notification.id === notificationId
        )
        if (index === -1) return
        this.notifications[index] = data
      } catch (e) {
        console.error(e)
      }
    }
  }
})

export default useNotificationStore
