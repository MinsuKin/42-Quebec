<template>
  <div />
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore from '@/stores/AuthStore'

export default defineComponent({
  name: 'ResetPassword',
  setup() {
    const authStore = useAuthStore()
    return { authStore }
  }
})
</script>

<style></style>
