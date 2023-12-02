<template>
  <VIcon
    v-if="gameStore.isPlaying"
    class="text-green-500 animate-pulse"
    size="24"
    icon="tabler-controller"
  />
  <VIcon
    v-else-if="gameStore.isWatching"
    class="text-green-500 animate-pulse"
    size="24"
    icon="tabler-eye"
  />
</template>

<script setup lang="ts">
import useGameStore from '@/stores/GameStore'
const gameStore = useGameStore()
</script>

<style scoped></style>
