<template>
  <v-card
    color="transparent"
    class="shadow-lg drop-shadow-md"
  >
    <div :class="[colorClass, 'p-6']">
      <h2 class="text-4xl uppercase font-bold">
        Statistiques
      </h2>
      <v-card-text>
        <div class="flex flex-col md:flex-row items-center gap-4 justify-between">
          <div
            class="text-center flex items-center justify-start gap-1 basis-full md:basis-1/2 lg:basis-1/4"
          >
            <v-avatar
              icon="icon-park-twotone:game-three"
              color="primary"
              variant="tonal"
            />
            <!-- <v-avatar color="primary" variant="tonal" :size="64">
              <v-icon icon="" :size="32" class="h-full w-full"> icon-park-twotone:game-three </v-icon>
            </v-avatar> -->
            <p class="font-weight-bold text-xl">
              {{ numberOfGames }}
            </p>
            <h3 class="font-medium uppercase text-xl">
              Parties Jouée(s)
            </h3>
          </div>
          <div
            class="text-center flex items-center justify-start gap-1 basis-full md:basis-1/2 lg:basis-1/4"
          >
            <v-avatar
              icon="tabler-trophy"
              color="yellow"
            />
            <p class="font-weight-bold text-xl">
              {{ numberOfWins }}
            </p>
            <h3 class="font-medium uppercase text-xl">
              Victoire(s)
            </h3>
          </div>
          <div
            class="text-center flex items-center justify-start gap-1 basis-full md:basis-1/2 lg:basis-1/4"
          >
            <v-avatar
              icon="ph:soccer-ball-fill"
              color="blue"
              variant="tonal"
            />
            <p class="font-weight-bold text-xl">
              {{ numberOfGoals }}
            </p>
            <h3 class="font-medium uppercase text-xl">
              But(s)
            </h3>
          </div>
          <div
            class="text-center flex items-center justify-start gap-1 basis-full md:basis-1/2 lg:basis-1/4"
          >
            <VAvatar
              icon="tabler-shield-x"
              color="red"
              variant="tonal"
            />
            <p class="font-weight-bold text-xl">
              {{ numberOfLostGames }}
            </p>
            <h3 class="font-medium uppercase text-xl">
              Défaite(s)
            </h3>
          </div>
        </div>
      </v-card-text>
    </div>
  </v-card>
</template>

<script lang="ts">
import { defineComponent, PropType } from 'vue'
import { GameEvent, GameHistory } from '@/interfaces/User'
import useGameStore from '@/stores/GameStore'

export default defineComponent({
  props: {
    histories: {
      type: Array as PropType<GameHistory[]>,
      required: false,
      default: () => []
    },
    colorClass: {
      type: Array as PropType<string[]>,
      required: false,
      default: () => ['bg-red-500/30']
    },
    userId: {
      type: Number,
      required: true
    }
  },
  setup() {
    const gameStore = useGameStore()
    return {
      gameStore
    }
  },
  data() {
    return {
      gameHistories: [] as GameHistory[],
      loading: false
    }
  },
  computed: {
    gameActions(): Record<number, GameHistory[]> {
      return this.gameHistories.reduce(
        (acc, curr) => {
          const gameActions = acc[curr.gameId]
          if (gameActions) {
            gameActions.push(curr)
          } else {
            acc[curr.gameId] = [curr]
          }
          return acc
        },
        {} as Record<number, GameHistory[]>
      )
    },
    numberOfWins(): number {
      return this.gameHistories.filter((gameHistory) => {
        return gameHistory.event === GameEvent.MATCH_WON
      }).length
    },
    numberOfGoals(): number {
      return this.gameHistories.filter((gameHistory) => {
        return gameHistory.event === GameEvent.ACTION_PERFORMED
      }).length
    },
    numberOfLostGames(): number {
      return this.gameHistories.filter((gameHistory) => {
        return gameHistory.event === GameEvent.MATCH_LOST
      }).length
    },
    numberOfGames(): number {
      return this.numberOfWins + this.numberOfLostGames
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
  beforeMount() {
    if (!this.histories || this.histories.length === 0) {
      this.fetchHistories()
    } else {
      this.gameHistories = this.histories
    }
  },
  methods: {
    async fetchHistories() {
      this.loading = true
      try {
        this.gameHistories = await this.gameStore.getSimpleGameHistory(this.userId)
      } catch (e) {
        console.info('can not fetch history')
      } finally {
        this.loading = false
      }
    }
  }
})
</script>

<style scoped></style>
