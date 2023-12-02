import DashboardLayout from '@/layouts/DashboardLayout.vue'
import HomeView from '@/views/HomeView.vue'
import usersRoutes from '@/router/users'
import DirectMessagesView from '@/views/Dm/DirectMessagesMainView.vue'
import Notifications from '@/views/Notifications.vue'
import LeaderboardView from '@/views/LeaderboardView.vue'
import { RouteRecordRaw } from 'vue-router'
import GameView from '@/views/Game/GameView.vue'
import ChatHome from '@/views/Chat/ChatRooms.vue'
import waitingRoom from '@/views/Game/WaitingRoom.vue'
import Watching from '@/views/Game/Watching.vue'
import BotGame from '@/views/Game/BotGame.vue'

const dashboardRoutes: RouteRecordRaw = {
  path: '/',
  component: DashboardLayout,
  children: [
    {
      path: '',
      name: 'dashboard',
      component: HomeView,
      meta: {
        requiresAuth: true,
        title: 'Dashboard'
      }
    },
    {
      path: 'watching/:gameId?',
      name: 'watch-game',
      component: Watching,
      props: (route) => {
        const gameId = route.params.gameId ? parseInt(route.params.gameId.toString()) : undefined
        return {
          gameId
        }
      },
      meta: {
        requiresAuth: true,
        layoutWrapperClasses: 'layout-content-height-fixed',
        title: 'Watch Game'
      }
    },
    {
      path: 'waiting-room',
      name: 'waiting-room',
      component: waitingRoom,
      meta: {
        requiresAuth: true,
        layoutWrapperClasses: 'layout-content-height-fixed',
        title: 'Waiting Room'
      }
    },
    {
      path: 'bot-game',
      name: 'bot-game',
      component: BotGame,
      meta: {
        requiresAuth: true,
        layoutWrapperClasses: 'layout-content-height-fixed',
        title: 'Bot Game'
      }
    },
    {
      path: 'game/:gameId?',
      name: 'game',
      component: GameView,
      props: (route) => {
        const gameId = route.params.gameId ? parseInt(route.params.gameId.toString()) : undefined
        return {
          gameId
        }
      },
      meta: {
        requiresAuth: true,
        layoutWrapperClasses: 'layout-content-height-fixed',
        title: 'Pong'
      }
    },
    {
      path: 'chat/:roomId?',
      name: 'chat',
      component: ChatHome,
      props: (route) => {
        const roomId = route.params.roomId ? parseInt(route.params.roomId.toString()) : undefined
        return {
          roomId
        }
      },
      meta: {
        requiresAuth: true,
        title: 'Chat',
        layoutWrapperClasses: 'layout-content-height-fixed'
      }
    },
    {
      path: 'dm/:contactId?',
      name: 'dm',
      component: DirectMessagesView,
      props: (route) => {
        const contactId = route.params.contactId
          ? parseInt(route.params.contactId.toString())
          : undefined
        return {
          contactId
        }
      },
      meta: {
        requiresAuth: true,
        title: 'Mes Dm',
        layoutWrapperClasses: 'layout-content-height-fixed'
      }
    },
    {
      path: 'notifications',
      name: 'notifications',
      component: Notifications,
      meta: {
        requiresAuth: true,
        title: 'Vos notifications'
      }
    },
    {
      path: 'leaderboard',
      name: 'leaderboard',
      component: LeaderboardView,
      meta: {
        requiresAuth: true,
        title: 'LeaderBoard'
      }
    },
    usersRoutes
  ]
}

export default dashboardRoutes
