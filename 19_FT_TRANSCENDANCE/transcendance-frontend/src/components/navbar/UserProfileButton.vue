<template>
  <VMenu
    v-if="authStore.getUser"
    width="230"
    transition="scale-transition"
  >
    <template #activator="{ props }">
      <AvatarBadge
        v-if="authStore.getUser"
        class="cursor-pointer"
        v-bind="props"
        :user-id="authStore.getUser.id"
        :user="authStore.getUser"
        :bordered="true"
        avatar-variant="outlined"
      />
    </template>
    <VList>
      <VListItem :to="{ name: 'me' }">
        <template #prepend>
          <VListItemAction start>
            <AvatarBadge
              :user-id="authStore.getUser.id"
              :user="authStore.getUser"
            />
          </VListItemAction>
        </template>

        <VListItemTitle class="font-weight-semibold">
          {{ authStore.getUser.username }}
        </VListItemTitle>
        <VListItemSubtitle>
          {{ authStore.getUser.email }}
        </VListItemSubtitle>
      </VListItem>

      <VDivider class="my-2" />
      <VListItem :to="{ name: 'settings', params: { tab: 'account' } }">
        <template #prepend>
          <VIcon
            class="me-2"
            icon="tabler-settings"
            size="22"
          />
        </template>

        <VListItemTitle>Paramètre</VListItemTitle>
      </VListItem>
      <VListItem :to="{ name: 'settings', params: { tab: 'security' } }">
        <template #prepend>
          <VIcon
            class="me-2"
            icon="tabler-lock"
            size="22"
          />
        </template>

        <VListItemTitle>Sécurité</VListItemTitle>
      </VListItem>
      <VDivider class="my-2" />

      <VListItem
        link
        color="red"
        @click="logout"
      >
        <template #prepend>
          <VIcon
            class="me-2"
            icon="tabler-logout"
            size="22"
          />
        </template>
        <VListItemTitle>Se déconnecter</VListItemTitle>
      </VListItem>
    </VList>
  </VMenu>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore, { LoginStatus } from '@/stores/AuthStore'
import AvatarBadge from '@/components/profile/AvatarBadge.vue'

export default defineComponent({
  name: 'UserProfileButton',
  components: { AvatarBadge },
  setup() {
    const authStore = useAuthStore()
    return {
      authStore
    }
  },
  computed: {
    isOnline(): boolean {
      return this.authStore.status === LoginStatus.LOGGED
    }
  },
  methods: {
    async logout() {
      await this.authStore.logout()
      this.$router.push({ name: 'auth' })
    }
  }
})
</script>

<style scoped lang="scss"></style>
