<template>
  <div class="flex flex-col w-full h-full">
    <div class="border-b border-gray-50 flex-0">
      <message-top-bar
        :friendship-status="friendShipStatus"
        :blocked-status="blockedStatus"
        :loading-status="loadingStatus"
        @update-friendship-status="fetchFriendShipState"
      />
      <VDivider class="d-md-none" />
    </div>
    <template v-if="messageStore.conversationWith && !loading">
      <div class="flex-1 w-full overflow-scroll hide-scrollbar">
        <div class="flex flex-col w-full h-full gap-4 hide-scrollbar">
          <PerfectScrollbar
            id="messages-log"
            ref="MessagesLogScroller"
            tag="ul"
            :options="{
              wheelPropagation: false,
              suppressScrollX: true
            }"
            class="h-full"
          >
            <ul>
              <li
                v-for="(msgGrp, index) in msgGroups"
                :key="index"
                class="p-2"
                :class="
                  msgGrp.senderId !== messageStore.conversationWith.id
                    ? 'self-end text-right'
                    : 'self-start'
                "
              >
                <p
                  class="relative message inline-flex flex-col px-6 min-w-[75px] py-2 border shadow-sm rounded-xl drop-shadow-md after:content-[''] after:h-4 after:absolute after:top-full after:translate-x-full after:w-4 after:-z-10 after:-translate-y-1/4"
                  :class="
                    msgGrp.senderId !== messageStore.conversationWith.id
                      ? 'text-left mr-0 ml-auto bg-[#1a1f3c] after:bg-[#1a1f3c]'
                      : 'text-left bg-[#343851] after:bg-[#343851]'
                  "
                >
                  <private-message
                    v-for="msgData in msgGrp.messages"
                    :key="msgData.id"
                    :message="msgData"
                  />
                </p>
                <span class="text-[.5rem] text-gray-50/90 font-thin block mt-4 px-4">
                  {{
                    formatDate(msgGrp.messages[msgGrp.messages.length - 1].time, {
                      hour: 'numeric',
                      minute: 'numeric'
                    })
                  }}
                </span>
              </li>
              <li
                class="p-2"
                :class="'self-start text-left text-sm px-6 h-8'"
              >
                <p
                  v-if="isTyping"
                  class="font-light"
                >
                  {{ messageStore.conversationWith.profile.name.split(' ').shift() }}
                  <span class="pr-1">est en train d'écrire</span>
                  <v-icon
                    :size="12"
                    color="primary"
                    icon="svg-spinners:3-dots-bounce"
                  />
                </p>
              </li>
            </ul>

            <div class="w-full h-4 shrink-0 grow-0" />
          </PerfectScrollbar>
        </div>
      </div>
      <div class="border rounded-md shadow-lg flex-0 drop-shadow-lg">
        <VForm @submit.prevent.stop="sendMessage">
          <VTextField
            v-model.lazy.trim="mpContent"
            :disabled="!canWrite"
            variant="solo"
            placeholder="Ecrivez votre message..."
            density="default"
            :autofocus="true"
            @keyup="handleUserTyping"
          >
            <template #append-inner>
              <VBtn
                rounded
                @click.prevent.stop="sendMessage"
              >
                <svg
                  class="w-4 h-4 text-current fill-current"
                  xmlns="http://www.w3.org/2000/svg"
                  viewBox="0 0 24 24"
                >
                  <path
                    d="M24 0l-6 22-8.129-7.239 7.802-8.234-10.458 7.227-7.215-1.754 24-12zm-15 16.668v7.332l3.258-4.431-3.258-2.901z"
                  />
                </svg>
              </VBtn>
            </template>
          </VTextField>
        </VForm>
      </div>
    </template>
    <div
      v-else-if="loading"
      class="flex items-center justify-center h-full"
    >
      <v-progress-circular
        :size="70"
        :width="7"
        color="sky"
        indeterminate
      />
    </div>
  </div>
</template>

<script lang="ts">
import useMessageStore, { PrivateMessage as PrivateMessageT } from '@/stores/MessageStore'
import { defineComponent } from 'vue'
import { Profile, User } from '@/interfaces/User'
import MessageTopBar from '@/components/messages/MessageTopBar.vue'
import { formatDate } from '@/vuetify/@core/utils/formatters'
import { PerfectScrollbar } from 'vue3-perfect-scrollbar'
import useRoomsStore from '@/stores/RoomsStore'
import useUserStore, { BlockedStatus, FriendshipStatus } from '@/stores/UserStore'
import useNotificationStore from '@/stores/NotificationStore'
import { RealTimeNotification, RealTimeNotificationTitle } from '@/utils/notificationSocket'
import PrivateMessage from '@/components/messages/PrivateMessage.vue'

interface MessageGroup {
  senderId: number
  messages: Array<{ id: number; message: string; time: string }>
}

