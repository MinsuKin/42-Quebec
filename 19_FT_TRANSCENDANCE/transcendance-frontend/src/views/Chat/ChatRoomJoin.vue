<template>
  <div
    v-if="roomsStore.currentRoom"
    class="relative h-full mt-4"
  >
    <div
      v-if="canViewMessagesList"
      class="absolute left-0 z-10 w-full h-full -top-[40px]"
    >
      <chat-room-message-list />
    </div>
    <div class="relative z-20 flex flex-col items-start justify-center h-full px-4">
      <div class="flex flex-col items-center justify-center w-full gap-4 md:flex-row">
        <div class="">
          <span class="text-4xl font-semibold text-gray-300">
            {{ roomsStore.currentRoom.name }}
          </span>
          <div class="my-4">
            <VChip
              label
              class="me-2"
            >
              {{ roomsStore.currentRoom.type }}
            </VChip>
          </div>
        </div>
        <div class="py-4 w-72 h-72">
          <img
            v-if="roomsStore.currentRoom.avatar"
            :src="roomsStore.currentRoom.avatar"
            class="object-cover w-full h-full rounded"
          >
        </div>
      </div>
      <v-divider class="mx-auto w-72" />
      <div class="flex flex-col gap-4 mx-auto my-8">
        <VTextField
          v-if="roomsStore.isPasswordProtected"
          v-model="password"
          :rules="[rules.required]"
          :disabled="isJoining"
          outlined
          dense
          :type="passwordVisibility ? 'text' : 'password'"
          :append-inner-icon="passwordVisibility ? 'tabler-eye-off' : 'tabler-eye'"
          placeholder="Mot de passe, de la salle de discussion"
          @click:append-inner="passwordVisibility = !passwordVisibility"
        />
        <VBtn
          color="primary"
          size="large"
          class="inline-flex w-64 py-4 text-sm bg-transparent border hover:bg-white hover:text-[#952175] gap-6 iems-center justify-center"
          @click="joinRoom()"
        >
          <span class="mr-2">
            <VIcon left> mdi-account-plus </VIcon>
          </span>
          <span>Rejoindre</span>
        </VBtn>
      </div>
    </div>
    <NotificationPopUp
      v-model:visible="popUpVisible"
      color="error"
      :snackbar-msg="errorMessage"
    />
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useRoomsStore from '@/stores/RoomsStore'
import ChatRoomMessageList from './ChatRoomMessageList.vue'

export default defineComponent({
  components: {
    ChatRoomMessageList
  },
  setup() {
    const roomsStore = useRoomsStore()
    return {
      roomsStore
    }
  },
  data() {
    return {
      password: '',
      passwordVisibility: false,
      isJoining: false,
      popUpVisible: false,
      errorMessage: 'sd',
      rules: {
        required: (value: string) => !!value || 'Ce champ est requis'
      }
    }
  },
  computed: {
    canViewMessagesList(): boolean {
      return this.roomsStore.isPublic
    }
  },
  methods: {
    async joinRoom() {
      if (!this.roomsStore.currentRoom) return
      this.isJoining = true
      this.password = this.password.trim()
      const result = await this.roomsStore.joinRoom(this.roomsStore.currentRoom.id, {
        userId: this.roomsStore.userId,
        password: this.password ? this.password : undefined
      })
      if (typeof result === 'string') {
        this.errorMessage = result as unknown as string
        this.popUpVisible = true
      }
      this.isJoining = false
    }
  }
})
</script>

<style scoped></style>
