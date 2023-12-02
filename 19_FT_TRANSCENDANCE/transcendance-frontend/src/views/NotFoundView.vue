<template>
  <main class="h-screen flex items-center justify-center">
    <div class="flex flex-col justify-center items-center p-8 space-y-4">
      <h1 class="font-sans font-bold text-white text-9xl hover:text-orange-500 hover:animate-pulse">
        404
      </h1>
      <p class="text-white text-base font-sans font-normal">
        Oupps, la page que vous cherchez n'existe pas sur le site. Clickez
        <router-link
          :to="{ name: 'dashboard' }"
          class="text-orange-500 hover:text-blue-700 font-semibold text-center animate-pulse"
        >
          ici
        </router-link>
        pour retourner sur la page d'accueil.
      </p>
    </div>
  </main>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
export default defineComponent({
  name: 'NotFound'
})
</script>
