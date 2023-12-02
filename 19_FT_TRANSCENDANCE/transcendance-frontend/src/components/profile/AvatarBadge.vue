<template>
  <div
    v-if="userProfile"
    class="flex items-center gap-2"
  >
    <v-badge
      dot
      location="bottom right"
      offset-x="3"
      offset-y="3"
      :color="color"
      :bordered="bordered"
    >
      <v-avatar
        :variant="avatarVariant"
        :size="size"
        @click="$emit('showUserProfile')"
      >
        <v-img
          v-if="userProfile.profile.avatar"
          :src="userProfile.profile.avatar"
          :alt="`avatar de ${userProfile.username}`"
        />
        <span v-else>{{ avatarText(userProfile.username) }}</span>
      </v-avatar>
      <slot />
    </v-badge>
    <div
      v-if="showName"
      class="text-center"
    >
      <span class="ext-sm line-clamp-1">
        {{ userProfile.profile.name }} {{ userProfile.profile.lastname }}
      </span>
    </div>
    <div
      v-else-if="showUsername"
      class="text-center"
    >
      <span class="text-sm line-clamp-1">
        {{ userProfile.username }}
      </span>
    </div>
  </div>
  <div v-else>
    <!-- a loader badge or a circular loader -->
    <VBadge
      dot
      location="bottom right"
      offset-x="3"
      offset-y="3"
      color="error"
      :bordered="true"
      class="animate-pulse"
    >
      <VAvatar
        :size="size"
        icon="tabler-loader"
        @click="$emit('showUserProfile')"
      />
    </VBadge>
  </div>
</template>

<script lang="ts">
import { defineComponent, PropType } from 'vue'
import { avatarText } from '@core/utils/formatters'
import useUserStore, { ShortUserProfile } from '@/stores/UserStore'
import useAuthStore from '@/stores/AuthStore'
import { Status } from '@/interfaces/User'

export default defineComponent({
  props: {
    userId: {
      type: Number,
      required: true
    },
    user: {
      type: Object as PropType<ShortUserProfile>,
      required: false,
      default: undefined
    },
    showUsername: {
      type: Boolean,
      required: false,
      default: false
    },
    showName: {
      type: Boolean,
      required: false,
      default: false
    },
    covered: {
      type: Boolean,
      required: false,
      default: false
    },
    showStatus: {
      type: Boolean,
      required: false,
      default: false
    },
    size: {
      type: Number,
      required: false,
      default: 38
    },
    bordered: {
      type: Boolean,
      required: false,
      default: false
    },
    avatarVariant: {
      type: String as PropType<'flat' | 'tonal' | 'text' | 'elevated' | 'outlined' | 'plain'>,
      required: false,
      default: () => 'flat'
    }
  },
  emits: ['showUserProfile'],
  setup() {
    const usersStore = useUserStore()
    const authStore = useAuthStore()
    return {
      usersStore,
      authStore
    }
  },
  data() {
    return {
      userProfile: null as unknown as ShortUserProfile
    }
  },
  computed: {
    status(): Status {
      if (this.userId === 0) {
        return Status.Online
      }
      const localValue = this.userProfile.profile.status ?? Status.Offline
      return this.usersStore.getUsersStatus.get(this.userId) ?? localValue
    },
    color(): 'success' | 'error' | 'warning' | 'secondary' {
      return this.authStore.resolveAvatarBadgeVariant(this.status)
    }
  },
  watch: {
    userId: {
      handler(value: number) {
        this.loadUser(value)
      }
    },
    user: {
      handler(value: ShortUserProfile) {
        if (value) {
          this.userProfile = value
        } else {
          this.loadUser(this.userId)
        }
      },
      deep: true,
      immediate: true
    }
  },
  methods: {
    avatarText,
    async loadUser(userId: number) {
      const data = await this.usersStore.getShortUserProfile(userId)
      if (data) {
        this.userProfile = data
      }
    }
  }
})
</script>
