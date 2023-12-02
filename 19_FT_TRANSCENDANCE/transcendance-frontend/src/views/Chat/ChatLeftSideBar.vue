<template>
  <div>
    <div class="mt-2 text-end">
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
    <div class="flex px-2 mb-2">
      <AvatarBadge
        v-if="authStore.getUser !== null"
        :user-id="authStore.getUser.id"
        :user="authStore.getUser"
        :bordered="true"
        @show-user-profile="$emit('showUserProfile')"
      />
      <VTextField
        v-model="search"
        density="compact"
        rounded
        placeholder="Chercher une salle de discussion..."
        class="ms-4 me-1 transparent-input-box"
      >
        <template #prepend-inner>
          <VIcon
            size="22"
            icon="tabler-search"
          />
        </template>
      </VTextField>
    </div>
    <v-toolbar color="#952175">
      <v-toolbar-title class="text-gray-300">
        Salles de discussion
      </v-toolbar-title>
      <VBtn
        variant="elevated"
        class="text-gray-300 bg-transparent"
        selected-class="text-red-300 bg-red"
        color="white"
        :border="true"
        icon
        size="small"
        rounded
        @click="$emit('createRoom')"
      >
        <VIcon
          size="18"
          icon="tabler-edit"
          color="white"
        />
      </VBtn>
    </v-toolbar>
    <VDivider />
    <PerfectScrollbar
      tag="ul"
      class="px-3 chat-contacts-list"
      :options="{ wheelPropagation: true }"
    >
      <li class="py-4">
        <span class="text-xl chat-contact-header text-primary font-weight-medium">
          Mes Salles de discussion
        </span>
      </li>
      <li class="py-4">
        <span
          v-show="roomsStore.filteredRooms.length === 0"
          class="no-chat-items-text text-disabled"
        >
          Vous n'avez rejoins aucune salle de discussion.
          <template v-if="search.length"> pour `{{ search }}`</template>
        </span>
      </li>
      <li
        v-for="room in roomsStore.filteredRooms"
        :key="room.id"
        @click="showRoom(room.id)"
      >
        <RoomCard :room="room" />
      </li>
      <li class="py-4">
        <span class="text-xl chat-contact-header text-primary font-weight-medium">
          Salles publique
        </span>
      </li>
      <li>
        <span
          v-show="roomsStore.filteredPublic.length === 0"
          class="no-chat-items-text text-disabled"
        >
          Aucune salle de discussion publique
          <template v-if="search.length"> pour `{{ search }}`</template>
        </span>
      </li>
      <li
        v-for="room in roomsStore.filteredPublic"
        :key="room.id"
        @click="showRoom(room.id)"
      >
        <RoomCard :room="room" />
      </li>
    </PerfectScrollbar>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import AvatarBadge from '@/components/profile/AvatarBadge.vue'
import { PerfectScrollbar } from 'vue3-perfect-scrollbar'
import useAuthStore from '@/stores/AuthStore'
import useUserStore from '@/stores/UserStore'
import useRoomsStore from '@/stores/RoomsStore'
import RoomCard from '@/components/chatRooms/RoomCard.vue'

export default defineComponent({
  name: 'ChatLeftSideBar',
  components: {
    RoomCard,
    AvatarBadge,
    PerfectScrollbar
  },
  emits: ['close', 'showUserProfile', 'showRoom', 'createRoom'],
  setup() {
    const authStore = useAuthStore()
    const userStore = useUserStore()
    const roomsStore = useRoomsStore()
    return {
      authStore,
      userStore,
      roomsStore
    }
  },
  data() {
    return {}
  },
  computed: {
    search: {
      get(): string {
        return this.roomsStore.searchTerm
      },
      set(value: string) {
        this.roomsStore.setSearchTerm(value)
      }
    }
  },
  methods: {
    showRoom(roomId: number) {
      this.$emit('showRoom', roomId)
    },
    showUserProfile() {
      this.$emit('showUserProfile')
    }
  }
})
</script>

<style scoped></style>
