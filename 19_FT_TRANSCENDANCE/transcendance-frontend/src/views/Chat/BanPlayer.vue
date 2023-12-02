<template>
  <v-btn
    :disabled="isLoading"
    color="primary"
    size="large"
    class="w-full text-xs"
    @click.prevent="handleUpdateIsBanned"
  >
    {{ banned ? 'Débannir' : 'Bannir' }}
    <VIcon
      v-if="failed"
      color="red"
      :size="12"
    >
      tabler-alert-triangle
    </VIcon>
  </v-btn>
</template>
<script setup lang="ts">
import { ref } from 'vue'
import useRoomsStore from '@/stores/RoomsStore'
import { ChatMemberRole } from '@/utils/chatSocket'

const roomsStore = useRoomsStore()

const props = defineProps({
  stateOfIsBanned: {
    type: Boolean,
    required: true
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
const banned = ref(props.stateOfIsBanned)
const failed = ref(false)

const handleUpdateIsBanned = async () => {
  try {
    isLoading.value = true
    const member = roomsStore.roomMembers.find((member) => member.memberId === props.userId)
    if (!member) return
    const newRole = banned.value ? ChatMemberRole.USER : ChatMemberRole.BAN
    await roomsStore.changeMemberRole(props.roomId, member, newRole)
    isLoading.value = false
    failed.value = false
  } catch (error) {
    failed.value = true
  } finally {
    isLoading.value = false
  }
}
</script>
<style></style>
