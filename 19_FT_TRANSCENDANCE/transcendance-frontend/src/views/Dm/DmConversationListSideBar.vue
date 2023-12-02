<template>
  <div class="mt-2 text-end">
    <v-btn
      v-if="$vuetify.display.smAndDown"
      variant="text"
      color="default"
      icon
      size="small"
      @click="$emit('close')"
    >
      <v-icon
        size="18"
        icon="tabler-x"
        color="error"
        class="text-medium-emphasis"
      />
    </v-btn>
  </div>
  <div class="flex px-1 mb-2">
    <avatar-badge
      v-if="authStore.getUser"
      :user="authStore.getUser"
      :user-id="authStore.getUser.id"
      @show-user-profile="$emit('showUserProfile')"
    />
    <v-text-field
      v-model="search"
      density="compact"
      rounded
      placeholder="Chercher une conversation..."
      class="ms-4 me-1 transparent-input-box"
    >
      <template #prepend-inner>
        <v-icon
          size="22"
          icon="tabler-search"
        />
      </template>
    </v-text-field>
  </div>
  <VDivider />
  <PerfectScrollbar
    tag="ul"
    class="px-3 chat-contacts-list"
    :options="{ wheelPropagation: false }"
  >
    <li class="py-4">
      <span class="text-xl chat-contact-header text-primary font-weight-medium">
        Conversations
      </span>
    </li>
    <message-contact
      v-for="contact in messageStore.conversationsUsersFiltered"
      :key="contact.id"
      class="mb-2"
      :contact="contact"
      :show-last-message="true"
      @open-chat-of-contact="showMessages(contact.id)"
    />
    <span
      v-show="messageStore.conversationsUsersFiltered.length === 0"
      class="no-chat-items-text text-disabled"
    >
      Aucune Conversation
      <span v-show="search.length">pour `{{ search }}` dans {{ nbOfConversation }}</span>
    </span>
    <li class="my-4">
      <span class="text-xl chat-contact-header text-primary font-weight-medium"> Amis </span>
    </li>
    <message-contact
      v-for="contact in messageStore.contactsWithoutConversations"
      :key="contact.id"
      class="mb-2"
      :contact="contact"
      @open-chat-of-contact="showMessages(contact.id)"
    />
  </PerfectScrollbar>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore from '@/stores/AuthStore'
import useMessageStore from '@/stores/MessageStore'
import { PerfectScrollbar } from 'vue3-perfect-scrollbar'
import MessageContact from '@/components/messages/MessageContact.vue'
import AvatarBadge from '@/components/profile/AvatarBadge.vue'
import useUserStore from '@/stores/UserStore'
import useRoomsStore from '@/stores/RoomsStore'

export default defineComponent({
  components: {
    PerfectScrollbar,
    MessageContact,
    AvatarBadge
  },
  emits: ['openChatOfContact', 'showUserProfile', 'close'],
  setup() {
    const authStore = useAuthStore()
    const messageStore = useMessageStore()
    const userStore = useUserStore()
    const roomsStore = useRoomsStore()
    return {
      authStore,
      userStore,
      messageStore,
      roomsStore
    }
  },
  data() {
    return {
      loading: false,
      nbOfConversation: 0
    }
  },
  computed: {
    search: {
      get(): string {
        return this.messageStore.getSearchTerm
      },
      set(value: string) {
        this.messageStore.setSearchTerm(value)
      }
    }
  },
  watch: {
    'messageStore.conversationsUsers': {
      handler(value) {
        this.nbOfConversation = value.length
      },
      deep: true
    }
  },
  methods: {
    async showMessages(userId: number) {
      this.$emit('openChatOfContact', userId)
    }
  }
})
</script>

<style lang="scss">
.chat-contacts-list {
  --chat-content-spacing-x: 12px;

  padding-block-end: 0.75rem;

  .chat-contact-header {
    margin-block-end: 1rem;
    margin-block-start: 1.25rem;
  }

  .chat-contact-header,
  .no-chat-items-text {
    margin-inline: var(--chat-content-spacing-x);
  }
}
</style>
