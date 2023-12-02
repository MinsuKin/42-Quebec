<template>
  <div class="px-8 py-8">
    <div class="">
      <h1 class="text-4xl">
        Notifications
      </h1>
      <p class="mt-2 mb-0 text-sm">
        Voici une liste de ce qu'il se passe dans votre compte
        <br>
        Vous avez
        <span class="font-weight-semibold text-md">
          {{ notificationStore.unreadNotificationsCount }} notifications non lues
        </span>
      </p>
    </div>
    <div class="max-w-screen-sm p-8 my-16">
      <div class="flex flex-col gap-4">
        <div
          v-for="notification in notificationStore.allNotifications"
          :key="notification.id"
          class=""
        >
          <Notification
            :notification="notification"
            @mark-as-read="markAsRead"
          />
        </div>
      </div>
    </div>
  </div>
  <!-- <VCard>
    <VCardItem>
      <VCardTitle>Notifications</VCardTitle>
      <p class="mt-2 mb-0 text-sm">
        Voici une liste de ce qu'il se passe dans votre compte
        <br />
        Vous avez
        <span class="font-weight-semibold text-md">
          {{ notificationStore.unreadNotificationsCount }} notifications non lues
        </span>
      </p>
    </VCardItem>

    <VCardText>
      <VTable class="border rounded text-no-wrap bg-surface">
        <thead>
          <tr>
            <th scope="col">Notification</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="notification in notificationStore.allNotifications" :key="notification.id">
            <td class="text-center">
              <Notification :notification="notification" @mark-as-read="markAsRead" />
            </td>
          </tr>
        </tbody>
      </VTable>
    </VCardText>
  </VCard> -->
</template>
<script lang="ts">
import { defineComponent } from 'vue'
import useNotificationStore from '@/stores/NotificationStore'
import Notification from '@/components/notifications/Notification.vue'

export default defineComponent({
  components: { Notification },
  setup() {
    const notificationStore = useNotificationStore()
    return {
      notificationStore
    }
  },
  data() {
    return {}
  },
  beforeMount() {
    this.reloadNotifications()
  },
  methods: {
    markAsRead(notificationId: number) {
      this.notificationStore.markNotificationAsRead(notificationId)
      this.reloadNotifications()
    },
    deleteNotification(notificationId: number) {
      this.notificationStore.deleteNotification(notificationId)
    },
    openNotification() {
      // to do: implement, open the notification in a modal or the appropriate page
    },
    readAllNotifications() {
      // TODO: Implement
    },
    reloadNotifications() {
      this.notificationStore.getNotifications()
    }
  }
})
</script>

<style scoped></style>
