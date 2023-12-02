<template>
  <div class="h-full shrink-0 grow-0">
    <div class="p-2 w-full">
      <VTextField
        v-model.lazy="searchQuery"
        :loding="loading"
        placeholder="Rechercher un utilisateur a inviter"
        hint="Sensible a la casse"
        :persistent-hint="true"
        :clearable="true"
        rounded
        append-icon="mdi-magnify"
      />
    </div>
    <PerfectScrollbar
      tag="ul"
      :options="{
        wheelPropagation: false,
        suppressScrollX: true
      }"
      class="h-full pt-4 pb-16 grow-0 srink-0 hide-scrollbar"
    >
      <li
        v-for="m in users"
        :key="m.id"
        class="block px-2 py-2"
      >
        <div class="flex items-center gap-2">
          <AvatarBadgeVue
            :user-id="m.id"
            :user="m"
          />
          <span class="flex-1 inline-block w-16 max-w-full text-sm line-clamp-1">
            {{ m.username }}
          </span>
          <v-btn
            :size="24"
            icon
            color="transparent"
            @click.prevent="inviteUser(m.id)"
          >
            <v-icon :size="16">
              mingcute:add-fill
            </v-icon>
          </v-btn>
        </div>
      </li>
    </PerfectScrollbar>
  </div>
</template>
<script setup lang="ts">
import { ref, watch } from 'vue'
import useUserStore from '@/stores/UserStore'
import { Profile, User } from '@/interfaces/User'
import { PerfectScrollbar } from 'vue3-perfect-scrollbar'
import useRoomsStore from '@/stores/RoomsStore'
import AvatarBadgeVue from '@/components/profile/AvatarBadge.vue'

const userStore = useUserStore()
const roomStore = useRoomsStore()
const invitedUsers = ref<Array<number>>([])

const loading = ref(false)
const searchQuery = ref('')
let users = ref<Array<User & { profile: Profile }>>([])

const fetchUsers = async () => {
  loading.value = true
  const data = await userStore.searchUsers({
    searchTerm: searchQuery.value.trim(),
    currentPage: 1,
    perPage: 15
  })
  const currentRoomMembers = roomStore.currentRoomMembers
  users.value = data.filter((user) => {
    return !currentRoomMembers.find((m) => m.memberId === user.id)
  })
  loading.value = false
}

watch(searchQuery, (newValue) => {
  if (newValue) {
    if (newValue.length > 0) {
      fetchUsers()
    }
  } else {
    users.value.splice(0, users.value.length)
  }
})

const inviteUser = async (userId: number) => {
  if (!roomStore.currentRoom) return
  const r = await roomStore.inviteUser(roomStore.currentRoom.id, userId)
  if (r !== 'success') return
  invitedUsers.value.push(userId)
  users.value = users.value.filter((u) => u.id !== userId)
}
</script>
