<template>
  <div class="flex items-center gap-6">
    <v-select
      v-model="role"
      :disabled="canNotPromote || isLoading"
      label="Role"
      :items="rolesList"
      item-title="text"
      item-value="value"
      variant="outlined"
    />

    <v-btn
      :disabled="memberRole === role || canNotPromote || isLoading"
      color="primary"
      variant="text"
      size="large"
      class="text-xs"
      @click="tryToMute"
    >
      Promouvoir
    </v-btn>
  </div>
</template>
<script setup lang="ts">
import { PropType, ref, computed } from 'vue'
import { ChatMemberRole } from '@/utils/chatSocket'
import useRoomsStore from '@/stores/RoomsStore'

const roomsStore = useRoomsStore()

const rolesList = [
  { value: ChatMemberRole.USER, text: 'Rétrograder' },
  { value: ChatMemberRole.ADMIN, text: 'Promouvoir' }
]

const props = defineProps({
  memberRole: {
    type: String as PropType<ChatMemberRole>,
    required: true,
    default: ChatMemberRole.USER
  },
  userId: {
    type: Number,
    required: true
  },
  roomId: {
    type: Number,
    required: true
  }
})

const isLoading = ref(false)
const role = ref(props.memberRole)

const canNotPromote = computed(() => {
  return (
    role.value === ChatMemberRole.OWNER ||
    role.value === ChatMemberRole.BAN ||
    role.value === ChatMemberRole.MUTED
  )
})

const tryToMute = async (e: Event) => {
  e.preventDefault()
  try {
    if (role.value === props.memberRole) return

    isLoading.value = true

    const member = roomsStore.roomMembers.find((member) => member.memberId === props.userId)
    if (!member) return
    await roomsStore.changeMemberRole(props.roomId, member, role.value)
    isLoading.value = false
  } catch (error) {
    console.info(error)
    isLoading.value = false
  }
}
</script>
<style></style>
