<template>
  <div class="flex flex-col md:flex-row justify-between gap-4">
    <div class="flex gap-2">
      <div
        v-if="numberOfWins > 0"
        class="px-4 py-2 text-sm border bg-none inline-block rounded-md hover:bg-white/10"
      >
        <span class="flex gap-1 items-center">
          <v-avatar
            icon="tabler-trophy"
            color="yellow"
          />
          <span>WINNER CIRCLE achievement! (gagner 1 match)</span>
        </span>
      </div>

      <div
        v-if="numberOfGoals > 9"
        class="px-4 py-2 text-sm border bg-none inline-block rounded-md hover:bg-cyan-400/10"
      >
        <v-avatar
          icon="tabler-trophy"
          color="yellow"
        />
        <span> BIG SCORER achievement! (marquer 10 buts) </span>
      </div>
    </div>
  </div>
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
        console.log('histories not fetched')
      } finally {
        this.loading = false
      }
    }
  }
})
</script>
<style></style>
