import Settings from '@/views/User/UserSettings.vue'
import UserList from '@/views/User/UserList.vue'
import UserShowView from '@/views/User/UserShow.vue'
import useAuthStore from '@/stores/AuthStore'
import { RouteRecordRaw } from 'vue-router'

const usersRoutes: RouteRecordRaw = {
  path: 'users',
  children: [
    {
      path: '',
      name: 'user-list',
      component: UserList,
      meta: {
        requiresAuth: true,
        title: 'Liste des utilisateurs'
      }
    },
    {
      path: 'me/:tab?',
      name: 'me',
      component: UserShowView,
      props: (route) => {
        const userId = useAuthStore().user?.id ? useAuthStore().user?.id : undefined
        const tab = route.params.tab ? route.params.tab : undefined
        return {
          userId,
          tab
        }
      },
      meta: {
        requiresAuth: true,
        title: 'Mon Profil'
      }
    },
    {
      path: 'show/:userId/:tab?',
      name: 'user-profile',
      component: UserShowView,
      props: (route) => {
        const userId = parseInt(route.params.userId.toString()) ?? undefined
        const tab = route.params.tab ? route.params.tab : undefined
        return {
          userId,
          tab
        }
      },
      meta: {
        requiresAuth: true,
        title: 'Voir Le Profile'
      }
    },
    {
      path: 'settings/:tab',
      name: 'settings',
      component: Settings,
      meta: {
        requiresAuth: true,
        title: 'Réglages'
      }
    }
  ]
}

export default usersRoutes
