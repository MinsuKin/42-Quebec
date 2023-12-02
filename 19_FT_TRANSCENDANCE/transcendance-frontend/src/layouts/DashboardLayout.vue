<template>
  <VerticalNavLayout
    :nav-items="navItems"
    v-bind="layoutAttrs"
    class=""
  >
    <template #navbar="{ toggleVerticalOverlayNavActive }">
      <div class="flex items-center justify-between h-100">
        <VBtn
          v-if="isLessThanOverlayNavBreakpoint(windowWidth)"
          icon
          variant="text"
          color="default"
          class="ms-n3"
          size="small"
          @click="toggleVerticalOverlayNavActive(true)"
        >
          <VIcon
            icon="tabler-menu-2"
            size="24"
          />
        </VBtn>
        <NavSearchBar class="ms-lg-n3" />
        <VSpacer />
        <NotificationButton />
        <UserProfileButton />
      </div>
    </template>

    <RouterView v-slot="{ Component }">
      <Transition
        :name="appRouteTransition"
        mode="out-in"
      >
        <Component :is="Component" />
      </Transition>
    </RouterView>

    <template #footer>
      <NotificationPopUp
        v-if="challengeNotification"
        v-model:visible="showChallengePopUp"
        :snackbar-msg="challengeNotification.message"
        color="success"
      />
      <FooterSection />
    </template>
  </VerticalNavLayout>
</template>

<script setup lang="ts">
import { ref, watch } from 'vue'
import { useRouter } from 'vue-router'
import { useThemeConfig } from '@core/composable/useThemeConfig'
import navItems from '@/layouts/navigation'
import { VerticalNavLayout } from '@layouts'
import { useWindowSize } from '@vueuse/core'
import { useSkins } from '@core/composable/useSkins'
import FooterSection from '@/layouts/FooterSection.vue'
import NavSearchBar from '@/components/navbar/NavSearchBar.vue'
import UserProfileButton from '@/components/navbar/UserProfileButton.vue'
import NotificationButton from '@/components/navbar/NotificationButton.vue'
import useAuthStore from '@/stores/AuthStore'
import useNotificationStore from '@/stores/NotificationStore'
import {
  RealTimeNotification,
  RealTimeNotificationTitle,
  RealTimeNotificationType
} from '@/utils/notificationSocket'
import NotificationPopUp from '@/components/notifications/NotificationPopUp.vue'

const { appRouteTransition, isLessThanOverlayNavBreakpoint } = useThemeConfig()
const { width: windowWidth } = useWindowSize()
const { layoutAttrs, injectSkinClasses } = useSkins()
injectSkinClasses()
const authStore = useAuthStore()
const notificationStore = useNotificationStore()
const router = useRouter()

const showChallengePopUp = ref(false)
const challengeNotification = ref<RealTimeNotification>(null as unknown as RealTimeNotification)
const checkIfNewNotificationIsANewGameChallenge = (notification: RealTimeNotification) => {
  if (
    notification.type === RealTimeNotificationType.Game &&
    notification.title === RealTimeNotificationTitle.GameStarted
  ) {
    challengeNotification.value = notification
    if (!authStore.getUser?.id) return
    if (!notification.userId) return
    if (notification.userId === authStore.getUser.id) {
      showChallengePopUp.value = true
      if (notification.gameId) {
        router.push({ name: 'game', params: { gameId: notification.gameId } })
      }
    }
  }
}

// watch if new notification is a new game challenge
watch(notificationStore.allRealTimeNotifications, (notifications) => {
  if (notifications.length > 0) {
    checkIfNewNotificationIsANewGameChallenge(notifications[0])
  }
})
</script>

<style lang="scss">
@use '@layouts/styles/default-layout';
</style>
