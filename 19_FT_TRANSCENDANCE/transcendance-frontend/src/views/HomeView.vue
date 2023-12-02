<template>
  <div>
    <div class="w-full">
      <greetings />
      <div class="w-full">
        <VCol class="w-full">
          <top-chat-card />
        </VCol>
      </div>
    </div>
    <div class="flex flex-row flex-wrap py-8">
      <div
        v-for="meta in userListStatsMeta"
        :key="meta.title"
        class="p-2 basis-1/2"
      >
        <VCard :loading="loadingStats">
          <VCardText class="flex justify-space-between">
            <div>
              <span>{{ meta.title }}</span>
              <div class="flex items-center gap-2 my-1">
                <h6 class="text-h6">
                  {{ Math.round(meta.stats) }}
                </h6>
              </div>
              <span>{{ meta.subtitle }}</span>
            </div>
            <v-avatar
              rounded
              variant="tonal"
              :color="meta.color"
              :icon="meta.icon"
            />
          </VCardText>
        </VCard>
      </div>
    </div>
    <div class="w-full">
      <VRow>
        <VCol>
          <player-simple-stats
            v-if="authStore.getUser"
            :histories="authStore.getUser.gameHistories"
            :user-id="authStore.getUser.id"
            :color-class="colorClasses"
          />
        </VCol>
      </VRow>
    </div>
    <div>
      <div class="flex gap-4 my-8 overflow-scroll hide-scrollbar">
        <div
          v-for="(friend, index) in userStore.contacts"
          :key="friend.id"
          class="flex flex-row items-center w-auto h-32 gap-4 p-4 border rounded-md max-w-64 grow-0 shrink-0"
        >
          <v-avatar
            rounded
            size="96"
            class="w-full h-32 cursor-pointer"
            @click.prevent="pushToUserProfile(friend.id, $router)"
          >
            <VImg
              v-if="friend.profile.avatar"
              class="w-full h-full"
              :src="friend.profile.avatar"
            />
            <VIcon
              v-else
              color="primary"
              icon="tabler-user"
            />
          </v-avatar>
          <div class="flex flex-col gap-4">
            <button
              class="text-base text-left font-weight-bold line-clamp-1"
              @click.prevent="pushToUserProfile(friend.id, $router)"
            >
              {{ friend.profile.name }} {{ friend.profile.lastname }}
            </button>
            <div class="flex flex-col gap-2">
              <game-status-badge
                v-if="gameStatus[index] && friend.profile.status"
                :status="friend.profile.status"
                :user-id="friend.id"
                :user-game-status="gameStatus[index]"
              />
              <div class="flex flex-row items-center gap-4">
                <status-badge
                  v-if="friend.id !== 0"
                  :user-id="friend.id"
                  :value="friend.profile.status"
                  class="w-16"
                />
                <button
                  class="flex items-center justify-center w-8 h-8 p-2 border rounded-md bg-green-400/50"
                  @click.prevent="pushToDmWithUser(friend.id, $router)"
                >
                  <v-icon
                    size="16"
                    icon="mdi-chat"
                  />
                </button>
                <button
                  class="flex items-center justify-center w-8 h-8 p-2 border rounded-md bg-yellow"
                >
                  <v-icon
                    size="16"
                    icon="mdi-goal"
                  />
                </button>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class="my-16">
      <leader-board-view :is-top-players="true" />
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore from '@/stores/AuthStore'
import useUserStore from '@/stores/UserStore'
import TopChatCard from '@/components/chatRooms/TopsChatCard.vue'
import PlayerSimpleStats from '@/components/profile/PlayerSimpleStats.vue'
import Greetings from '@/components/profile/Greetings.vue'
import useMessageStore from '@/stores/MessageStore'
import { pushToUserProfile, pushToDmWithUser } from '@/utils/router'
import GameStatusBadge from '@/components/game/GameStatusBadge.vue'
import StatusBadge from '@/components/profile/StatusBadge.vue'
import useGameStore, { GameSession } from '@/stores/GameStore'
import LeaderBoardView from './LeaderboardView.vue'

export default defineComponent({
  components: {
    PlayerSimpleStats,
    TopChatCard,
    Greetings,
    GameStatusBadge,
    StatusBadge,
    LeaderBoardView
  },
  setup() {
    const authStore = useAuthStore()
    const coalition = authStore.getCoalition
    const colorClasses = [`bg-[${coalition.color}]`, 'bg-opacity-30']
    const userStore = useUserStore()
    const messageStore = useMessageStore()
    const gameStore = useGameStore()
    return { authStore, colorClasses, userStore, messageStore, gameStore }
  },
  data() {
    const userListStatsMeta: Array<{
      icon: string
      color: 'primary' | 'error' | 'success' | 'warning'
      title: string
      stats: number
      subtitle: string
    }> = [
      {
        icon: 'tabler-user',
        color: 'primary',
        title: 'Utilisateurs',
        stats: 0,
        subtitle: 'Nombre total des utilisateurs'
      },
      {
        icon: 'tabler-table',
        color: 'error',
        title: 'Sessions',
        stats: 0,
        subtitle: 'Session creer les 30 derniers jours'
      },
      {
        icon: 'game-icons:ping-pong-bat',
        color: 'success',
        title: 'Parties par joeur',
        stats: 0,
        subtitle: 'Moyenne de parties, par utilisateur'
      },
      {
        icon: 'arcticons:games-2',
        color: 'warning',
        title: 'Total Parties',
        stats: 0,
        subtitle: 'Total, nombres de partie jouees'
      }
    ]
    return {
      userListStatsMeta,
      totalUser: 0,
      gameStatus: [] as Array<{
        status: 'playing' | 'inQueue' | 'free'
        gameSession?: GameSession
      }>,
      loadingStats: false
    }
  },
  async beforeMount() {
    await this.loadStats()
    await this.userStore.loadAllMyFriends()
    await this.fetchAllGameStatus()
  },
  methods: {
    async loadStats() {
      this.loadingStats = true
      await this.userStore.getAppStatistics()
      this.userListStatsMeta[0].stats = this.userStore.getStats.totalUsers
      this.userListStatsMeta[1].stats = this.userStore.getStats.activeUsers
      this.userListStatsMeta[2].stats = this.userStore.getStats.averageGamesPerUser
      this.userListStatsMeta[3].stats = this.userStore.getStats.totalGamesPlayed
      this.totalUser = this.userStore.getStats.totalUsers
      this.loadingStats = false
    },
    pushToUserProfile,
    pushToDmWithUser,
    async fetchAllGameStatus() {
      const ids = this.userStore.contacts.map((contact) => contact.id)
      this.gameStatus = await this.gameStore.getUsersGameStatus(ids)
    }
  }
})
</script>
