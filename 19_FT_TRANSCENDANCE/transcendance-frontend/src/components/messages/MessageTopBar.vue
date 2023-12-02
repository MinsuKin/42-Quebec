<template>
  <div class="flex my-1 align-center text-medium-emphasis">
    <v-btn
      variant="text"
      color="default"
      icon
      size="small"
      class="d-md-none me-3"
      :active="isLeftSidebarOpen"
      @click.stop.prevent="isLeftSidebarOpen = !isLeftSidebarOpen"
    >
      <v-icon
        size="24"
        icon="tabler-menu-2"
      />
    </v-btn>
    <template v-if="messageStore.conversationWith">
      <div
        class="flex cursor-pointer align-center"
        @click.stop="showProfile"
      >
        <avatar-badge
          :user-id="messageStore.conversationWith.id"
          :user="messageStore.conversationWith"
          :show-name="true"
        />
        <span class="pl-2 text-sm text-primary line-clamp-1">
          @{{ messageStore.conversationWith.username }}</span>
      </div>
      <v-chip
        v-if="blockedStatus !== 'none'"
        class="ml-2"
        append-icon="tabler-lock"
        color="error"
      >
        <template v-if="blockedStatus === 'mutual'">
          Mutuellement bloquer
        </template>
        <template v-else-if="blockedStatus === 'blocked'">
          Vous avez bloquer
        </template>
        <template v-else-if="blockedStatus === 'blockedBy'">
          Vous a bloquer
        </template>
      </v-chip>
      <VSpacer />
      <div class="flex items-center">
        <game-status-badge :user-id="messageStore.conversationWith.id" />
      </div>
      <VBtn
        variant="text"
        color="default"
        icon
        size="small"
      >
        <v-icon
          size="22"
          icon="tabler-dots-vertical"
        />
        <v-menu activator="parent">
          <v-list>
            <VListItem
              prepend-icon="tabler-eye"
              @click.stop="showProfile"
            >
              <VListItemTitle> Voir le profil</VListItemTitle>
            </VListItem>
            <VListItem
              v-if="blockedStatus === 'none'"
              prepend-icon="tabler-ban"
              @click.stop="blockContact"
            >
              <VListItemTitle>Bloquer</VListItemTitle>
            </VListItem>
            <VListItem
              v-else-if="blockedStatus === 'blocked' || blockedStatus === 'mutual'"
              prepend-icon="tabler-ban"
              @click.stop="unblockContact"
            >
              <VListItemTitle>Debloquer le contact</VListItemTitle>
            </VListItem>
          </v-list>
        </v-menu>
      </VBtn>
    </template>
  </div>
</template>

<script lang="ts">
import { defineComponent, PropType } from 'vue'
import useMessageStore from '@/stores/MessageStore'
import useUserStore, { BlockedStatus, FriendshipStatus } from '@/stores/UserStore'
import AvatarBadge from '@/components/profile/AvatarBadge.vue'
import GameStatusBadge from '@/components/game/GameStatusBadge.vue'

export default defineComponent({
  name: 'MessageTopBar',
  components: {
    GameStatusBadge,
    AvatarBadge
  },
  props: {
    friendshipStatus: {
      type: String as PropType<FriendshipStatus>,
      required: true,
      default: FriendshipStatus.None
    },
    blockedStatus: {
      type: String as PropType<BlockedStatus>,
      required: true,
      default: BlockedStatus.None
    },
    loadingStatus: {
      type: Boolean,
      required: false,
      default: false
    }
  },
  emits: ['updateFriendshipStatus'],
  setup() {
    const usersStore = useUserStore()
    const messageStore = useMessageStore()
    return {
      messageStore,
      usersStore
    }
  },
  computed: {
    isLeftSidebarOpen: {
      get(): boolean {
        return this.messageStore.isSidebarOpen
      },
      set(value: boolean) {
        this.messageStore.setSidebarOpen(value)
      }
    }
  },
  methods: {
    async blockContact() {
      if (!this.messageStore.conversationWith) return
      await this.usersStore.blockUser(this.messageStore.conversationWith.id)
      this.$nextTick(() => {
        this.$emit('updateFriendshipStatus')
      })
    },
    async unblockContact() {
      if (!this.messageStore.conversationWith) return
      await this.usersStore.unblockUser(this.messageStore.conversationWith.id)
      this.$nextTick(() => {
        this.$emit('updateFriendshipStatus')
      })
    },
    async showProfile() {
      if (!this.messageStore.conversationWith) return
      this.$router.push({
        name: 'user-profile',
        params: { userId: this.messageStore.conversationWith.id }
      })
    }
  }
})
</script>

<style scoped></style>
