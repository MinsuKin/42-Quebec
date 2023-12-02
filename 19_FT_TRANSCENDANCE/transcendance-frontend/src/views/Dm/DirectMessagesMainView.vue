<template>
  <VLayout
    v-show="!loading"
    class="p-2 border border-solid rounded shadow-sm bg-surface border-slate-400"
  >
    <v-navigation-drawer
      v-model="isLeftSidebarOpen"
      :absolute="true"
      :touchless="true"
      location="start"
      width="370"
      :temporary="$vuetify.display.smAndDown"
      :permanent="$vuetify.display.mdAndUp"
      class="chat-list-sidebar"
    >
      <dm-conversation-list-side-bar
        @open-chat-of-contact="openChatOfContact"
        @show-user-profile="showMyProfile"
        @close="isLeftSidebarOpen = false"
      />
    </v-navigation-drawer>
    <VMain class="chat-content-container">
      <contact-direct-message v-if="!!messageStore.conversationWith" />
      <div
        v-else
        class="flex items-center justify-center h-full flex-column"
      >
        <VAvatar
          :size="109"
          class="mb-6 elevation-3 bg-surface"
        >
          <VIcon
            :size="50"
            class="rounded-0 text-high-emphasis"
            icon="tabler-message"
          />
        </VAvatar>
        <p
          class="px-6 py-1 mb-0 text-lg font-weight-medium elevation-3 rounded-xl text-high-emphasis bg-surface"
          :class="[{ 'cursor-pointer': $vuetify.display.smAndDown }]"
          @click.prevent.stop="isLeftSidebarOpen = true"
        >
          Commencez une conversation
        </p>
      </div>
    </VMain>
  </VLayout>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import { useDisplay } from 'vuetify'
import useAuthStore from '@/stores/AuthStore'
import useMessageStore from '@/stores/MessageStore'
import { useResponsiveLeftSidebar } from '@core/composable/useResponsiveSidebar'
import DmConversationListSideBar from './DmConversationListSideBar.vue'
import useUserStore from '@/stores/UserStore'
import ContactDirectMessage from '@/views/Dm/ContactDirectMessage.vue'

export default defineComponent({
  components: {
    ContactDirectMessage,
    DmConversationListSideBar
  },
  props: {
    contactId: {
      type: Number,
      required: false,
      default: undefined
    }
  },
  setup() {
    const authStore = useAuthStore()
    const messageStore = useMessageStore()
    const userStore = useUserStore()
    const vuetifyDisplays = useDisplay()
    const { isLeftSidebarOpen } = useResponsiveLeftSidebar(vuetifyDisplays.smAndDown)
    return {
      authStore,
      messageStore,
      userStore,
      isLeftSidebarOpen,
      vuetifyDisplays
    }
  },
  data() {
    return {
      loading: false
    }
  },
  watch: {
    'messageStore.currentContact': {
      handler(value) {
        if (value) {
          document.title = `${value.profile.name} - Message | Transcendence`
        }
      }
    },
    contactId: {
      handler(value) {
        this.setConversation(value)
      },
      immediate: true
    },
    'messageStore.isSidebarOpen': {
      handler(value) {
        if (value !== this.isLeftSidebarOpen) {
          this.isLeftSidebarOpen = value
        }
      }
    },
    isLeftSidebarOpen: {
      handler(value) {
        if (value !== this.messageStore.isSidebarOpen) {
          this.messageStore.setSidebarOpen(value)
        }
      }
    }
  },
  async beforeMount() {
    this.loading = true
    await this.userStore.loadAllMyFriends()
    await this.messageStore.getUniqueConversations()
    if (this.contactId) {
      await this.setConversation(this.contactId)
    }
    this.loading = false
  },
  beforeUnmount() {
    this.messageStore.resetCurrentConversationWith()
  },
  methods: {
    async setConversation(contactId?: number) {
      if (!contactId || this.messageStore.currentContact?.id === contactId) return
      this.loading = true
      await this.messageStore.setCurrentConversationWith(contactId)
      this.loading = false
    },
    showMyProfile() {
      this.$router.push({ name: 'me', params: { tab: 'profile' } })
    },
    async openChatOfContact(id: number) {
      await this.$router.push({ name: 'dm', params: { contactId: id } })
    },
    openLeftSide() {
      if (this.vuetifyDisplays.mdAndUp) return
      this.isLeftSidebarOpen = true
    }
  }
})
</script>

<style lang="scss"></style>
