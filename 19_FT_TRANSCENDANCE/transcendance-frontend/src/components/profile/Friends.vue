<template>
  <VCard
    :loading="loading"
    color="transparent"
    class="border-none"
  >
    <h2 class="text-4xl uppercase font-bold mb-8">
      Vos amis
    </h2>
    <VRow v-if="userStore.contacts.length">
      <VCol
        v-for="(friend, index) in userStore.contacts"
        :key="friend.id"
        cols="12"
        md="6"
      >
        <div class="bg-slate-700/30 rounded-lg mx-1 mt-8">
          <div class="flex items-center justify-center">
            <VAvatar
              rounded
              size="120"
              class="user-profile-avatar"
            >
              <VImg
                v-if="friend.profile?.avatar"
                :src="friend.profile?.avatar"
              />
              <VIcon
                v-else
                color="primary"
                icon="tabler-user"
              />
            </VAvatar>
          </div>
          <div class="relative -top-12">
            <VCardText class="flex flex-col items-center">
              <p class="text-center text-lg font-weight-bold">
                {{ friend.profile?.name }} {{ friend.profile?.lastname }}
              </p>
              <router-link
                class="text-center text-lg font-weight-semibold text-purple-500"
                :to="{
                  name: 'user-profile',
                  params: {
                    userId: friend.id,
                    tab: 'profile'
                  }
                }"
              >
                ☁︎ {{ friend.username }}
              </router-link>
            </VCardText>
            <div class="flex flex-column align-center justify-center gap-4">
              <friend-request-box :friend-id="friend.id" />
              <game-status-badge
                v-if="gameStatus[index] && friend.profile.status"
                :status="friend.profile.status"
                :user-id="friend.id"
                :user-game-status="gameStatus[index]"
              />
              <status-badge
                v-if="friend.id !== 0"
                :user-id="friend.id"
                :value="friend.profile?.status"
              />
              <VBtnGroup size="small">
                <VBtn
                  size="small"
                  color="blue"
                  variant="outlined"
                  :to="{
                    name: 'user-profile',
                    params: {
                      userId: friend.id,
                      tab: 'profile'
                    }
                  }"
                >
                  <span class="flex gap-2">
                    <VIcon left> mdi-account </VIcon>
                    <span> Profile </span>
                  </span>
                </VBtn>
                <VBtn
                  size="small"
                  color="purple"
                  variant="tonal"
                  :to="{ name: 'dm', params: { contactId: friend.id } }"
                >
                  <span class="flex gap-2">
                    <VIcon left> mdi-chat </VIcon>
                    <span> Discuter </span>
                  </span>
                </VBtn>
              </VBtnGroup>
            </div>
          </div>
        </div>
      </VCol>
    </VRow>
    <VRow v-else>
      <VCol cols="12">
        <div class="flex flex-col items-center justify-center gap-4">
          <VIcon
            size="100"
            color="primary"
            icon="mdi-account-multiple"
          />
          <p class="text-xl font-semibold">
            Vous n'avez pas encore d'amis
          </p>
          <p class="text-lg font-semibold">
            Ajoutez des amis pour jouer avec eux
          </p>
        </div>
      </VCol>
    </VRow>
  </VCard>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useUserStore from '@/stores/UserStore'
import FriendRequestBox from '@/components/profile/FriendRequestBox.vue'
import GameStatusBadge from '@/components/game/GameStatusBadge.vue'
import useGameStore, { GameSession } from '@/stores/GameStore'
import StatusBadge from '@/components/profile/StatusBadge.vue'

export default defineComponent({
  components: { GameStatusBadge, FriendRequestBox, StatusBadge },
  setup() {
    const userStore = useUserStore()
    const gameStore = useGameStore()
    return {
      userStore,
      gameStore
    }
  },
  data() {
    return {
      loading: false,
      gameStatus: [] as Array<{ status: 'playing' | 'inQueue' | 'free'; gameSession?: GameSession }>
    }
  },
  computed: {},
  async beforeMount() {
    await this.fetchFriends()
  },
  methods: {
    async fetchFriends() {
      this.loading = true
      await this.userStore.loadAllMyFriends()
      await this.fetchAllGameStatus()
      this.loading = false
    },
    async fetchAllGameStatus() {
      const ids = this.userStore.contacts.map((contact) => contact.id)
      this.gameStatus = await this.gameStore.getUsersGameStatus(ids)
    }
  }
})
</script>

<style scoped></style>
