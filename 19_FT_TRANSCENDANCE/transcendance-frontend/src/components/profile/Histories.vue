<template>
  <v-card
    title="Historique"
    :loading="loading"
  >
    <v-card-text>
      <p class="font-weight-semibold">
        Total Won : {{ getCountByEvent('MATCH_WON') }}
      </p>
      <p class="font-weight-semibold">
        Total Lost : {{ getCountByEvent('MATCH_LOST') }}
      </p>
      <p class="font-weight-semibold">
        Total Score : {{ getCountByEvent('ACTION_PERFORMED') }}
      </p>
    </v-card-text>
    <VTable>
      <thead>
        <tr>
          <th>Opposant</th>
          <th>Date</th>
          <th>Résultat</th>
          <th>Actions</th>
        </tr>
      </thead>
      <tbody>
        <tr
          v-for="history in histories"
          :key="history.gameId"
        >
          <td>
            <avatar-badge
              :user-id="getOpponentId(history)"
              :show-name="true"
              :size="32"
            />
          </td>
          <td>{{ getDate(history) }}</td>
          <td>
            <VChip
              v-if="getIsUserWon(history)"
              label
              color="success"
            >
              Victoire
            </VChip>
            <VChip
              v-else-if="getLostType(history) === 'perdu'"
              label
              color="error"
            >
              Défaite
            </VChip>
            <VChip
              v-else-if="getLostType(history) === 'abandon'"
              label
              color="orange"
            >
              Abandon
            </VChip>
            <VChip
              v-else-if="getLostType(history) === 'none'"
              label
              color="gray"
            >
              Déconnexion / Non confrontation
            </VChip>
          </td>
          <td class="flex gap-2">
            <div
              v-for="(userActions, i) in getActions(history)"
              :key="userActions.userId"
              class="flex items-center gap-2"
            >
              <avatar-badge
                :user-id="userActions.userId ?? 0"
                :size="32"
              />
              <span class="font-weight-bold text-slate-200 text-sm">{{ userActions.goals }} But(s)</span>
              <div class="v-avatar-group">
                <VAvatar
                  v-for="(eventInfo, index) in userActions.event"
                  :key="index"
                  :size="eventInfo.color === 'yellow' ? 32 : 24"
                  :variant="
                    eventInfo.color === 'yellow' || eventInfo.color === 'orange'
                      ? 'elevated'
                      : 'tonal'
                  "
                  :color="eventInfo.color"
                  :icon="eventInfo.icon"
                />
              </div>
              <p
                v-if="i === 0 && getGameType(history) !== GameSessionType.Bot"
                class="border-l border-r px-1 border-slate-200 font-weight-light text-slate-200 text-sm"
              >
                VS
              </p>
              <p
                v-else-if="getGameType(history) === GameSessionType.Bot"
                class="font-weight-light text-slate-200 text-sm"
              >
                IA
                <span class="font-weight-bold">{{ userActions.iaGoals }} But(s)</span>
              </p>
            </div>
          </td>
        </tr>
      </tbody>
    </VTable>
  </v-card>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import { formatDate } from '@core/utils/formatters'
import useGameStore, { CompleteGameHistory, GameSessionType } from '@/stores/GameStore'
import useUserStore from '@/stores/UserStore'
import AvatarBadge from '@/components/profile/AvatarBadge.vue'
import { GameEvent } from '@/interfaces/User'

type EventIcons = {
  icon:
    | 'ph:soccer-ball-fill'
    | 'tabler:trophy'
    | 'arcticons:quicklyquit'
    | 'game-icons:corner-explosion'
  color: 'success' | 'yellow' | 'error' | 'gray' | 'orange'
}
interface ActionsBox {
  userId: number
  goals: number
  iaGoals: number
  event: EventIcons[]
}

