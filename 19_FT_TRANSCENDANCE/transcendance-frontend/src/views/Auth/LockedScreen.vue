<template>
  <div class="h-full">
    <VCardText class="flex flex-col justify-center gap-4">
      <h5 class="text-h5 text-center font-semibold mb-1">
        Salut, {{ authStore.getProfile?.name }}
      </h5>
      <VAvatar
        rounded
        size="120"
        class="mx-auto"
      >
        <VImg
          v-if="authStore.getProfile?.avatar"
          :src="authStore.getProfile.avatar"
        />
        <VIcon
          v-else
          color="primary"
          icon="tabler-user"
        />
      </VAvatar>
      <p class="text-center font-light">
        Votre session est actuellement bloqué, pour des raisons de sécurité
      </p>
      <VBtn
        variant="text"
        @click="unlock"
      >
        Débloquer
      </VBtn>
    </VCardText>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore from '@/stores/AuthStore'

export default defineComponent({
  name: 'LockedScreen',
  setup() {
    const authStore = useAuthStore()
    return {
      authStore
    }
  },
  data() {
    return {
      isLoading: false
    }
  },
  beforeMount() {
    if (!this.authStore.isLocked) {
      this.$router.push({ name: 'dashboard' })
    }
  },
  methods: {
    async unlock() {
      this.isLoading = true
      try {
        await this.authStore.logout()
      } catch (e) {
        console.log('logOut, error')
      }
      this.isLoading = false
      this.$router.push({ name: 'auth' })
    }
  }
})
</script>

<style scoped></style>
