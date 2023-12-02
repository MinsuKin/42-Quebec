<template>
  <VRow>
    <VCol
      v-for="meta in userListStatsMeta"
      :key="meta.title"
      cols="12"
      sm="6"
      lg="3"
    >
      <VCard>
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
          <VAvatar
            rounded
            variant="tonal"
            :color="meta.color"
            :icon="meta.icon"
          />
        </VCardText>
      </VCard>
    </VCol>
    <VCol cols="12">
      <VCard title="Rechercher un Joeur">
        <VCardText class="flex flex-wrap py-4 gap-4">
          <div class="w-24">
            <VSelect
              v-model="rowPerPage"
              density="compact"
              variant="outlined"
              :items="[10, 20, 30, 50]"
            />
          </div>
          <VSpacer />
          <div class="w-1/3">
            <VTextField
              v-model.lazy="searchQuery"
              :loding="loading"
              class="transparent-input-box"
              placeholder="Rechercher"
              hint="Sensible a la casse"
              :persistent-hint="true"
              clearable
            />
          </div>
        </VCardText>

        <VDivider />
        <VTable class="bg-transparent">
          <thead>
            <tr>
              <th scope="col">
                UTILISATEURS
              </th>
              <th scope="col">
                STATUS
              </th>
            </tr>
          </thead>
          <tbody>
            <tr
              v-for="user in users"
              :key="user.id"
            >
              <td>
                <div class="flex items-center">
                  <AvatarBadge
                    :user-id="user.id"
                    :user="user"
                  />

                  <div class="d-flex flex-column">
                    <h6 class="text-base">
                      <RouterLink
                        :to="{ name: 'user-profile', params: { userId: user.id } }"
                        class="font-weight-medium user-list-name"
                      >
                        {{ user.profile.name }} {{ user.profile.lastname }}
                      </RouterLink>
                    </h6>
                    <span class="text-sm text-disabled">@{{ user.username }}</span>
                  </div>
                </div>
              </td>
              <td>
                <div class="flex gap-4 items-center">
                  <StatusBadge
                    :value="user.profile.status"
                    :user-id="user.id"
                  />
                  <GameStatusBadge
                    v-if="user.gameStatus && user.id !== authStore.user?.id"
                    :user-game-status="user.gameStatus"
                    :user-id="user.id"
                    :status="user.profile?.status"
                  />
                </div>
              </td>
            </tr>
          </tbody>
        </VTable>
        <VDivider />

        <VCardText class="flex items-center fjustify-space-between gap-4 py-3 px-5">
          <span class="text-sm text-disabled">
            {{ paginationData }}
          </span>
          <VPagination
            v-model="currentPage"
            size="small"
            :total-visible="5"
            :length="totalPage"
          />
        </VCardText>
      </VCard>
    </VCol>
  </VRow>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useUserStore from '@/stores/UserStore'
import type { Profile, User } from '@/interfaces/User'
import { avatarText } from '@/vuetify/@core/utils/formatters'
import AvatarBadge from '@/components/profile/AvatarBadge.vue'
import useAuthStore from '@/stores/AuthStore'
import useGameStore, { GameSession } from '@/stores/GameStore'
import GameStatusBadge from '@/components/game/GameStatusBadge.vue'
import StatusBadge from '@/components/profile/StatusBadge.vue'

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

type userGameStatus = {
  status: 'playing' | 'inQueue' | 'free'
  gameSession?: GameSession
}
type SpecialUser = User & { gameStatus: userGameStatus; profile: Profile }

export default defineComponent({
  name: 'UserList',
  components: { StatusBadge, AvatarBadge, GameStatusBadge },
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
      loading: false,
      rowPerPage: 10,
      currentPage: 1,
      totalUser: 0,
      searchQuery: '',
      userListStatsMeta,
      users: [] as SpecialUser[]
    }
  },
  computed: {
    paginationData(): string {
      const firstIndex = this.users.length ? (this.currentPage - 1) * this.rowPerPage + 1 : 0
      const lastIndex = this.users.length + (this.currentPage - 1) * this.rowPerPage
      return `${firstIndex} de ${lastIndex} a ${this.totalUser} utilisateurs`
    },
    totalPage(): number {
      return Math.ceil(this.totalUser / this.rowPerPage) ?? 0
    }
  },
  watch: {
    currentPage(newValue, oldValue) {
      if (newValue !== oldValue) {
        this.fetchUsers()
      }
    },
    rowPerPage() {
      this.currentPage = 1
      this.fetchUsers()
    },
    searchQuery() {
      this.currentPage = 1
      this.fetchUsers()
    }
  },
  beforeMount() {
    this.loadStats().then(() => {
      this.fetchUsers()
    })
  },
  methods: {
    avatarText,
    async loadStats() {
      await this.userStore.getAppStatistics()
      this.userListStatsMeta[0].stats = this.userStore.getStats.totalUsers
      this.userListStatsMeta[1].stats = this.userStore.getStats.activeUsers
      this.userListStatsMeta[2].stats = this.userStore.getStats.averageGamesPerUser
      this.userListStatsMeta[3].stats = this.userStore.getStats.totalGamesPlayed
      this.totalUser = this.userStore.getStats.totalUsers
    },
    async fetchUsers() {
      this.loading = true
      if (!this.searchQuery) {
        const users = await this.userStore.getPaginatedUser({
          currentPage: this.currentPage,
          perPage: this.rowPerPage
        })
        this.users = users as SpecialUser[]
      } else {
        const users = await this.userStore.searchUsers({
          searchTerm: this.searchQuery,
          currentPage: this.currentPage,
          perPage: this.rowPerPage
        })
        this.users = users as SpecialUser[]
      }
      this.fetchUsersGameStatus()
      this.loading = false
    },
    fetchUsersGameStatus() {
      this.users.forEach((user) => {
        this.gameStore.getUserGameStatus(user.id).then((userGameStatus: userGameStatus) => {
          user.gameStatus = userGameStatus
        })
      })
    }
  }
})
</script>

<style scoped></style>
