<template>
  <Loader />
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore from '@/stores/AuthStore'
import Loader from '@/views/Auth/Loader.vue'

export default defineComponent({
  components: { Loader },
  setup() {
    const authStore = useAuthStore()
    return { authStore }
  },
  async beforeMount() {
    if (!this.authStore.isLocked || !this.authStore.isLoggedIn) {
      await this.authStore.logout()
    }
    this.$router.push({ name: 'auth' })
  }
})
</script>

<style></style>
