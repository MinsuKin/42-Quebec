<template>
  <div
    v-if="member"
    class="w-full p-2 text-center rounded-md cursor:pointer hover:bg-darkBlue/50"
  >
    <div class="flex items-center justify-between">
      <div class="flex items-center gap-2">
        <button
          class="w-40 overflow-scroll line-clamp-1 hide-scrollbar"
          @click.prevent.stop="pushToUserProfile(member.memberId, $router)"
        >
          <avatar-badge
            :user-id="member.memberId"
            :user-profile="member.member.profile"
            :show-username="true"
            :size="36"
            avatar-variant="tonal"
          />
        </button>
        <span class="flex items-center gap-2">
          <v-icon
            v-if="isOwner"
            :size="16"
            color="primary"
          > tabler-crown </v-icon>
          <v-icon
            v-else-if="isAdmin"
            :size="16"
            color="secondary"
          > tabler-shield-check </v-icon>
          <v-icon
            v-else-if="isMuted"
            :size="16"
            color="red"
            icon="mdi:volume-mute"
          />
          <v-icon
            v-else-if="isBan"
            :size="16"
            color="gray"
          > tabler-user-x </v-icon>
        </span>
      </div>
      <div
        v-if="!amTheMember"
        class="flex items-center gap-2"
      >
        <v-btn
          icon
          title="envoyer un message"
          :size="16"
          color="transparent"
          class="text-gray-400"
          @click.prevent.stop="pushToDmWithUser(member.memberId, $router)"
        >
          <v-icon
            :size="16"
            class=""
            title="Envoyer un message"
          >
            lets-icons:chat-light
          </v-icon>
        </v-btn>

        <v-menu
          v-model="menu"
          class=""
          :close-on-content-click="false"
          location="end"
        >
          <template #activator="{ props }">
            <button
              class="w-full p-2 text-left"
              icon
              v-bind="props"
            >
              <v-icon
                class="text-red-600"
                :size="16"
              >
                ri:user-settings-line
              </v-icon>
            </button>
          </template>

          <v-card>
            <v-list class="py-4">
              <v-list-item v-if="amTheOwner || (amAnAdmin && !isOwner && !isAdmin)">
                <div class="flex flex-col gap-3">
                  <mute-player
                    :state-of-is-muted="isMuted"
                    :room-id="member.chatroomId"
                    :user-id="member.memberId"
                  />
                  <div class="flex gap-2">
                    <div class="basis-1/2">
                      <ban-player
                        :state-of-is-banned="isBan"
                        :room-id="member.chatroomId"
                        :user-id="member.memberId"
                      />
                    </div>
                    <kick-player
                      :room-id="member.chatroomId"
                      :user-id="member.memberId"
                    />
                  </div>
                </div>
              </v-list-item>
              <v-divider v-if="(amAnAdmin && !isAdmin && !isOwner) || amTheOwner" />
              <v-list-item v-if="amTheOwner">
                <promote-player
                  :member-role="member.role"
                  :room-id="member.chatroomId"
                  :user-id="member.memberId"
                />
              </v-list-item>
              <v-divider v-if="(amAnAdmin && !isAdmin && !isOwner) || amTheOwner" />
              <div class="flex flex-col items-start gap-2 p-6 justify-normal">
                <game-status-badge :user-id="member.memberId" />
                <friend-request-box :friend-id="member.memberId" />
              </div>
            </v-list>
          </v-card>
        </v-menu>
      </div>
    </div>
  </div>
</template>
<script lang="ts">
import { defineComponent, PropType } from 'vue'
import MutePlayer from '@/views/Chat/MutePlayer.vue'
import AvatarBadge from '@/components/profile/AvatarBadge.vue'
import BanPlayer from '@/views/Chat/BanPlayer.vue'
import KickPlayer from '@/views/Chat/KickPlayer.vue'
import PromotePlayer from '@/views/Chat/PromotePlayer.vue'
import useRoomsStore, { MemberRoomWithUserProfiles } from '@/stores/RoomsStore'
import { pushToDmWithUser, pushToUserProfile } from '@/utils/router'
import { ChatMemberRole } from '@/utils/chatSocket'
import GameStatusBadge from '@/components/game/GameStatusBadge.vue'
import FriendRequestBox from '@/components/profile/FriendRequestBox.vue'

export default defineComponent({
  components: {
    MutePlayer,
    BanPlayer,
    PromotePlayer,
    AvatarBadge,
    GameStatusBadge,
    FriendRequestBox,
    KickPlayer
  },
  props: {
    member: {
      type: Object as PropType<MemberRoomWithUserProfiles>,
      required: true
    }
  },
  setup() {
    const roomStore = useRoomsStore()
    return {
      roomStore
    }
  },
  data() {
    return {
      menu: false
    }
  },
  computed: {
    isOwner(): boolean {
      if (!this.member) return false
      return this.member.role === ChatMemberRole.OWNER
    },
    me(): MemberRoomWithUserProfiles | undefined {
      const roomMembers = this.roomStore.roomMembers
      if (!roomMembers) return undefined
      return roomMembers.find((member) => member.memberId === this.roomStore.userId)
    },
    amAnAdmin(): boolean {
      if (!this.me) return false
      return this.me.role === ChatMemberRole.ADMIN
    },
    amTheMember(): boolean {
      if (!this.me) return false
      return this.me.memberId === this.member.memberId
    },
    amTheOwner(): boolean {
      if (!this.me) return false
      return this.me.role === 'OWNER'
    },

    isAdmin(): boolean {
      if (!this.me) return false
      return this.member.role === 'ADMIN'
    },
    isMuted(): boolean {
      if (!this.member) return false
      return this.member.role === 'MUTED'
    },
    isBan(): boolean {
      if (!this.member) return false
      return this.member.role === 'BAN'
    }
  },
  methods: {
    pushToDmWithUser,
    pushToUserProfile
  }
})
</script>
