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
      <div :class="[isAlreadyPlayed || !isValid ? 'opacity-75' : 'opacity-100']">
        <v-icon
          class="text-2xl"
          color="orange"
        >
          tabler:device-gamepad-2
        </v-icon>
      </div>
      <div class="flex-col flex-1 pr-4">
        <p :class="['text-left text-sm fomt-semiBold']">
          Invitation Challenge
        </p>
        <p :class="['text-left text-xs text-gray-500/75']">
          {{ notification.message }}
        </p>
        <div class="flex gap-2 mt-4">
          <button
            :disabled="isAlreadyPlayed || !isValid"
            class="px-8 py-2 text-xs border rounded-md cursor-pointer border-gray-50/10 bg-green-700/50 hover:bg-green-700/60 text-gary-500 disabled:bg-gray-800/50 disabled:opacity-50"
            @click.prevent="handleAcceptChallenge"
          >
            Accepter
          </button>
          <button
            :disabled="isAlreadyPlayed || !isValid"
            class="px-8 py-2 text-xs border rounded-md cursor-pointer border-gray-50/10 bg-red-700/50 hover:bg-red-700/60 text-gary-500 disabled:bg-gray-800/50 disabled:opacity-50"
            @click.prevent="handleRejectChallenge"
          >
            Refuser
          </button>
        </div>
      </div>
      <div
        v-if="notification.status !== 'READ'"
        class="absolute right-0 z-50 w-2 h-2 -translate-y-1/2 rounded-full top-1/2"
        :class="isAlreadyPlayed ? 'bg-red-400/50' : 'bg-green-400/50'"
      />
    </div>
  </button>
</template>

<script setup lang="ts">
import { onBeforeMount, PropType, ref } from 'vue'
import { useRouter } from 'vue-router'
import { Notification } from '@/utils/notificationSocket'
import useNotificationStore from '@/stores/NotificationStore'
import useGameStore from '@/stores/GameStore'

const router = useRouter()
const notificationStore = useNotificationStore()
const gameStore = useGameStore()

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
const isValid = ref(false)
const isAlreadyPlayed = ref(true)
const loading = ref(false)
const errorDuringAccept = ref(false)
const errorMessage = ref('')

const checkChallengeStatus = async () => {
  loading.value = true
  const status = await gameStore.getChallengeStatus(props.notification.referenceId)
  isValid.value = status.valid
  isAlreadyPlayed.value = status.played
  loading.value = false
}
const handleRead = () => {
  loading.value = true
  if (props.notification.status !== 'READ') {
    notificationStore.markNotificationAsRead(props.notification.id)
  }
  loading.value = false
}

const handleAcceptChallenge = async () => {
  handleRead()
  if (isValid.value && !isAlreadyPlayed.value) {
    loading.value = true
    const r = await gameStore.acceptGameChallenge(props.notification.referenceId)
    loading.value = false
    if (typeof r === 'string') {
      errorDuringAccept.value = true
      errorMessage.value = r
    } else {
      await router.push({ name: 'game', params: { gameId: r.gameId } })
    }
  }
}

const handleRejectChallenge = async () => {
  handleRead()
  if (isValid.value && !isAlreadyPlayed.value) {
    loading.value = true
    await gameStore.rejectGameChallenge(props.notification.referenceId)
    await checkChallengeStatus()
    loading.value = false
  }
}

onBeforeMount(() => {
  checkChallengeStatus()
})
</script>

<style scoped></style>
