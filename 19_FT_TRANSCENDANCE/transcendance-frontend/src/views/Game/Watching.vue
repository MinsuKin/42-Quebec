<template>
  <div class="h-full">
    <template v-if="!loading && gameSession">
      <GamePlayer
        v-if="viewer"
        :room-id="gameId"
        :player="viewer"
        :theme="theme"
      />
    </template>
    <div
      v-else-if="loading"
      class="h-full flex items-center justify-center"
    >
      <v-progress-circular
        indeterminate
        color="deep-purple-accent-4"
      />
    </div>
    <v-alert
      v-else
      border="start"
      variant="tonal"
      :closable="false"
      color="error"
      title="Partie en non disponible"
    >
      <template v-if="error">
        {{ error }}
      </template>
      <template v-else>
        La partie est terminée, est deja terminé, ou n'existe pas.
      </template>
    </v-alert>
  </div>
</template>

<script lang="ts">
import { defineAsyncComponent, defineComponent } from 'vue'
import useAuthStore from '@/stores/AuthStore'
import useGameStore, { GameSession } from '@/stores/GameStore'
import { GAME_STATE } from '@/Game/network/Monitor'
import axios from '@/utils/axios'
import { GameUser, GameUserType } from '@/Game/network/GameNetwork'
import { Theme } from '@/Game/scenes/Boot'

export default defineComponent({
  components: {
    GamePlayer: defineAsyncComponent(() => import('@/Game/GamePlayer.vue'))
  },
  props: {
    gameId: {
      type: Number,
      default: () => 0
    }
  },
  setup() {
    const authStore = useAuthStore()
    const gameStore = useGameStore()
    return {
      authStore,
      gameStore
    }
  },
  data() {
    return {
      loading: false,
      error: '' as string,
      gameState: undefined as GAME_STATE | undefined,
      gameSession: undefined as GameSession | undefined
    }
  },
  computed: {
    viewer(): (GameUser & { userType: GameUserType }) | undefined {
      if (this.gameSession) {
        const user = this.gameSession.observers.find(
          (user) => user.userId === this.authStore.getUser?.id
        )
        if (user) {
          return {
            userId: user.userId,
            username: user.username,
            avatar: this.authStore.getProfile?.avatar ?? '',
            userType: GameUserType.Viewer
          }
        }
      }
      return undefined
    },
    theme(): Theme {
      if (this.gameSession) {
        return this.gameSession.rules.theme ?? Theme.Classic
      }
      return Theme.Classic
    }
  },
  watch: {},
  async beforeMount() {
    this.loading = true
    await this.getCurrentGameSessionState()
    if (this.gameState !== GAME_STATE.Ended && this.gameState !== undefined) {
      await this.startViewingGame(this.gameId)
    }
    this.loading = false
  },
  methods: {
    async getCurrentGameSessionState() {
      if (!this.gameId) {
        this.gameState = undefined
      } else {
        this.gameState = await this.gameStore.getGameSessionState(this.gameId)
      }
    },
    async startViewingGame(gameId: number) {
      try {
        const { data } = await axios.get<GameSession>(`/game/watch-game/${gameId}`, {
          headers: { Accept: 'application/json' }
        })
        this.gameSession = data
      } catch (error) {
        this.error = 'Impossible de visionner la partie'
      }
    }
  }
})
</script>

<style scoped></style>
