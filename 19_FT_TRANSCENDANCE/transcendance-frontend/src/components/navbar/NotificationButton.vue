<template>
  <VBtn
    icon
    variant="text"
    color="default"
    class="mx-1"
  >
    <VBadge
      :color="notificationStore.unreadNotificationsCount > 0 ? 'red' : 'secondary'"
      :content="notificationStore.unreadNotificationsCount"
    >
      <VIcon
        icon="tabler-bell"
        size="24"
      />
    </VBadge>
    <VMenu
      activator="parent"
      width="380px"
      location="bottom end"
      offset="14px"
    >
      <VList class="py-0">
        <VListItem
          title="Notifications"
          height="48px"
        >
          <template #append>
            <VChip
              color="primary"
              size="small"
            >
              {{ notificationStore.unreadNotificationsCount }} notifications non lues
            </VChip>
          </template>
        </VListItem>
        <VDivider />
        <template v-if="notifications.length > 0">
          <div class="max-h-[500px] overflow-scroll hide-scrollbar">
            <VListItem
              v-for="notification in notifications"
              :key="notification.id"
            >
              <Notification
                :notification="notification"
                :is-short="true"
              />
            </VListItem>
          </div>
        </template>
        <VListItem v-else>
          <div class="flex justify-center items-center">
            <span class="text-gray-400">Aucune notifications</span>
          </div>
        </VListItem>
        <VDivider />
        <VListItem class="p-2">
          <VBtn
            block
            @click="readAllNotifications"
          >
            VOIR TOUTES LES NOTIFICATIONS
          </VBtn>
        </VListItem>
      </VList>
    </VMenu>
  </VBtn>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useNotificationStore from '@/stores/NotificationStore'
import Notification from '@/components/notifications/Notification.vue'
import { Notification as NotificationT } from '@/utils/notificationSocket'
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
  computed: {
    notifications(): NotificationT[] {
      return this.notificationStore.allNotifications
    }
  },
  methods: {
    readAllNotifications() {
      this.$router.push({ name: 'notifications' })
    }
  }
})
</script>

<style scoped></style>