export default defineComponent({
  components: {
    PrivateMessage,
    MessageTopBar,
    PerfectScrollbar
  },
  setup() {
    const messageStore = useMessageStore()
    const roomsStore = useRoomsStore()
    const usersStore = useUserStore()
    const notificationStore = useNotificationStore()
    return {
      messageStore,
      roomsStore,
      usersStore,
      notificationStore
    }
  },
  data() {
    return {
      loading: false,
      loadingStatus: false,
      take: 400,
      skip: 0,
      mpContent: '',
      friendShipStatus: FriendshipStatus.None as FriendshipStatus,
      blockedStatus: BlockedStatus.None as BlockedStatus,
      isTyping: false,
      lastInteraction: null as unknown as number
    }
  },
  computed: {
    messagesByTime(): PrivateMessageT[] {
      return this.messageStore.currentContactMessages.slice().sort((a, b) => {
        return new Date(a.timestamp).getTime() - new Date(b.timestamp).getTime()
      })
    },
    msgGroups(): MessageGroup[] {
      if (this.messagesByTime.length === 0) return []
      const _msgGroups: MessageGroup[] = []
      const messages = this.messagesByTime
      let msgSenderId = messages[0].senderId
      let msgGroup: MessageGroup = {
        senderId: msgSenderId,
        messages: []
      }
      messages.forEach((msg: PrivateMessageT, index) => {
        if (msgSenderId === msg.senderId) {
          msgGroup.messages.push({ id: msg.id, message: msg.text, time: msg.timestamp })
        } else {
          msgSenderId = msg.senderId
          _msgGroups.push(msgGroup)
          msgGroup = {
            senderId: msg.senderId,
            messages: [
              {
                id: msg.id,
                message: msg.text,
                time: msg.timestamp
              }
            ]
          }
        }
        if (index === messages.length - 1) _msgGroups.push(msgGroup)
      })
      return _msgGroups
    },
    canWrite(): boolean {
      if (!this.messageStore.conversationWith) return false
      return this.blockedStatus === BlockedStatus.None
    }
  },
  watch: {
    'messageStore.conversationWith': {
      handler(value: (User & { profile: Profile }) | null) {
        if (!value) return
        this.fetchFriendShipState()
        this.loadPrivateMessages(value.id)
      },
      deep: true,
      immediate: true
    },
    messagesByTime: {
      handler() {
        this.$nextTick(() => {
          this.scrollToBottomInChatLog()
        })
      },
      deep: true
    },
    'roomsStore.getContactTyping': {
      handler() {
        if (!this.messageStore.conversationWith) return
        const lastTime = this.roomsStore.getContactTyping.get(this.messageStore.conversationWith.id)
        if (!lastTime) return false
        const now = new Date().getTime()
        this.isTyping = now - lastTime < 3000
      },
      deep: true,
      immediate: true
    },
    isTyping: {
      handler(value) {
        this.$nextTick(() => {
          this.scrollToBottomInChatLog()
        })
        if (!value) return
        setTimeout(() => {
          this.isTyping = false
        }, 1000)
      },
      deep: true,
      immediate: true
    },
    'notificationStore.allRealTimeNotifications': {
      handler(value: RealTimeNotification[]) {
        if (value.length === 0) return
        this.checkAndRefreshFriendShip(value[0])
      },
      deep: true
    }
  },
  mounted() {
    this.scrollToBottomInChatLog()
  },
  methods: {
    async fetchFriendShipState() {
      if (!this.messageStore.conversationWith) {
        this.friendShipStatus = FriendshipStatus.None
        this.blockedStatus = BlockedStatus.None
        return
      }
      this.loadingStatus = true
      const contactId = this.messageStore.conversationWith.id
      const checkFriend = await this.usersStore.checkFriendShip(contactId)
      this.friendShipStatus = checkFriend.status
      this.blockedStatus = await this.usersStore.checkBlocked(contactId)
      this.loadingStatus = false
    },
    async checkAndRefreshFriendShip(notification: RealTimeNotification) {
      if (!this.messageStore.conversationWith) return
      if (
        notification.title === RealTimeNotificationTitle.BlockedContactMessage ||
        notification.title === RealTimeNotificationTitle.BrokenFriendship
      ) {
        if (
          notification.sourceUserId === this.messageStore.conversationWith.id ||
          notification.userId === this.messageStore.conversationWith.id
        ) {
          await this.fetchFriendShipState()
        }
      }
    },
    async loadPrivateMessages(id: number) {
      this.loading = true
      await this.messageStore.getPrivateMessageBetween({
        userTwoId: id,
        skip: this.skip,
        take: this.take
      })
      this.loading = false
      this.$nextTick(() => {
        this.scrollToBottomInChatLog()
      })
    },
    async sendMessage() {
      if (this.loading) return
      if (!this.messageStore.conversationWith) return
      if (!this.mpContent.trim()) return
      this.loading = true
      const id = this.messageStore.conversationWith.id
      this.messageStore.sendPrivateMessage(id, this.mpContent.trim())
      this.mpContent = ''
      this.loading = false
      this.$nextTick(() => {
        this.scrollToBottomInChatLog()
      })
    },
    async handleUserTyping() {
      const now = new Date().getTime()
      if (!this.messageStore.conversationWith) return
      const id = this.messageStore.conversationWith.id
      if (this.lastInteraction && now - (this.lastInteraction as number) > 50) {
        this.messageStore.sendUserTyping(id)
        this.lastInteraction = now
      } else this.lastInteraction = now
    },
    scrollToBottomInChatLog() {
      const el = this.$refs.MessagesLogScroller?.$el as HTMLElement
      if (el) {
        el.scrollTop = el.scrollHeight
      }
    },
    scrollToTopInChatLog() {
      const el = this.$refs.MessagesLogScroller?.$el as HTMLElement
      if (el) {
        el.scrollTop = 0
      }
    },
    formatDate
  }
})
</script>

<style lang="scss" scoped></style>
