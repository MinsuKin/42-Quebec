<template>
  <button
    :disabled="notification.status === 'READ'"
    :class="[
      'relative block w-full p-4 hover:bg-[#01051e] cursor-pointer',
      notification.status === 'READ' ? 'opacity-75' : 'opacity-100'
    ]"
    @click="handleRead"
  >
    <div class="relative flex w-full gap-4">
      <div>
        <v-icon
          class="text-2xl"
          color="orange"
        >
          tabler:eye
        </v-icon>
      </div>
      <div class="flex-col flex-1 pr-4">
        <p :class="['text-left text-sm fomt-semiBold']">
          A Rejoins
        </p>
        <p :class="['text-left text-xs text-gray-500/75']">
          {{ notification.message }}
        </p>
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
import { Notification } from '@/utils/notificationSocket'
import useNotificationStore from '@/stores/NotificationStore'

const notificationStore = useNotificationStore()

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
const handleRead = () => {
  notificationStore.markNotificationAsRead(props.notification.id)
}
</script>

<style scoped></style>
