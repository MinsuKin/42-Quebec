<template>
  <VCard
    color="#952175"
    :loading="loading"
  >
    <template #loader="{ isActive }">
      <v-progress-linear
        :active="isActive"
        color="blue"
        height="20"
        :indeterminate="true"
      />
    </template>
    <VCarousel
      v-if="!loading && topRooms.length > 0"
      cycle
      :continuous="false"
      :show-arrows="false"
      hide-delimiter-background
      :delimiter-icon="() => h(VIcon, { icon: 'fa-circle', size: '10' })"
      height="320"
    >
      <VCarouselItem
        v-for="(room, index) in topRooms"
        :key="room.id"
        class="p-0"
      >
        <div class="p-8 h-[320px]">
          <div class="">
            <h2 class="text-4xl uppercase font-bold">
              Les Top Chat - {{ index + 1 }}
            </h2>
          </div>
          <div class="flex h-full">
            <div class="basis-full md:basis-1/2 flex flex-col gap-4">
              <p class="text-base font-medium text-gray-300">
                Nom de la room:
                <a
                  class="text-gray-300 hover:text-gray-50"
                  href="#"
                >{{ room.name }}</a>
              </p>
              <div class="flex gap-4">
                <div>
                  <VChip
                    label
                    class="me-2"
                  >
                    {{ room.members.length }}
                  </VChip>
                  <span>Membres(s)</span>
                </div>
                <div>
                  <span> Type: </span>
                  <VChip
                    label
                    class="me-2"
                  >
                    {{ room.type }}
                  </VChip>
                </div>
              </div>
              <div class="flex gap-4">
                <VBtn
                  class="text-no-wrap text-sm bg-transparent border hover:bg-white hover:text-[#952175] flex gap-2 iems-center justify-center"
                  color="white"
                  @click="goToChatRoom(room.id)"
                >
                  <span>
                    <VIcon left> tabler-eye </VIcon>
                  </span>
                  <span>Voir</span>
                </VBtn>
              </div>
            </div>
            <div class="basis-full md:basis-1/2 h-full py-4">
              <img
                v-if="room.avatar"
                :src="room.avatar"
                class="rounded object-cover h-full w-full"
              >
            </div>
          </div>
        </div>
      </VCarouselItem>
    </VCarousel>
  </VCard>
  <NotificationPopUp
    v-model:visible="popUpVisible"
    :snackbar-msg="popUpMessage"
  />
</template>

<script lang="ts">
import { defineComponent, h } from 'vue'
import { VIcon } from 'vuetify/components'
import useAuthStore from '@/stores/AuthStore'
import useRoomsStore, { ChatRoomWithMembers } from '@/stores/RoomsStore'
import NotificationPopUp from '@/components/notifications/NotificationPopUp.vue'
export default defineComponent({
  name: 'TopChatCard',
  components: { NotificationPopUp },
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
      loading: false,
      popUpVisible: false,
      popUpMessage: ''
    }
  },
  computed: {
    VIcon() {
      return VIcon
    },
    topRooms(): ChatRoomWithMembers[] {
      const publicRoom = this.roomsStore.publicRooms
      return publicRoom.slice(0, 3)
    }
  },
  async beforeMount() {
    await this.fetchRooms()
  },
  methods: {
    h,
    async fetchRooms() {
      this.loading = true
      await this.roomsStore.fetchPublicRooms()
      this.loading = false
    },
    goToChatRoom(roomId: number) {
      this.$router.push({ name: 'chat', params: { roomId: roomId } })
    }
  }
})
</script>

<style scoped></style>
