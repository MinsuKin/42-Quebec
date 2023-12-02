<template>
  <button
    :disabled="notification.status === 'READ'"
    class="relative block w-full p-4 hover:bg-[#01051e] cursor-pointer"
    @click="handleRead"
  >
    <div class="flex gap-4 w-full relative">
      <div :class="[notification.status === 'READ' ? 'opacity-75' : 'opacity-100']">
        <avatar-badge :user-id="notification.referenceId" />
      </div>
      <div class="flex-1 flex-col pr-4">
        <p
          :class="[
            'text-left text-sm fomt-semiBold',
            notification.status === 'READ' ? 'text-gray-400/50' : ''
          ]"
        >
          Demande d'amitié Accetpée
        </p>
        <p
          :class="[
            'text-left text-xs',
            notification.status === 'READ' ? 'text-gray-400/75' : 'text-gray-200/75'
          ]"
        >
          {{ notification.message }}
        </p>
      </div>
      <div
        v-if="notification.status !== 'READ'"
        class="absolute h-2 w-2 right-0 top-1/2 -translate-y-1/2 rounded-full bg-green-400/75 z-50"
      />
    </div>
  </button>
</template>

<script setup lang="ts">
import { PropType } from 'vue'
import { useRouter } from 'vue-router'
import AvatarBadge from '@/components/profile/AvatarBadge.vue'
import { Notification } from '@/utils/notificationSocket'
import useNotificationStore from '@/stores/NotificationStore'

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

const router = useRouter()
const notificationStore = useNotificationStore()
// const handleDelete = () => {
//   notificationStore.deleteNotification(props.notification.id)
// }
const handleRead = async () => {
  if (props.notification.status !== 'READ') {
    await notificationStore.markNotificationAsRead(props.notification.id)
  }
  await router.push({
    name: 'user-profile',
    params: { userId: props.notification.referenceId }
  })
}
</script>

<style scoped></style>
