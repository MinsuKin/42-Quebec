<template>
  <div class="flex items-center gap-6">
    <v-select
      v-model="delay"
      :disabled="isMuted || isLoading"
      label="Select"
      :items="delayList"
      variant="outlined"
      class="w-32"
    />
    <v-btn
      :disabled="isMuted || isLoading"
      color="primary"
      variant="text"
      size="large"
      class="text-xs"
      @click="tryToMute"
    >
      Mute
    </v-btn>
  </div>
</template>
<script setup lang="ts">
import { ref, onMounted } from 'vue'
import useRoomsStore from '@/stores/RoomsStore'
import { ChatMemberRole } from '@/utils/chatSocket'

const roomsStore = useRoomsStore()

const delayList = [
  '30 sec',
  '1 min',
  '5 min',
  '10 min',
  '30 min',
  '1 h',
  '1 j',
  '1 sem',
  '1 mois',
  '1 an'
]

const props = defineProps({
  stateOfIsMuted: {
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
const isMuted = ref(props.stateOfIsMuted)
const delay = ref(delayList[0])

const makeMuteDelayTimestamp = (value: string) => {
  switch (value) {
    case '30 sec':
      return 30 * 1000
    case '1 min':
      return 60 * 1000
    case '5 min':
      return 60 * 5 * 1000
    case '30 min':
      return 60 * 30 * 1000
    case '1 h':
      return 3600 * 1000
    case '1 j':
      return 86400 * 1000
    case '1 sem':
      return 604800 * 1000
    case '1 mois':
      return 2592000 * 1000
    case '1 an':
      return 31536000 * 1000
    case '10 min':
    default:
      return 60 * 10 * 1000
  }
}

const tryToMute = async () => {
  try {
    if (isMuted.value) return
    isLoading.value = true
    const now = new Date().getTime()
    const expiresAt = now + makeMuteDelayTimestamp(delay.value)
    const member = roomsStore.roomMembers.find((member) => member.memberId === props.userId)
    if (!member) return
    await roomsStore.changeMemberRole(props.roomId, member, ChatMemberRole.MUTED, expiresAt)
    isLoading.value = false
  } catch (error) {
    isLoading.value = false
  }
}

onMounted(() => {})
</script>
<style></style>
