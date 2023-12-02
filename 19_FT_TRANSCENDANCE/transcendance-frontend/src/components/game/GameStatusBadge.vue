<template>
  <div class="flex gap-2 items-center">
    <v-chip
      v-if="userGameStatus.status === 'playing'"
      color="green"
      class="flex gap-2"
    >
      <span class="flex gap-2">
        <v-icon left> tabler:device-gamepad </v-icon>
        <span> Dans une partie </span>
      </span>
    </v-chip>
    <v-chip
      v-else-if="userGameStatus.status === 'inQueue'"
      color="orange"
    >
      <span class="flex gap-2">
        <v-icon left> ic:baseline-timer </v-icon>
        <span> En attente </span>
      </span>
    </v-chip>
    <v-chip
      v-else-if="liveStatus === 'Online'"
      color="blue"
      class="rounded-md"
    >
      <span class="flex gap-2">
        <v-icon left> mdi-account-check-outline </v-icon>
        <span> Peut jouer </span>
      </span>
    </v-chip>
    <v-chip
      v-else
      color="error"
      class="rounded-md"
    >
      <span class="flex gap-2">
        <v-icon left>tabler:device-gamepad</v-icon>
        <span>Indisponible</span>
      </span>
    </v-chip>
    <v-btn
      v-if="localGameStatus && localGameStatus.gameSession"
      size="small"
      color="deep-purple accent-4"
      :to="{
        name: 'watch-game',
        params: {
          gameId: localGameStatus.gameSession.gameId
        }
      }"
    >
      <span class="flex gap-2">
        <v-icon left> tabler-eye </v-icon>
        <span> Regardez la partie </span>
      </span>
    </v-btn>
    <challenge-modal
      v-else-if="liveStatus === 'Online'"
      :status="liveStatus"
      :user-id="userId"
      :user-game-status="localGameStatus"
    />
  </div>
</template>

<script lang="ts" setup>
import { computed, PropType, ref, watch } from 'vue'
import useGameStore, { GameSession } from '@/stores/GameStore'
import { Status } from '@/interfaces/User'
import ChallengeModal from '@/components/game/ChallengeModal.vue'
import useUserStore from '@/stores/UserStore'
import useNotificationStore from '@/stores/NotificationStore'
import { RealTimeNotificationType } from '@/utils/notificationSocket'

const props = defineProps({
  userId: {
    type: Number,
    required: true
  },
  userGameStatus: {
    type: Object as PropType<{
      status: 'playing' | 'inQueue' | 'free'
      gameSession?: GameSession
    }>,
    required: false,
    default: () => ({ status: 'free', gameSession: undefined })
  },
  status: {
    type: String as PropType<Status>,
    required: false,
    default: () => Status.Offline
  }
})
const usersStore = useUserStore()
const loading = ref(false)
const gameStore = useGameStore()
const notificationStore = useNotificationStore()

const localGameStatus = ref<{
  status: 'playing' | 'inQueue' | 'free'
  gameSession?: GameSession
}>(props.userGameStatus)

const liveStatus = computed(() => {
  return usersStore.getUsersStatus.get(props.userId) ?? props.status
})

const updateLocalGameStatus = async (userId: number) => {
  loading.value = true
  localGameStatus.value = await gameStore.getUserGameStatus(userId)
  loading.value = false
}

// watch userId
watch(
  props,
  async (newProps) => {
    if (!newProps.userId) return
    await updateLocalGameStatus(newProps.userId)
  },
  { immediate: true }
)

// watch status change
watch(liveStatus, async (newStatus) => {
  if (newStatus === Status.Offline) {
    localGameStatus.value = { status: 'free', gameSession: undefined }
  } else {
    await updateLocalGameStatus(props.userId)
  }
})

watch(notificationStore.allRealTimeNotifications, async (newNotifications) => {
  if (newNotifications.length === 0) return
  const lastNotification = newNotifications[0]
  if (
    lastNotification.type === RealTimeNotificationType.GameWaitingQue ||
    lastNotification.type === RealTimeNotificationType.Game
  ) {
    if (
      lastNotification.userId === props.userId ||
      lastNotification.sourceUserId === props.userId
    ) {
      await updateLocalGameStatus(props.userId)
    }
  }
})
</script>