export default defineComponent({
  components: {
    AvatarBadge
  },
  props: {
    userId: {
      type: Number,
      required: true
    }
  },
  setup() {
    const userStore = useUserStore()
    const gameStore = useGameStore()
    return {
      gameStore,
      userStore
    }
  },
  data() {
    return {
      histories: [] as CompleteGameHistory[],
      loading: false
    }
  },
  computed: {
    GameSessionType() {
      return GameSessionType
    }
  },
  watch: {
    userId: {
      immediate: true,
      handler() {
        this.fetchHistories()
      }
    }
  },
  methods: {
    formatDate,
    async fetchHistories() {
      this.loading = true
      try {
        this.histories = await this.gameStore.getUserCompleteGameHistory(this.userId)
      } catch (e) {
        console.log('Complete histories not fetched')
      } finally {
        this.loading = false
      }
    },
    getGameType(gameHistory: CompleteGameHistory): GameSessionType {
      // Determine the game type base on game name
      switch (gameHistory.gameName) {
        case 'Bot Game':
          return GameSessionType.Bot
        case 'QueList Game':
          return GameSessionType.QueListGame
        case 'Challenge Game':
        default:
          return GameSessionType.PrivateGame
      }
    },
    getPlayersIds(gameHistory: CompleteGameHistory): number[] {
      const ids = Object.keys(gameHistory.histories)
      return ids.map((id) => parseInt(id, 10))
    },
    getOpponentId(gameHistory: CompleteGameHistory): number {
      const gameType = this.getGameType(gameHistory)
      if (gameType === GameSessionType.Bot) return 0
      // find the first one different from the user
      const playersId = this.getPlayersIds(gameHistory)
      const opponentId = playersId.find((id) => id !== this.userId)
      if (!opponentId) return -1
      return opponentId
    },
    getDate(gameHistory: CompleteGameHistory): string {
      const eventOfCurrentUser = Object.values(gameHistory.histories).find((UserHistories) => {
        return UserHistories.find((userHistory) => userHistory.userId === this.userId)
      })
      if (!eventOfCurrentUser) {
        return ''
      }
      const timestamp = eventOfCurrentUser[0].timestamp
      return formatDate(timestamp)
    },
    getIsUserWon(gameHistory: CompleteGameHistory) {
      const winner = gameHistory.winnerId
      return winner === this.userId
    },
    getLostType(gameHistory: CompleteGameHistory): 'perdu' | 'abandon' | 'none' {
      const histories = gameHistory.histories[this.userId]
      if (!histories) {
        return 'none'
      }
      const lostEvent = histories.find((history) => history.event === GameEvent.MATCH_LOST)
      if (lostEvent) {
        return 'perdu'
      }
      const startedTheGame = histories.find((history) => history.event === GameEvent.GAME_STARTED)
      if (startedTheGame) {
        return 'abandon'
      }
      return 'none'
    },
    pushGameEvents(event: GameEvent, actions: ActionsBox) {
      switch (event) {
        case GameEvent.ACTION_PERFORMED:
          actions.event.push({ icon: 'ph:soccer-ball-fill', color: 'success' })
          actions.goals++
          break
        case GameEvent.IA_ACTION_PERFORMED:
          actions.event.push({ icon: 'ph:soccer-ball-fill', color: 'gray' })
          actions.iaGoals++
          break
        case GameEvent.MATCH_WON:
          actions.event.push({ icon: 'tabler:trophy', color: 'yellow' })
          break
        case GameEvent.MATCH_LOST:
          actions.event.push({ icon: 'game-icons:corner-explosion', color: 'orange' })
          break
        case GameEvent.PLAYER_LEFT:
          actions.event.push({ icon: 'arcticons:quicklyquit', color: 'error' })
          break
      }
    },
    getActions(gameHistory: CompleteGameHistory): ActionsBox[] {
      // build a map with [userId, ACTION_PERFORMED count]
      const actions = new Map<number, ActionsBox>()
      for (const userID in gameHistory.histories) {
        const histories = gameHistory.histories[userID]
        const actionsInfo = {
          userId: parseInt(userID, 10),
          goals: 0,
          iaGoals: 0,
          event: []
        }
        histories.forEach((history) => {
          this.pushGameEvents(history.event, actionsInfo)
        })
        actions.set(parseInt(userID, 10), actionsInfo)
      }
      return Array.from(actions.values())
    },
    getCountByEvent(event: GameEvent) {
      let count = 0
      this.histories.forEach((gameHistory) => {
        const histories = Object.values(gameHistory.histories)
        histories.forEach((userHistories) => {
          userHistories.forEach((userHistory) => {
            if (userHistory.event === event && userHistory.userId === this.userId) {
              count++
            }
          })
        })
      })
      return count
    }
  }
})
</script>
