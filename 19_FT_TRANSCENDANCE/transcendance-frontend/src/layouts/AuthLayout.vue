<template>
  <main class="w-screen h-screen overflow-hidden">
    <VRow
      no-gutters
      class="w-full h-full"
    >
      <VCol
        cols="12"
        sm="6"
        md="8"
        class="hidden sm:block h-full w-full"
      >
        <img
          :src="bgImage"
          alt="landing"
          class="object-cover w-full h-full"
        >
      </VCol>
      <VCol
        cols="12"
        sm="6"
        md="4"
        class="mx-auto p-0 flex justify-center sm:block"
      >
        <router-view />
      </VCol>
    </VRow>
  </main>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore from '@/stores/AuthStore'

export default defineComponent({
  setup() {
    const authStore = useAuthStore()
    return { authStore }
  },
  data() {
    return {
      bgImages: ['/authbg.png', '/pong/backgrounds/pink_pong_bg.png']
    }
  },
  computed: {
    routeName(): string {
      return this.$route.name as string
    },
    bgImage(): string {
      if (this.routeName === 'auth') return this.bgImages[0]
      else if (this.routeName === 'reset-password') return this.bgImages[1]
      else return this.bgImages[0]
    }
  }
})
</script>

<style>
.bg-gradient {
  background-image: linear-gradient(to right, rgba(0, 0, 0, 0) 0%, #797e9e90 95%);
}
</style>
