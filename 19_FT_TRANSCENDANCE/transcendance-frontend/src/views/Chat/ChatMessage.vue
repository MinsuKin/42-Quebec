<template>
  <div :class="blocked ? 'blur-xl pointer-events-none' : ''">
    <div
      class="flex flex-col"
      :class="[isSender ? 'justify-end items-end' : 'order-2 text-left']"
    >
      <div
        :class="[
          'relative inline-block max-w-xs px-4 py-4 text-sm rounded-md shadow-lg drop-shadow-lg mb-2',
          isSender ? 'reply order-2' : 'sender order-1'
        ]"
        style="background-color: #272b47"
      >
        <p
          v-for="msg in msgGroup.messages"
          :key="msg.id"
          class="my-2 text-sm"
        >
          {{ msg.message }}
        </p>
      </div>
      <div
        class="items-center inline-block w-48 h-auto gap-4 text-xs font-light grow-0 shrink-0"
        :class="[isSender ? 'order-2 text-right' : 'order-2 text-left']"
      >
        <span class="text-xs text-gray-400">
          {{
            formatDate(msgGroup.messages[msgGroup.messages.length - 1].time, {
              hour: 'numeric',
              minute: 'numeric'
            })
          }}
        </span>
        <div
          class="flex items-center gap-2"
          :class="[isSender ? 'justify-end' : 'justify-start']"
        >
          <span class="line-clamp-1">{{ sender?.member.username.split(' ').shift() }}</span>
          <VIcon
            v-if="isOwner"
            :size="16"
            color="primary"
          >
            tabler-crown
          </VIcon>
          <VIcon
            v-else-if="isAdmin"
            :size="16"
            color="secondary"
          >
            tabler-shield-check
          </VIcon>
          <VIcon
            v-else-if="isBan"
            :size="16"
            color="gray"
          >
            tabler-user-x
          </VIcon>
          <VIcon
            v-else-if="isMuted"
            :size="16"
            color="gray"
          >
            tabler-user-minus
          </VIcon>
        </div>
      </div>
    </div>
  </div>
</template>
<script lang="ts">
import { defineComponent, PropType } from 'vue'
import { formatDate } from '@core/utils/formatters'
import useRoomsStore, { MemberRoomWithUserProfiles } from '@/stores/RoomsStore'
import { BlockedStatus } from '@/stores/UserStore'
import { ChatMemberRole } from '@/utils/chatSocket'

interface ChatMessageGroup {
  senderId: number
  messages: Array<{ id: number; message: string; time: string }>
}

export default defineComponent({
  props: {
    msgGroup: {
      type: Object as PropType<ChatMessageGroup>,
      required: true,
      default: () => ({ senderId: 0, messages: [], time: new Date().toTimeString() })
    },
    isSender: {
      type: Boolean,
      required: true
    }
  },
  setup() {
    const roomStore = useRoomsStore()
    return {
      roomStore
    }
  },
  computed: {
    sender(): MemberRoomWithUserProfiles | undefined {
      return this.roomStore.roomMembers.find(
        (member) => member.member.id === this.msgGroup.senderId
      )
    },
    isBan(): boolean {
      return this.sender?.role === ChatMemberRole.BAN
    },
    isAdmin(): boolean {
      return this.sender?.role === ChatMemberRole.ADMIN
    },
    isOwner(): boolean {
      return this.sender?.role === ChatMemberRole.OWNER
    },
    isMuted(): boolean {
      return this.sender?.role === ChatMemberRole.MUTED
    },
    blocked(): boolean {
      if (!this.sender && this.roomStore.isMemberOfRoom) return false
      if (!this.sender) return true
      const blockStatus = this.roomStore.allBlockedStatus.get(this.sender.member.id)
      if (!blockStatus) return false
      // one of the two block the other
      return blockStatus !== BlockedStatus.None
    }
  },
  methods: {
    formatDate
  }
})
</script>
<style lang="scss">
.sender::before {
  display: block;
  clear: both;
  content: '';
  position: absolute;
  top: -6px;
  left: -7px;
  width: 0;
  height: 0;
  border-style: solid;
  border-width: 0 12px 15px 12px;
  border-color: transparent transparent #272b47 transparent;
  -webkit-transform: rotate(-37deg);
  -ms-transform: rotate(-37deg);
  transform: rotate(-37deg);
}
.reply::before {
  display: block;
  clear: both;
  content: '';
  position: absolute;
  bottom: -5px;
  right: -7.5px;
  width: 0;
  height: 0;
  border-style: solid;
  border-width: 0 12px 15px 12px;
  border-color: transparent transparent #272b47 transparent;
  -webkit-transform: rotate(37deg);
  -ms-transform: rotate(37deg);
  transform: rotate(37deg);
}
</style>
