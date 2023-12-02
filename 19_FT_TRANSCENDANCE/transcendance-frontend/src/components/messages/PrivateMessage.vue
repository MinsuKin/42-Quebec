<script setup lang="ts">
import { PropType } from 'vue'

defineProps({
  message: {
    type: Object as PropType<{ id: number; message: string; time: string }>,
    required: true,
    default: () => ({ id: 0, message: '', time: '' })
  }
})
</script>

<template>
  <span>
    {{ message.message }}
  </span>
</template>

<style scoped></style>
