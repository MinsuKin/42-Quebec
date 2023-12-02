<template>
  <v-container fluid>
    <v-card
      color="purple"
      :loading="loading"
    >
      <v-card-title class="text-h5">
        Bienvenue dans la salle d'attente
      </v-card-title>
      <v-card-item>
        <v-card-text>
          <v-table class="p-4 rounded-md">
            <template #top>
              <thead>
                <tr>
                  <th class="text-left">
                    Joeur
                  </th>
                </tr>
              </thead>
            </template>
            <tbody>
              <tr
                v-for="player in queList"
                :key="player.userId"
              >
                <td>{{ player.username }}</td>
              </tr>
            </tbody>
          </v-table>
        </v-card-text>
      </v-card-item>
      <div
        v-if="gameStore.getCurrentGameSession === undefined"
        class="flex justify-center"
      >
        <p>
          Vous êtes dans la salle d'attente. Vous pouvez rejoindre une file d'attente pour jouer à
          Pong avec un autre joueur. Si vous quittez cette page, vous quitterez la file d'attente.
        </p>
        <VIcon
          icon="medical-icon:i-waiting-area"
          :size="128"
        />
      </div>
      <div
        v-else
        class="flex justify-center"
      >
        <p class="w-1/2 text-center">
          Oh, Vous avez deja une session de jeu en cours
        </p>
        <VIcon
          color="orange"
          :size="128"
        >
          tabler:device-gamepad-2
        </VIcon>
      </div>
      <v-card-actions>
        <v-btn
          :loading="loading"
          :disabled="gameStore.getCurrentGameSession !== undefined || loading"
          color="primary"
          variant="elevated"
          @click="joinQueue"
        >
          Rejoindre la file d'attente
        </v-btn>
      </v-card-actions>
    </v-card>
    <NotificationPopUp
      v-model:visible="showPopUp"
      :message="popUpMessage"
      color="success"
    />
  </v-container>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useGameStore, { GameSessionQResponse } from '@/stores/GameStore'
import useNotificationStore from '@/stores/NotificationStore'
import NotificationPopUp from '@/components/notifications/NotificationPopUp.vue'
import { RealTimeNotificationTitle, RealTimeNotificationType } from '@/utils/notificationSocket'
import useAuthStore from '@/stores/AuthStore'

export default defineComponent({
  components: { NotificationPopUp },
  props: {},
  setup() {
    const gameStore = useGameStore()
    const notificationStore = useNotificationStore()
    const authStore = useAuthStore()
    return {
      authStore,
      gameStore,
      notificationStore
    }
  },
  data() {
    return {
      showPopUp: false,
      popUpMessage: '',
      loading: false,
      queResponse: null as unknown as GameSessionQResponse,
      queList: [] as { userId: number; username: string; avatar: string }[]
    }
  },
  watch: {
    'gameStore.getCurrentGameSession': {
      handler() {
        this.checkIfAlreadyInGame()
      },
      immediate: true
    },
    'notificationStore.allRealTimeNotifications': {
      handler() {
        this.checkWaitingQue()
        this.checkIfGameMatched()
      },
      deep: true
    }
  },
  async beforeMount() {
    await this.gameStore.getAllGameSessions()
    await this.loadCurrentWaitingRoom()
  },
  async beforeUnmount() {
    await this.gameStore.quitQueList()
  },
  methods: {
    async checkIfAlreadyInGame() {
      if (this.gameStore.getCurrentGameSession) {
        this.$router.push({
          name: 'game',
          params: { gameId: this.gameStore.getCurrentGameSession.gameId }
        })
      }
    },
    async joinQueue() {
      if (this.gameStore.getCurrentGameSession) {
        this.$router.push({
          name: 'game',
          params: { gameId: this.gameStore.getCurrentGameSession.gameId }
        })
      } else {
        this.loading = true
        const qResponse = await this.gameStore.enterInQueList()
        await this.loadCurrentWaitingRoom()
        this.queResponse = qResponse
        if (qResponse.gameSession) {
          this.$router.push({ name: 'game', params: { gameId: qResponse.gameSession?.gameId } })
        } else {
          this.popUpMessage = `Vous êtes dans la file d'attente.`
          this.showPopUp = true
        }
        this.loading = false
      }
    },
    checkIfGameMatched() {
      if (this.queResponse) {
        if (this.notificationStore.allRealTimeNotifications.length === 0) return
        const lastNotification = this.notificationStore.allRealTimeNotifications[0]
        if (!this.authStore.getUser) return
        if (
          lastNotification &&
          lastNotification.type === RealTimeNotificationType.GameWaitingQue &&
          lastNotification.title === RealTimeNotificationTitle.GameMatched &&
          lastNotification.userId === this.authStore.getUser.id
        ) {
          this.$router.push({
            name: 'game',
            params: { gameId: lastNotification.gameId }
          })
        }
      }
    },
    async checkWaitingQue() {
      if (this.notificationStore.allRealTimeNotifications.length === 0) return
      const lastNotification = this.notificationStore.allRealTimeNotifications[0]
      if (!this.authStore.getUser) return
      if (lastNotification && lastNotification.type === RealTimeNotificationType.GameWaitingQue) {
        await this.loadCurrentWaitingRoom()
      }
    },
    async loadCurrentWaitingRoom() {
      this.loading = true
      this.queList = await this.gameStore.getCurrentQueList()
      this.loading = false
    }
  }
})
</script>

<style scoped></style>
