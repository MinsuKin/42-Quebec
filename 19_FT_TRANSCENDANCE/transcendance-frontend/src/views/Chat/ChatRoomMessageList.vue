<template>
  <div class="h-full">
    <div
      class="w-full h-full overflow-sroll"
      :class="canRead ? '' : 'blur-sm'"
    >
      <perfect-scrollbar
        id="messages-log"
        ref="MessagesLogScroller"
        tag="ul"
        :options="{ wheelPropagation: false, suppressScrollX: true }"
        class="flex flex-col h-full gap-4 px-4 pt-6 pb-32 overflow-scroll hide-scrollbar"
      >
        <li
          v-for="(msgGrp, index) in msgGroups"
          :key="`message-group-${index}-${msgGrp.senderId}`"
          :class="msgGrp.senderId === roomStore.userId ? 'self-end' : 'self-start'"
        >
          <chat-message
            :is-sender="msgGrp.senderId === roomStore.userId"
            :msg-group="msgGrp"
          />
        </li>
        <li
          v-if="isTypingUserName"
          class="pb-4 font-weight-medium"
        >
          <p>
            <span class="text-primary">{{ isTypingUserName }}</span> est en train d'écrire...
          </p>
        </li>
      </perfect-scrollbar>
    </div>

    <div
      class="absolute w-full px-8 py-2 h-[65px] bottom-0 bg-gradient-to-b from-[#262A46]/0 to-[80%] to-[#262A46]"
    >
      <form
        action=""
        class="flex items-center justify-center w-full h-full"
      >
        <div class="w-full h-[40px] relative">
          <div
            v-if="roomStore.isMuted"
            class="absolute left-0 z-50 flex items-center justify-center w-full h-full -top-5"
          >
            <p class="text-xs text-primary">
              Vous pouvez écrire dans
              <span class="text-xs text-primary">
                {{ canWriteAt }}
              </span>
            </p>
          </div>
          <div
            v-if="me && roomStore.isBanned"
            class="absolute left-0 z-50 flex items-center justify-center w-full h-full -top-5"
          >
            <p class="text-xs text-primary">
              Vous avez été banni de ce salon
            </p>
          </div>
          <VForm @submit.prevent="sendMessage">
            <VTextField
              v-model="chatMessageContent"
              :disabled="!canWrite"
              variant="solo"
              placeholder="Envoyer un message dans le chat"
              density="default"
              class="h-full px-4 -mt-5 text-sm font-light disabled:blur-md"
              autofocus
              @keypress="sendIsTyping"
            >
              <template #append-inner>
                <v-btn
                  color="transparent"
                  class="absolute -translate-y-1/2 border right-2 top-1/2"
                  size="26"
                  icon
                  @click="sendMessage"
                >
                  <v-icon
                    color="primary"
                    size="16"
                    icon="mingcute:send-fill"
                  />
                </v-btn>
              </template>
            </VTextField>
          </VForm>
        </div>
      </form>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import { PerfectScrollbar } from 'vue3-perfect-scrollbar'
import ChatMessage from '@/views/Chat/ChatMessage.vue'
import useRoomsStore from '@/stores/RoomsStore'
import useAuthStore from '@/stores/AuthStore'
import { ChatMessage as ChatMessageT, ChatRoomMember } from '@/utils/chatSocket'

