<template>
  <VCard v-if="info">
    <VImg
      :src="info.coalition?.cover_url"
      :cover="true"
      max-height="12rem"
    />
    <VCardText class="flex flex-col gap-2 md:flex-row md:justify-between">
      <div class="flex">
        <VAvatar
          rounded
          size="120"
          class="mx-auto user-profile-avatar -mb-6"
        >
          <VImg
            v-if="info.avatar"
            :src="info.avatar"
          />
          <VIcon
            v-else
            color="primary"
            icon="tabler-user"
          />
        </VAvatar>
        <CoalitionFlag
          :color="info.coalition?.color"
          :image="info.coalition?.image_url"
        />
      </div>
      <div class="w-full">
        <h6 class="sm:text-center md:text-left text-h6 font-weight-semibold">
          {{ info?.fullName }}
        </h6>
        <div class="flex justify-center md:flex-col gap-2 flex-grow-1">
          <span class="flex">
            <VIcon
              size="20"
              icon="game-icons:space-suit"
              :color="info.coalition?.color"
            />
            <span class="text-lg font-weight-semibold text-primary">{{ info?.username }}</span>
          </span>
          <v-tooltip
            :text="`A rejoins la communauté le ${showDateFormated(info?.joiningDate)}`"
            bottom
          >
            <template #activator="{ props }">
              <span
                class="flex items-center"
                v-bind="props"
              >
                <VIcon
                  size="20"
                  icon="tabler-calendar"
                  class="me-2"
                />
                <span class="text-body-1">{{ showDateFormated(info?.joiningDate) }}</span>
              </span>
            </template>
          </v-tooltip>
          <StatusBadge
            v-if="id !== 0"
            :value="info.status"
            :user-id="id"
          />
        </div>
      </div>
      <div>
        <FriendRequestBox
          v-if="id !== 0"
          :friend-id="id"
        />
      </div>
    </VCardText>
  </VCard>
</template>
<script lang="ts">
import { defineComponent, PropType } from 'vue'
import type { ProfileHeaderData } from '@/interfaces/User'
import useAuthStore from '@/stores/AuthStore'
import useUserStore from '@/stores/UserStore'
import FriendRequestBox from '@/components/profile/FriendRequestBox.vue'
import CoalitionFlag from '@/components/profile/CoalitionFlag.vue'
import StatusBadge from '@/components/profile/StatusBadge.vue'

export default defineComponent({
  components: {
    StatusBadge,
    CoalitionFlag,
    FriendRequestBox
  },
  props: {
    info: {
      type: Object as PropType<ProfileHeaderData>,
      required: true
    },
    id: {
      type: Number,
      required: true
    }
  },
  setup() {
    const authStore = useAuthStore()
    const userStore = useUserStore()
    return { authStore, userStore }
  },
  computed: {},
  beforeMount() {},
  methods: {
    showDateFormated(date: string | Date): string {
      return new Date(date).toLocaleDateString('fr-CA', {
        year: 'numeric',
        month: 'long',
        day: 'numeric'
      })
    }
  }
})
</script>

<style lang="scss">
.user-profile-avatar {
  border: 5px solid rgb(var(--v-theme-surface));
  background-color: rgb(var(--v-theme-surface)) !important;
  inset-block-start: -3rem;
  .v-img__img {
    border-radius: 0.125rem;
  }
}
</style>
