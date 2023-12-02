<template>
  <div class="h-full">
    <template v-if="!loading && gameStore.isPlaying">
      <v-alert
        v-model="alertGameAlreadyJoined"
        border="start"
        variant="tonal"
        closable
        close-label="Close Alert"
        color="secondary"
        title="Partie en cours"
      >
        Vous avez deja une session, veuillez patienter... Vous avez deja une partie en cours, elle
        va etre chargée. Quand la partie sera terminée, vous serez redirigé vers la page de
        résultat.
      </v-alert>
      <GamePlayer
        v-if="player && gameStore.currentGameId"
        :key="gameStore.currentGameId"
        :room-id="gameStore.currentGameId"
        :player="player"
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
    <div
      v-if="!gameStore.isPlaying"
      class="flex justify-center"
    >
      <p class="w-1/2 text-center">
        Aucune partie en cours
      </p>
      <VIcon
        color="orange"
        :size="128"
      >
        tabler:device-gamepad-2
      </VIcon>
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore from '@/stores/AuthStore'
import useGameStore, { GameSession } from '@/stores/GameStore'
import { GameUser, GameUserType } from '@/Game/network/GameNetwork'
import { Theme } from '@/Game/scenes/Boot'
import GamePlayer from '@/Game/GamePlayer.vue'

export default defineComponent({
  components: {
    GamePlayer
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
      error: null as unknown as string,
      alertGameAlreadyJoined: false
    }
  },
  computed: {
    player(): (GameUser & { userType: GameUserType }) | undefined {
      if (this.gameStore.getCurrentGameSession) {
        const user = this.gameStore.getCurrentGameSession.participants.find(
          (user) => user.userId === this.authStore.getUser?.id
        )
        if (user) {
          return {
            userId: user.userId,
            username: user.username,
            avatar: this.authStore.getProfile?.avatar ?? '',
            userType: GameUserType.Player
          }
        }
      }
      return undefined
    },
    theme(): Theme {
      if (this.gameStore.getCurrentGameSession) {
        return this.gameStore.getCurrentGameSession.rules.theme ?? Theme.Classic
      }
      return Theme.Classic
    }
  },
  watch: {
    'gameStore.getCurrentGameSession': {
      handler() {
        this.moveToCurrentGame()
      },
      immediate: true
    }
  },
  async beforeMount() {
    this.loading = true
    await this.gameStore.getAllGameSessions()
    if (!this.gameId) {
      await this.startAgainstBot()
    } else {
      this.gameStore.setCurrentGameSession(this.gameId)
    }
    this.loading = false
  },
  beforeUnmount() {
    if (this.gameId) {
      this.gameStore.quitGameSession(this.gameId)
      // force reload of the page after quit to avoid bug
      window.location.reload();
    }
  },
  methods: {
    moveToCurrentGame() {
      if (this.gameStore.getCurrentGameSession) {
        // get players username and set it as title of page
        const title = `${this.gameStore.getCurrentGameSession.participants[0].username} vs ${this.gameStore.getCurrentGameSession.participants[1].username}`
        document.title = `PONG - ${title} | Transcendance`
        if (this.gameId !== this.gameStore.getCurrentGameSession.gameId) {
          this.$router.push({
            name: 'game',
            params: { gameId: this.gameStore.getCurrentGameSession.gameId }
          })
        }
      }
    },
    async startAgainstBot() {
      const response = await this.gameStore.startGameAgainstBot()
      if (typeof response !== 'string') {
        const session = response as GameSession
        this.$router.push({
          name: 'bot-game',
          params: { gameId: session.gameId }
        })
      }
    }
  }
})
</script>

<style scoped></style>
