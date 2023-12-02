<template>
  <li
    v-if="contact"
    class="flex flex-col px-2 pb-2 rounded-lg cursor-pointer hover:bg-darkBlue"
    :class="{ 'bg-darkBlue/50': isActive }"
    @click.stop="showThisConversation"
  >
    <div class="flex items-center gap-2 p-2">
      <avatar-badge
        :user-id="contact.id"
        :user="contact"
        :avatar-variant="isActive ? 'outlined' : 'tonal'"
        :size="32"
      />
      <span
        class="font-weight-medium line-clamp-1"
        :class="{ 'font-weight-bold': isActive }"
      >
        {{ contact.profile.name.split(' ').shift() }} {{ contact.profile.lastname }}
      </span>
    </div>
    <div class="flex items-center justify-center px-4">
      <span
        v-if="canShowLastMessage && lastMessage"
        class="w-full ml-16 -mt-2 text-xs font-light text-disabled shrink-0 line-clamp-1"
      >
        {{ lastMessage.text }}
      </span>
      <p
        v-else-if="isTyping"
        class="w-full ml-16 -mt-2 text-xs font-light shrink-0"
      >
        {{ contact.profile.name.split(' ').shift() }}
        <span class="pr-1">est en train d'écrire</span>
        <v-icon
          :size="12"
          color="primary"
          icon="svg-spinners:3-dots-bounce"
        />
      </p>
    </div>
  </li>
</template>

<script lang="ts">
import { defineComponent, PropType } from 'vue'
import useMessageStore, { PrivateMessage } from '@/stores/MessageStore'
import AvatarBadge from '@/components/profile/AvatarBadge.vue'
import useRoomsStore from '@/stores/RoomsStore'
import { ShortUserProfile } from '@/stores/UserStore'

export default defineComponent({
  components: { AvatarBadge },
  props: {
    contact: {
      type: Object as PropType<ShortUserProfile>,
      required: true
    },
    showLastMessage: {
      type: Boolean,
      required: false,
      default: false
    }
  },
  emits: ['openChatOfContact'],
  setup() {
    const messageStore = useMessageStore()
    const roomsStore = useRoomsStore()
    return {
      messageStore,
      roomsStore
    }
  },
  data() {
    return {
      isTyping: false,
      lastMessage: null as PrivateMessage | null
    }
  },
  computed: {
    isActive() {
      return this.messageStore.currentContactId === this.contact.id
    },
    canShowLastMessage() {
      return this.showLastMessage && !this.isTyping
    }
  },
  watch: {
    'roomsStore.getContactTyping': {
      handler() {
        if (!this.contact) return
        const lastTime = this.roomsStore.getContactTyping.get(this.contact.id)
        if (!lastTime) return false
        const now = new Date().getTime()
        this.isTyping = now - lastTime < 3000
      },
      deep: true,
      immediate: true
    },
    'messageStore.messages': {
      handler() {
        this.lastMessage = this.messageStore.getLastMessageBetween(this.contact.id)
      },
      deep: true,
      immediate: true
    },
    isTyping: {
      handler(value) {
        if (!value) return
        setTimeout(() => {
          this.isTyping = false
        }, 1000)
      },
      deep: true,
      immediate: true
    }
  },
  methods: {
    showThisConversation() {
      this.$emit('openChatOfContact', this.contact.id)
    }
  }
})
</script>

<style scoped lang="scss"></style>
