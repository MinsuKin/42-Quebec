<template>
  <VChip
    label
    :color="color"
  >
    {{ status }}
  </VChip>
</template>

<script setup lang="ts">
import { computed, PropType } from 'vue'
import useUserStore from '@/stores/UserStore'
import useAuthStore from '@/stores/AuthStore'
import { Status } from '@/interfaces/User'

const props = defineProps({
  userId: {
    type: Number,
    required: true
  },
  value: {
    type: String as PropType<Status>,
    required: true,
    default: () => Status.Offline
  }
})
const usersStore = useUserStore()
const authStore = useAuthStore()

const status = computed(() => {
  const localValue = props.value ?? Status.Offline
  return usersStore.getUsersStatus.get(props.userId) ?? localValue
})
const color = computed<'success' | 'error' | 'warning' | 'secondary'>(() => {
  return authStore.resolveAvatarBadgeVariant(status.value)
})
</script>
