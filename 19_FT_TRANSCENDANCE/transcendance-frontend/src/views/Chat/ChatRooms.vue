<template>
  <section class="w-full h-full overflow-auto border rounded-md">
    <div class="relative flex w-full h-full overflow-hidden flex-nowrap">
      <chat-left-nav
        @create-room="showCreateRoomForm = !showCreateRoomForm"
        @show-room="changeRoom"
      />
      <chat-room :is-loading="loading" />
      <chat-right-nav :is-loading="loading" />
    </div>
  </section>
</template>
<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore from '@/stores/AuthStore'
import useRoomsStore from '@/stores/RoomsStore'
import useUserStore from '@/stores/UserStore'
import { ChatRoom as ChatRoomT } from '@/utils/chatSocket'
import ChatLeftNav from './ChatLeftNav.vue'
import ChatRightNav from './ChatRightNav.vue'
import ChatRoom from './ChatRoom.vue'
import { RealTimeNotification, RealTimeNotificationTitle } from '@/utils/notificationSocket'
import useNotificationStore from '@/stores/NotificationStore'

export default defineComponent({
  components: {
    ChatLeftNav,
    ChatRightNav,
    ChatRoom
  },
  props: {
    roomId: {
      type: Number,
      required: false,
      default: undefined
    }
  },
  setup() {
    const authStore = useAuthStore()
    const roomsStore = useRoomsStore()
    const userStore = useUserStore()
    const notificationStore = useNotificationStore()
    return {
      authStore,
      roomsStore,
      userStore,
      notificationStore
    }
  },
  data() {
    return {
      loading: false,
      errorRoomAccessMsg: '',
      showCreateRoomForm: false,
      showErrorPopUp: false,
      isRightSidebarOpen: false
    }
  },
  watch: {
    roomId: {
      handler(value) {
        this.accessRoom(value)
      },
      immediate: true
    },
    'roomsStore.currentRoom': {
      handler(value: ChatRoomT | undefined) {
        if (value) {
          document.title = `${value.name} - Room | Transcendence`
        }
      },
      immediate: true
    },
    'notificationStore.allRealTimeNotifications': {
      handler(value: RealTimeNotification[]) {
        if (value.length === 0) return
        this.checkAndRefreshRoom(value[0])
        this.checkAndRefreshStatus(value[0])
        this.checkAndRefreshMembers(value[0])
      },
      deep: true,
      immediate: true
    }
  },
  async beforeMount() {
    this.loading = true
    await this.roomsStore.getAllMyRooms()
    await this.roomsStore.fetchPublicRooms()
    this.loading = false
    if (this.roomId) {
      await this.accessRoom(this.roomId)
    }
  },
  methods: {
    async accessRoom(roomId?: number) {
      if (!roomId) return
      this.loading = true
      await this.roomsStore.selectRoom(roomId)
      this.loading = false
    },
    changeRoom(roomId: number) {
      this.$router.push({ name: 'chat', params: { roomId: roomId } })
    },
    async checkAndRefreshRoom(notification: RealTimeNotification) {
      if (
        notification.title === RealTimeNotificationTitle.ChatRoomSettingsUpdated ||
        notification.title === RealTimeNotificationTitle.ChatRoomDeleted
      ) {
        await this.roomsStore.getAllMyRooms()
        await this.roomsStore.fetchPublicRooms()
        if (!this.roomsStore.currentRoom) return
        this.loading = true
        // will re select the room, loading all datas again, and settings
        await this.roomsStore.selectRoom(this.roomsStore.currentRoom.id)
        this.loading = false
      }
      if (notification.title === RealTimeNotificationTitle.RemovedFromChatRoom) {
        await this.roomsStore.getAllMyRooms()
        await this.roomsStore.fetchPublicRooms()
        if (!this.roomsStore.currentRoom) return
        if (this.roomsStore.currentRoom.id === notification.roomId) {
          await this.roomsStore.selectRoom(this.roomsStore.currentRoom.id)
        }
      }
    },
    async checkAndRefreshMembers(notification: RealTimeNotification) {
      if (
        notification.title === RealTimeNotificationTitle.NewRolesInChatRoom ||
        notification.title === RealTimeNotificationTitle.NewMemberInChatRoom
      ) {
        await this.roomsStore.getAllMyRooms()
        await this.roomsStore.fetchPublicRooms();
        await this.roomsStore.reloadCurrentRoomMembers()
        if (!this.roomsStore.currentRoom) return;
        if (this.roomsStore.currentRoom.id === notification.roomId) {
          await this.roomsStore.selectRoom(this.roomsStore.currentRoom.id)
        }
      }
    },
    async checkAndRefreshStatus(notification: RealTimeNotification) {
      if (
        notification.title === RealTimeNotificationTitle.BlockedContactMessage ||
        notification.title === RealTimeNotificationTitle.BrokenFriendship
      ) {
        if (
          notification.sourceUserId === this.roomsStore.userId ||
          notification.userId === this.roomsStore.userId
        ) {
          // we fetch all blocked status for all members
          await this.roomsStore.setBlockedStatusForMembers(this.roomsStore.roomMembers)
        }
      }
    }
  }
})
</script>
<style lang="scss">
.h-\[65\] {
  height: 75px;
  bottom: 0rem;
}
.h-\[40px\] {
  height: 45px;
}
.relative {
  position: relative;
}
.bottom-\1\/2 {
  bottom: 50%;
}

.max-h-\1\/2 {
  height: 400px;
  max-height: 50%;
}
</style>
