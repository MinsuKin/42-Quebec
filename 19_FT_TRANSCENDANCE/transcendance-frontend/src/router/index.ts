import { createRouter, createWebHistory } from 'vue-router'
import useAuthStore, { LoginStatus } from '@/stores/AuthStore'
import dashboardRoutes from '@/router/dashboard'
import authRoutes from '@/router/auth'
import NotFound from '@/views/NotFoundView.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    dashboardRoutes,
    authRoutes,
    // ROUTE NOT FOUND REGEX
    {
      path: '/:catchALL(.*)', //regex to catch non existing routes
      name: 'NotFound',
      component: NotFound,
      meta: {
        requiresAuth: false,
        title: 'Not Found'
      }
    }
  ]
})

router.beforeEach((to, from, next) => {
  const authStore = useAuthStore()
  const requiresAuth = to.matched.some((record) => record.meta.requiresAuth)
  const isAuth = authStore.isLoggedIn
  if (requiresAuth && !isAuth) {
    const status = authStore.status
    switch (status) {
      case LoginStatus.LOCKED:
        if (to.name === 'locked-screen') {
          next()
        } else if (to.name === 'auth') {
          next({ name: 'auth' })
        } else {
          next({ name: 'locked-screen' })
        }
        break
      case LoginStatus.TWOFA_CHECK:
        if (to.name === 'two-factors') {
          next()
        } else {
          next({ name: 'two-factors' })
        }
        break
      default:
        next({ name: 'auth' })
    }
  } else {
    next()
  }
})

router.afterEach((to) => {
  if (to?.meta?.title) {
    let title = 'Transcendence'
    title = `${to.meta.title} | ${title}`
    document.title = title
  }
})

export default router
