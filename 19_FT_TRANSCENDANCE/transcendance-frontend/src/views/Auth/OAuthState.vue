<template>
  <Loader />
</template>
<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore, { LoginStatus } from '@/stores/AuthStore'
import Loader from '@/views/Auth/Loader.vue'

export default defineComponent({
  name: 'AuthState',
  components: { Loader },
  setup() {
    const authStore = useAuthStore()
    return { authStore }
  },
  async beforeMount() {
    const { token } = this.$route.query
    if (token) {
      this.authStore.setToken(token)
      await this.authStore.refreshCurrentUser()
      if (this.authStore.status === LoginStatus.LOGGED) {
        return this.$router.push({ name: 'dashboard' })
      } else if (this.authStore.status === LoginStatus.TWOFA_CHECK) {
        return this.$router.push({ name: 'two-factors' })
      }
    }
    return this.$router.push({ name: 'auth' })
  }
})
</script>
