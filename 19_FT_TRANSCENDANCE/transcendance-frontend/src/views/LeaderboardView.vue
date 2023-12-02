<template>
  <v-card class="border-none">
    <section class="max-w-screen-lg mx-auto">
      <div class="relative overflow-x-auto shadow-md sm:rounded-lg hide-scrollbar">
        <table class="w-full text-sm text-left text-gray-500 bg-none">
          <caption class="p-5 text-lg font-semibold text-left text-white bg-none">
            Classement des meilleurs joueurs
            <p class="mt-1 text-sm font-normal text-gray-500 dark:text-gray-400">
              Regardez le classement des joueurs du jeu. Les 3 premiers joueurs sont récompensés
              avec des awards spéciaux.
            </p>
          </caption>
          <thead class="text-xs uppercase border-b rounded-md text-gray-50 bg-none">
            <tr>
              <th class="px-1 py-1 text-center">
                Pos
              </th>
              <th class="px-6 py-3 text-center">
                Avatar
              </th>
              <th class="px-6 py-3 text-center">
                Username
              </th>
              <th class="px-6 py-3 text-center">
                Total
              </th>
              <th class="px-6 py-3 text-center">
                Victoires
              </th>
              <th class="px-6 py-3 text-center">
                Défaites
              </th>
            </tr>
          </thead>
          <tbody v-if="isTopPlayers">
            <tr
              v-for="(user, index) in topPlayers"
              :key="user.id"
              class="text-gray-200 bg-none"
            >
              <td class="w-10 px-1 py-1 text-xl font-bold text-gray-200 whitespace-nowrap">
                {{ index + 1 }}
              </td>
              <td class="px-6 py-4">
                <button
                  class="mx-auto"
                  @click.stop.prevent="pushToUserProfile(user.id, $router)"
                >
                  <avatar-badge :user-id="user.id" />
                </button>
              </td>
              <td class="px-6 py-4">
                <button
                  class="w-48 line-clamp-1"
                  @click="(_) => pushToUserProfile(user.id, $router)"
                >
                  {{ user.username }}
                </button>
              </td>
              <td class="px-6 py-4">
                {{
                  getCountByEvent(user?.gameHistories, 'MATCH_WON') +
                    getCountByEvent(user?.gameHistories, 'MATCH_LOST')
                }}
              </td>
              <td class="px-6 py-4">
                {{ getCountByEvent(user?.gameHistories, 'MATCH_WON') }}
              </td>
              <td class="px-6 py-4">
                {{ getCountByEvent(user?.gameHistories, 'MATCH_LOST') }}
              </td>
              <td class="px-6 py-4 text-right">
                <game-status-badge
                  v-if="user.gameStatus && user.id !== authStore.user?.id"
                  :user-game-status="user.gameStatus"
                  :user-id="user.id"
                  :status="user?.profile?.status"
                />
              </td>
            </tr>
          </tbody>
          <tbody v-else>
            <tr
              v-for="(user, index) in users"
              :key="user.id"
              class="text-gray-200 bg-none"
            >
              <th
                class="w-4 px-1 py-1 text-xl font-bold text-gray-200 whitespace-nowrap dark:text-white"
              >
                {{ index + 1 }}
              </th>
              <td class="px-6 py-4">
                <button @click="(_) => pushToUserProfile(user.id, $router)">
                  <avatar-badge :user-id="user.id" />
                </button>
              </td>
              <td class="px-6 py-4">
                <button
                  class="w-48 line-clamp-1"
                  @click="(_) => pushToUserProfile(user.id, $router)"
                >
                  {{ user.username }}
                </button>
              </td>
              <td class="px-6 py-4">
                {{
                  getCountByEvent(user?.gameHistories, 'MATCH_WON') +
                    getCountByEvent(user?.gameHistories, 'MATCH_LOST')
                }}
              </td>
              <td class="px-6 py-4">
                {{ getCountByEvent(user?.gameHistories, 'MATCH_WON') }}
              </td>
              <td class="px-6 py-4">
                {{ getCountByEvent(user?.gameHistories, 'MATCH_LOST') }}
              </td>
            </tr>
          </tbody>
        </table>
      </div>
    </section>
  </v-card>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore from '@/stores/AuthStore'
import useUserStore, { UserWithScore } from '@/stores/UserStore'
import AvatarBadge from '@/components/profile/AvatarBadge.vue'
import GameStatusBadge from '@/components/game/GameStatusBadge.vue'
import useGameStore from '@/stores/GameStore'
import { GameEvent, GameHistory } from '@/interfaces/User'
import { pushToUserProfile } from '@/utils/router'

export default defineComponent({
  name: 'LeaderBoardView',
  components: { GameStatusBadge, AvatarBadge },
  props: {
    isTopPlayers: {
      type: Boolean,
      default: false
    }
  },
  setup() {
    const userStore = useUserStore()
    const authStore = useAuthStore()
    const gameStore = useGameStore()
    return {
      userStore,
      authStore,
      gameStore
    }
  },
  data() {
    return {
      users: [] as UserWithScore[],
      loading: false
    }
  },
  computed: {
    topPlayers(): UserWithScore[] {
      return this.users.slice(0, 3)
    }
  },
  async beforeMount() {
    await this.fetchUsersGameStatusAndScores()
  },
  methods: {
    getCountByEvent(gameHistories: GameHistory[] | undefined, event: GameEvent) {
      if (!gameHistories) return 0
      return gameHistories.filter((history) => history.event === event).length
    },
    async fetchUsersGameStatusAndScores() {
      this.loading = true
      const users = await this.userStore.getPaginatedUsersWithScore({ take: 100 })
      const usersIds = users.map((user) => user.id)
      const usersGameStatus = await this.gameStore.getUsersGameStatus(usersIds)
      this.users = users.map((user, index) => {
        const userGameStatus = usersGameStatus[index]
        return {
          ...user,
          gameStatus: userGameStatus
        }
      })
      this.loading = false
    },
    pushToUserProfile
  }
})
</script>

<style lang="css">
.texte {
  color: white;
}
.special-avatar-gold {
  background-color: gold; /* Define gold style */
  /* Add any other custom styling for gold here */
}

.special-avatar-silver {
  background-color: silver; /* Define silver style */
  /* Add any other custom styling for silver here */
}

.special-avatar-bronze {
  background-color: #cd7f32; /* Define bronze style */
  /* Add any other custom styling for bronze here */
}

.special-avatar-trans {
  background-color: transparent; /* Define bronze style */
  /* Add any other custom styling for bronze here */
}
</style>
