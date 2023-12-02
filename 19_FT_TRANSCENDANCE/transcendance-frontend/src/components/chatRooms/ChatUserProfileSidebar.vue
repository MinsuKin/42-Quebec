<template>
  <div class="pt-2 me-2 text-end">
    <VBtn
      variant="text"
      color="error"
      icon
      size="small"
      @click="$emit('close')"
    >
      <VIcon
        size="18"
        class="text-medium-emphasis"
        icon="tabler-x"
      />
    </VBtn>
  </div>
  <div class="text-end">
    <VBtn
      v-if="$vuetify.display.smAndDown"
      variant="text"
      color="default"
      icon
      size="small"
      @click="$emit('close')"
    >
      <VIcon
        size="18"
        icon="tabler-x"
        color="error"
        class="text-medium-emphasis"
      />
    </VBtn>
  </div>
  <div
    v-if="authStore.getProfile"
    class="text-center px-6"
  >
    <VBadge
      location="bottom right"
      offset-x="7"
      offset-y="4"
      bordered
      :color="authStore.resolveAvatarBadgeVariant(authStore.getProfile?.status)"
      class="chat-user-profile-badge mb-5"
    >
      <VAvatar
        size="84"
        variant="tonal"
        :class="`text-${authStore.resolveAvatarBadgeVariant(authStore.getProfile?.status)}`"
      >
        <VImg
          v-if="authStore.getProfile?.avatar"
          :src="authStore.getProfile?.avatar"
        />
        <span
          v-else
          class="text-3xl"
        >{{
          avatarText(authStore.getUser?.username ?? 'no username')
        }}</span>
      </VAvatar>
    </VBadge>
    <h2 class="mb-1 text-high-emphasis font-weight-medium text-base">
      {{ authStore.getUser?.username }}
    </h2>
    <h6>{{ authStore.getProfile?.name }} {{ authStore.getProfile?.lastname }}</h6>
  </div>
  <div
    v-if="roomsStore.currentRoom"
    class="mb-5 w-full"
  >
    <p class="text-md text-center font-weight-bold py-2">
      STATUS
    </p>
    <p
      class="text-center font-weight-semibold"
      :class="`text-${printedRole?.bgClass}`"
    >
      {{ printedRole?.printRole }}
      sur le groupe selectionné
    </p>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore from '@/stores/AuthStore'
import { Status } from '@/interfaces/User'
import { avatarText } from '@core/utils/formatters'
import useRoomsStore, { rolePrint } from '@/stores/RoomsStore'
import { ChatMemberRole } from '@/utils/chatSocket'

export default defineComponent({
  name: 'ChatUserProfileSidebar',
  emits: ['close'],
  setup() {
    const authStore = useAuthStore()
    const roomsStore = useRoomsStore()
    return {
      authStore,
      roomsStore
    }
  },
  data() {
    return {
      userStatusOptions: [
        { title: 'En ligne', value: Status.Online, color: 'success' },
        { title: 'Away', value: Status.Away, color: 'warning' },
        { title: 'Ne pas déranger', value: Status.Busy, color: 'error' },
        { title: 'Hors ligne', value: Status.Offline, color: 'secondary' }
      ]
    }
  },
  computed: {
    status: {
      get(): Status {
        return this.authStore.visibleStatus
      },
      set(value: Status) {
        this.authStore.changeMyStatus(value)
      }
    },
    role(): ChatMemberRole {
      const room = this.roomsStore.currentRoom
      if (room) {
        const member = room.members.find((member) => {
          if (!this.authStore.getUser) return false
          return member.id === this.authStore.getUser.id
        })
        if (member) return member.role
      }
      return ChatMemberRole.USER
    },
    printedRole():
      | { role: ChatMemberRole; printRole: string; color?: string; bgClass?: string }
      | undefined {
      return rolePrint.find((role) => role.role === this.role)
    }
  },
  methods: {
    avatarText
  }
})
</script>

<style scoped></style>