interface ChatMessageGroup {
  senderId: number
  messages: Array<{ id: number; message: string; time: string }>
}
export default defineComponent({
  components: { PerfectScrollbar, ChatMessage },
  setup() {
    const authStore = useAuthStore()
    const roomStore = useRoomsStore()
    return {
      authStore,
      roomStore
    }
  },
  data() {
    return {
      take: 400,
      skip: 0,
      chatMessageContent: '',
      loading: false,
      isTypingUserName: '',
      timer: null as NodeJS.Timeout | null,
      canWriteAt: '',
    }
  },
  computed: {
    me(): ChatRoomMember | undefined {
      return this.roomStore.roomMembers.find((member) => member.member.id === this.roomStore.userId)
    },
    expiresAt(): number {
      if (!this.me) return new Date().getTime()
      return new Date(this.me?.unMuteAt).getTime()
    },
    canRead(): boolean {
      if (!this.me) return false
      return !this.roomStore.isBanned
    },
    canWrite(): boolean {
      if (!this.me) return false
      return !this.roomStore.isBanned && !this.roomStore.isMuted
    },
    messages(): ChatMessageT[] {
      return this.roomStore.getCurrentRoomMessages
    },
    messagesByTime(): ChatMessageT[] {
      return this.messages.slice().sort((a, b) => {
        return new Date(a.timestamp).getTime() - new Date(b.timestamp).getTime()
      })
    },
    msgGroups(): ChatMessageGroup[] {
      if (this.messagesByTime.length === 0) return []
      const _msgGroups: ChatMessageGroup[] = []
      const messages = this.messagesByTime
      let msgSenderId = messages[0].userId
      let msgGroup: ChatMessageGroup = {
        senderId: msgSenderId,
        messages: []
      }
      messages.forEach((msg: ChatMessageT, index) => {
        if (msgSenderId === msg.userId) {
          msgGroup.messages.push({ id: msg.id, message: msg.content, time: msg.timestamp })
        } else {
          msgSenderId = msg.userId
          _msgGroups.push(msgGroup)
          msgGroup = {
            senderId: msg.userId,
            messages: [
              {
                id: msg.id,
                message: msg.content,
                time: msg.timestamp
              }
            ]
          }
        }
        if (index === messages.length - 1) _msgGroups.push(msgGroup)
      })
      return _msgGroups
    }
  },
  watch: {
    'roomStore.currentRoom': {
      handler(value: number) {
        if (!value) return
        if (!this.roomStore.isMemberOfRoom && !this.roomStore.isPublic) return
        this.fetchMessages();
        if (this.roomStore.isMuted){
          this.startMuteCountDown();
        }
      },
      immediate: true
    },
    'roomStore.getRoomMembersTyping': {
      handler() {
        if (!this.roomStore.currentRoom) return
        const lastTypingUserInRoom = this.roomStore.getRoomMembersTyping.get(
          this.roomStore.currentRoom.id
        )
        if (!lastTypingUserInRoom) return
        const now = new Date().getTime()
        const isTyping = now - lastTypingUserInRoom.timestamp < 2000
        if (isTyping) {
          this.isTypingUserName = lastTypingUserInRoom.username
          setTimeout(() => {
            this.isTypingUserName = ''
          }, 1000)
        } else {
          this.isTypingUserName = ''
        }
      },
      deep: true,
      immediate: true
    },
    messages: {
      handler() {
        this.$nextTick(() => {
          this.scrollToBottomInChatLog()
        })
      },
      deep: true
    }
  },
  mounted() {
    this.scrollToBottomInChatLog()
  },
  beforeUnmount() {
    if (this.timer) clearInterval(this.timer)
  },
  methods: {
    async fetchMessages() {
      this.loading = true
      if (!this.roomStore.currentRoom) return
      // to allow public room to be read
      if (!this.canRead && !this.roomStore.isPublic) return
      await this.roomStore.loadCurrentRoomMessages({ skip: this.skip, take: this.take })
      this.loading = false
      this.$nextTick(() => {
        this.scrollToBottomInChatLog()
      })
    },
    async sendMessage() {
      if (!this.me) return
      if (!this.chatMessageContent.trim()) return
      if (this.loading) return
      this.loading = true
      this.roomStore.sendMessage(this.me.chatroomId, this.chatMessageContent)
      this.chatMessageContent = ''
      this.loading = false
      this.$nextTick(() => {
        this.scrollToBottomInChatLog()
      })
    },
    async sendIsTyping() {
      if (!this.me) return
      if (!this.authStore.getUser) return
      this.roomStore.sendUserIsTypingInRoom(this.me.chatroomId, this.authStore.getUser.username)
    },
    startMuteCountDown(){
      this.timer = setInterval(this.getTimeRemaining, 1000);
    },
    getTimeRemaining() {
      const now = Date.now()
      const timeDifference = this.expiresAt - now
      if (timeDifference <= 0) {
        this.canWriteAt = ''
        if (this.timer){
          clearInterval(this.timer);
          this.roomStore.reloadCurrentRoomMembers();
          this.timer = null;
        }
        return
      } else {
        const seconds = Math.floor((timeDifference / 1000) % 60)
        const minutes = Math.floor((timeDifference / (1000 * 60)) % 60)
        const hours = Math.floor((timeDifference / (1000 * 60 * 60)) % 24)
        const days = Math.floor(timeDifference / (1000 * 60 * 60 * 24))

        let rtn = ''
        if (days > 0) {
          rtn += `${days} jours `
        }

        if (hours > 0) {
          rtn += `${hours} heure(s) `
        }

        if (minutes > 0) {
          rtn += `${minutes} minute(s) `
        }

        if (seconds > 0) {
          rtn += `${seconds} seconde(s)`
        }

        this.canWriteAt = rtn
      }
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
    }
  }
})
</script>

<style scoped></style>
