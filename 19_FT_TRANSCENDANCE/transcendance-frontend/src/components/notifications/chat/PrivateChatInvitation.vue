<template>
  <button
    :disabled="notification.status === 'READ'"
    :class="[
      'relative block w-full p-4 hover:bg-[#01051e] cursor-pointer',
      notification.status === 'READ' ? 'opacity-75' : 'opacity-100'
    ]"
    @click.prevent="handleRead"
  >
    <div class="relative flex w-full gap-4">
      <div>
        <v-icon
          class="text-2xl"
          color="cyan"
        >
          mdi-forum
        </v-icon>
      </div>
      <div class="flex-col flex-1 pr-4">
        <p :class="['text-left text-sm fomt-semiBold']">
          Club privé 📜
        </p>
        <p :class="['text-left text-xs text-gray-500/75']">
          {{ notification.message }}
        </p>
        <button
          class="px-8 py-2 text-xs border rounded-md cursor-pointer border-gray-50/10 bg-green-700/50 hover:bg-green-700/60 text-gary-500 disabled:bg-gray-800/50 disabled:opacity-50"
          @click.prevent.stop="handleShowRoom"
        >
          Voir la room
        </button>
      </div>
      <div
        v-if="notification.status !== 'READ'"
        class="absolute right-0 z-50 w-2 h-2 -translate-y-1/2 rounded-full top-1/2 bg-green-400/50"
      />
    </div>
  </button>
</template>

<script setup lang="ts">
import { PropType } from 'vue'
import { useRouter } from 'vue-router'
import { Notification } from '@/utils/notificationSocket'
import useNotificationStore from '@/stores/NotificationStore'

const notificationStore = useNotificationStore()
const router = useRouter()

const props = defineProps({
  notification: {
    type: Object as PropType<Notification>,
    required: true
  },
  isShort: {
    type: Boolean,
    default: false
  }
})
const handleRead = async () => {
  if (props.notification.status === 'READ') return
  await notificationStore.markNotificationAsRead(props.notification.id)
}
const handleShowRoom = async () => {
  await handleRead()
  await router.push({ name: 'chat', params: { roomId: props.notification?.referenceId } })
}
</script>

<style scoped></style>
