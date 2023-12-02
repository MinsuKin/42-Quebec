<template>
  <div
    v-if="canBeDisplayed"
    class="absolute z-50 h-full transition-all duration-300 ease-in border-l w-80 border-gray-50/10 md:relative md:right-0"
    :class="[roomStore.isRightNavOpen ? 'right-0' : '-right-full']"
    style="background-color: #0e1231"
  >
    <div class="flex flex-col h-full gap-0">
      <div
        class="flex items-center justify-between w-full px-2 border-b md:justify-center h-14 text-primary grow-0 shrink-0"
      >
        <v-btn
          class="md:hidden"
          icon
          color="transparent"
          size="24"
          @click="roomStore.toggleRightNav()"
        >
          <v-icon>iconamoon:close</v-icon>
        </v-btn>
        <span> Membres </span>
      </div>
      <div
        class="flex-1 h-full"
        :class="[!roomStore.isMemberOfRoom && roomStore.isPublic && 'blur-sm pointer-events-none']"
      >
        <div class="relative h-1/2 hide-scrollbar">
          <span
            class="absolute z-10 w-full px-8 py-2 h-[65px] bottom-0 bg-gradient-to-b from-[#262A46]/0 to-[80%] to-[#262A46]"
          />
          <div class="relative z-0 w-full h-full shrink-0 grow-0">
            <perfect-scrollbar
              tag="ul"
              :options="{
                wheelPropagation: false,
                suppressScrollX: true
              }"
              class="h-full pb-16 grow-0 srink-0 hide-scrollbar"
            >
              <li
                v-for="member in roomStore.roomMembers"
                :key="member.id"
                class="block px-2 py-2"
              >
                <chat-members-list-button :member="member" />
              </li>
            </perfect-scrollbar>
          </div>
        </div>
        <div class="h-1/2 hide-scrollbar">
          <invite-users />
        </div>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { computed } from 'vue'
import ChatMembersListButton from './ChatMembersListButton.vue'
import { PerfectScrollbar } from 'vue3-perfect-scrollbar'
import useRoomsStore from '@/stores/RoomsStore'
import InviteUsers from './InviteUser.vue'

defineProps({
  isLoading: {
    type: Boolean,
    required: true,
    default: true
  }
})
const roomStore = useRoomsStore()
const canBeDisplayed = computed(() => {
  return roomStore.isMemberOfRoom || roomStore.isPublic
})
</script>
