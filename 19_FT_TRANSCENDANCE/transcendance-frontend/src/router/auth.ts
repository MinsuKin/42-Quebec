import AuthLayout from '@/layouts/AuthLayout.vue'
import AuthView from '@/views/Auth/AuthView.vue'
import TwoFactorsView from '@/views/Auth/TwoFactorsView.vue'
import ResetPasswordView from '@/views/Auth/ResetPasswordView.vue'
import LockedScreen from '@/views/Auth/LockedScreen.vue'
import OAuthStateView from '@/views/Auth/OAuthState.vue'

const authRoutes = {
  path: '/auth',
  component: AuthLayout,
  children: [
    {
      path: '',
      name: 'auth',
      component: AuthView,
      meta: {
        requiresAuth: false,
        title: 'Authentification'
      }
    },
    {
      path: 'reset-password',
      name: 'reset-password',
      component: ResetPasswordView,
      meta: {
        requiresAuth: false,
        title: 'Reset Password'
      }
    },
    {
      path: 'two-factors',
      name: 'two-factors',
      component: TwoFactorsView,
      meta: {
        requiresAuth: true,
        title: 'Two Factors'
      }
    },
    {
      path: 'locked',
      name: 'locked-screen',
      component: LockedScreen,
      meta: {
        requiresAuth: true,
        title: 'Locked Screen'
      }
    },
    {
      path: 'oauth-auth',
      name: 'oauth-auth',
      component: OAuthStateView,
      meta: {
        requiresAuth: false,
        title: 'OAuth Auth'
      }
    }
  ]
}
export default authRoutes
