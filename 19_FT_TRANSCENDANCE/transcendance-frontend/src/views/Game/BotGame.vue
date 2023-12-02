<script setup lang="ts">
import { onBeforeMount, ref } from 'vue'
import useGameStore, { GameSession } from '@/stores/GameStore'
import { useRouter } from 'vue-router'
import NotificationPopUp from '@/components/notifications/NotificationPopUp.vue'

const loading = ref(false)
const showError = ref(false)
const gameStore = useGameStore()
const router = useRouter()
onBeforeMount(async () => {
  loading.value = true
  if (gameStore.getCurrentGameSession) {
    await router.push({
      name: 'game',
      params: {
        gameId: gameStore.getCurrentGameSession.gameId
      }
    })
  } else {
    const response = await gameStore.startGameAgainstBot()
    if (typeof response !== 'string') {
      const session = response as GameSession
      await gameStore.getAllGameSessions()
      await router.push({
        name: 'game',
        params: { gameId: session.gameId }
      })
    } else {
      showError.value = true
      await router.push({ name: 'game' })
    }
  }
  loading.value = false
})
</script>

<template>
  <div>
    <NotificationPopUp
      v-if="showError"
      :message="'Impossible de preparer une partie avec le bot...'"
      :color="'pink'"
    />
    <NotificationPopUp
      v-else
      :message="'Preparing game'"
      :color="'pink'"
    />
  </div>
</template>

<style scoped></style>
