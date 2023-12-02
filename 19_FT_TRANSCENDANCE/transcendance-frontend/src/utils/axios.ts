import axios from 'axios'
import useAuthStore from '@/stores/AuthStore'

// Create an Axios instance if you wish or use the default axios object
const axiosInstance = axios.create({
  baseURL: '/api'
  // other config here
})

const notRefreshableRoutes = [
  'auth/login',
  'auth/signup',
  'auth/refresh',
  'auth/signup',
  'auth/updatePassword',
  'auth/2fa/authenticate',
  'auth/2fa/enable',
  'auth/2fa/generate',
  'auth/updatePassword',
  '/api/auth/login',
  '/api/auth/signup',
  '/api/auth/refresh',
  '/api/auth/signup',
  '/api/auth/updatePassword',
  '/api/auth/2fa/authenticate',
  '/api/auth/2fa/enable',
  '/api/auth/2fa/generate',
  '/api/auth/updatePassword'
]
// Request interceptor
axiosInstance.interceptors.request.use(
  async (config) => {
    const authStore = useAuthStore()
    if (authStore.token && !authStore.isExpired) {
      config.headers['Authorization'] = `Bearer ${authStore.token}`
    }
    return config
  },
  (error) => {
    return Promise.reject(error)
  }
)

axiosInstance.interceptors.response.use(
  (response) => response,
  async (error) => {
    const authStore = useAuthStore()
    const originalRequest = error.config
    if (
      error.response.status === 401 &&
      !notRefreshableRoutes.includes(originalRequest.url) &&
      !originalRequest._retry &&
      authStore.token
    ) {
      originalRequest._retry = true
      const access_token = await authStore.refreshToken()
      axios.defaults.headers.common['Authorization'] = 'Bearer ' + access_token
      return axiosInstance(originalRequest)
    }
    return Promise.reject(error)
  }
)

export default axiosInstance
