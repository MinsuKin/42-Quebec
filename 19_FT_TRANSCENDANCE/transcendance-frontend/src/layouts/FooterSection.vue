<template>
  <div class="flex justify-between h-100 align-center">
    <span class="flex items-center text-xs font-light"> Pong 🏓 by FTMJR </span>
    <span class="text-xs font-light">
      &copy; {{ new Date().getFullYear() }} - <strong>Transcendance</strong>
    </span>
  </div>
</template>
<script lang="ts">
import { defineComponent } from 'vue'

export default defineComponent({
  name: 'FooterSection'
})
</script>

<style scoped></style>
