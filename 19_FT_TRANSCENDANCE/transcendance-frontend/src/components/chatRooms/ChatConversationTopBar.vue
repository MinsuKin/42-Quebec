<template>
  <div class="flex align-center text-medium-emphasis my-1">
    <!-- menu button when sm-->
    <VBtn
      variant="text"
      color="default"
      icon
      size="small"
      class="d-md-none me-3"
      :active="isLeftSidebarOpenLocal"
      @click="isLeftSidebarOpenLocal = !isLeftSidebarOpenLocal"
    >
      <VIcon
        size="24"
        icon="tabler-menu-2"
      />
    </VBtn>
    <template v-if="room">
      <RoomCard
        :room="room"
        :top-bar="true"
      />
      <VChip
        v-if="room.password"
        label
        color="error"
        text-color="white"
        class="mx-2"
      >
        Salle protégée
        <VIcon :size="16">
          tabler-lock
        </VIcon>
      </VChip>
      <VChip
        v-if="userRole === 'OWNER'"
        :label="true"
        color="yellow"
        text-color="white"
        class="mx-2"
      >
        <VIcon :size="16">
          tabler-crown
        </VIcon>
        PROPRIÉTAIRE
      </VChip>
      <VChip
        v-else-if="userRole === 'ADMIN'"
        :label="true"
        color="blue"
        text-color="white"
        class="mx-2"
      >
        <VIcon :size="16">
          tabler-shield-check
        </VIcon>
        ADMIN
      </VChip>
      <VChip
        v-else-if="userRole === 'USER'"
        :label="true"
        color="gray"
        text-color="white"
        class="mx-2"
      >
        <VIcon :size="16">
          tabler-user
        </VIcon>
        MEMBRE
      </VChip>
      <VChip
        v-else-if="userRole === 'BAN'"
        :label="true"
        color="gray"
        text-color="white"
        class="mx-2"
      >
        <VIcon :size="16">
          tabler-user-x
        </VIcon>
        BANNI
      </VChip>
      <VSpacer />
      <div class="flex items-center gap-2">
        <VBtn
          v-if="roomStore.currentRoom"
          variant="text"
          :disabled="userRole === 'BAN'"
          icon
          size="small"
          :active="isRightSidebarOpenLocal"
          @click="isRightSidebarOpenLocal = !isRightSidebarOpenLocal"
        >
          <VIcon
            size="22"
            icon="tabler-settings"
          />
        </VBtn>
      </div>
      <VBtn
        variant="text"
        color="default"
        icon
        size="small"
      >
        <VIcon
          size="22"
          icon="tabler-dots-vertical"
        />
        <VMenu activator="parent">
          <VList>
            <VListItem prepend-icon="tabler-trash">
              <VListItemTitle> Quit, or something </VListItemTitle>
            </VListItem>
          </VList>
        </VMenu>
      </VBtn>
    </template>
  </div>
  <VDivider />
</template>

<script lang="ts">
import { defineComponent, PropType } from 'vue'
import useAuthStore from '@/stores/AuthStore'
import useRoomsStore, { ChatRoomWithMembers } from '@/stores/RoomsStore'
import { ChatMemberRole } from '@/utils/chatSocket'
import RoomCard from '@/components/chatRooms/RoomCard.vue'

export default defineComponent({
  name: 'ChatTopBar',
  components: { RoomCard },
  props: {
    isLeftSidebarOpen: {
      type: Boolean,
      required: true,
      default: false
    },
    isRightSidebarOpen: {
      type: Boolean,
      required: true,
      default: false
    },
    userRole: {
      type: String as PropType<ChatMemberRole>,
      required: true,
      default: ChatMemberRole.USER
    }
  },
  emits: ['update:isLeftSidebarOpen', 'update:isRightSidebarOpen'],
  setup() {
    const authStore = useAuthStore()
    const roomStore = useRoomsStore()
    return {
      authStore,
      roomStore
    }
  },
  computed: {
    isLeftSidebarOpenLocal: {
      get(): boolean {
        return this.isLeftSidebarOpen
      },
      set(value: boolean) {
        this.$emit('update:isLeftSidebarOpen', value)
      }
    },
    isRightSidebarOpenLocal: {
      get(): boolean {
        return this.isRightSidebarOpen
      },
      set(value: boolean) {
        this.$emit('update:isRightSidebarOpen', value)
      }
    },
    room(): ChatRoomWithMembers | null {
      return this.roomStore.currentRoom
    }
  },
  methods: {
    // quitTheRoom() {
    //   console.log('quit the room')
    // },
    // deleteTheRoom() {
    //   console.log('delete the room')
    // }
  }
})
</script>

<style scoped></style>
