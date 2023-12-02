import { VerticalNavItems } from '@layouts/types'

const navItems: VerticalNavItems = [
  {
    title: 'Tableau de bord',
    icon: { icon: 'tabler-smart-home' },
    to: { name: 'dashboard' }
  },
  {
    title: 'Play solo 🤖',
    icon: { icon: 'noto-v1:game-die' },
    to: { name: 'bot-game' }
  },
  {
    title: 'Waiting Room',
    icon: { icon: 'medical-icon:i-waiting-area', color: 'green' },
    to: { name: 'waiting-room' }
  },
  {
    title: 'Trouver un joueur',
    icon: { icon: 'tabler-users-group', color: 'blue' },
    to: { name: 'user-list' }
  },
  {
    title: 'Leaderboard',
    icon: { icon: 'solar:ranking-linear', color: 'yellow' },
    to: { name: 'leaderboard' }
  },
  { heading: 'Conversation' },
  {
    title: 'Chatrooms',
    icon: { icon: 'tabler-message' },
    to: { name: 'chat' }
  },
  {
    title: 'DMs',
    icon: { icon: 'tabler-mail' },
    to: { name: 'dm' }
  },
  { heading: 'Info' },
  {
    title: 'Profile',
    icon: { icon: 'tabler-user' },
    children: [
      { title: 'Mon profile', to: { name: 'me', params: { tab: 'profile' } } },
      { title: 'Réglages', to: { name: 'settings', params: { tab: 'account' } } },
      { title: 'Historique', to: { name: 'me', params: { tab: 'history' } } }
    ]
  }
]
export default navItems
