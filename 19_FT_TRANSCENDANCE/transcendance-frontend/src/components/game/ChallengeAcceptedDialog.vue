<template>
  <v-row justify="center">
    <v-dialog
      v-model="dialog"
      persistent
      width="auto"
    >
      <v-card :loading="loading">
        <v-card-title class="text-h5">
          Un defi est en cours !, la partie est lancée
        </v-card-title>
        <v-card-text>
          {{ notification.message }}
        </v-card-text>
        <v-card-text>
          Vous allez être redirigé vers la page de jeu. Vous pouvez aussi abandonner le défi, mais
          vous perdrez la partie.
        </v-card-text>
        <v-card-actions>
          <v-btn
            color="error"
            variant="outlined"
            @click="abandon"
          >
            Abandonner
          </v-btn>
          <v-btn
            color="success"
            variant="elevated"
            @click="acceptChallenge"
          >
            Jouer
          </v-btn>
        </v-card-actions>
      </v-card>
    </v-dialog>
  </v-row>
</template>

<script lang="ts">
import { defineComponent, PropType } from 'vue'
import { RealTimeNotification } from '@/utils/notificationSocket'
import useGameStore from '@/stores/GameStore'
import useNotificationStore from '@/stores/NotificationStore'

export default defineComponent({
  name: 'ChallengeAcceptedDialog',
  props: {
    showDialog: {
      type: Boolean,
      required: true
    },
    notification: {
      type: Object as PropType<RealTimeNotification>,
      required: true
    }
  },
  emits: ['update:showDialog'],
  setup() {
    const gameStore = useGameStore()
    const notificationStore = useNotificationStore()
    return {
      gameStore,
      notificationStore
    }
  },
  data() {
    return {
      loading: false
    }
  },
  computed: {
    dialog: {
      get() {
        return this.showDialog
      },
      set(value: boolean) {
        this.$emit('update:showDialog', value)
      }
    }
  },
  methods: {
    async acceptChallenge() {
      this.loading = true
      await this.gameStore.getAllGameSessions()
      this.loading = false
      if (this.notification.gameId) {
        this.$router.push({ name: 'game', params: { gameId: this.notification.gameId } })
      }
      this.dialog = false
    },
    async abandon() {
      this.loading = true
      if (this.notification.gameId) {
        await this.gameStore.quitGameSession(this.notification.gameId)
      }
      this.loading = false
      this.dialog = false
    }
  }
})
</script>

<style scoped></style>
