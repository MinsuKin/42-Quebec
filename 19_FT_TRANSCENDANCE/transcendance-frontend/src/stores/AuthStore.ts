import { defineStore } from 'pinia'
import type {
  AuthState,
  ILoginData,
  RegisterBody,
  User,
  Profile,
  Coalition
} from '@/interfaces/User'
import { Status } from '@/interfaces/User'
import axios from '@/utils/axios'
import { isAxiosError } from 'axios'
import jwt_decode from 'jwt-decode'

export interface JwtPayload {
  email: string
  sub: {
    userId: number
    sessionId: number
    needToPassTwoFactor: boolean
  }
  exp: number
  iat: number
}

export enum LoginStatus {
  NOT_LOGGED = 'notLogged',
  LOGGED = 'logged',
  TWOFA_CHECK = '2faCheck',
  LOCKED = 'locked'
}

function decodeJWT(token: string): JwtPayload | null {
  const decoded = jwt_decode<JwtPayload>(token)
  if (!decoded || !decoded.exp) return null
  return decoded
}

const useAuthStore = defineStore({
  id: 'auth',
  state: (): AuthState => {
    const token = localStorage.getItem('__token__') || null
    const user = JSON.parse(localStorage.getItem('__user__') ?? 'null') as
      | (User & { profile: Profile })
      | null
    const now = new Date().getTime()
    return {
      token,
      user,
      error: {
        state: false,
        message: ''
      },
      isRefreshingToken: false,
      timer: null,
      now
    }
  },
  getters: {
    getTokenData(): JwtPayload | null {
      if (this.token) {
        return decodeJWT(this.token)
      }
      return null
    },
    isExpired(): boolean {
      if (this.token) {
        const decoded = decodeJWT(this.token)
        if (decoded) {
          const now = this.now
          return decoded.exp * 1000 <= now
        }
      }
      return false
    },
    closeToExpire(): boolean {
      if (this.token) {
        const decoded = decodeJWT(this.token)
        if (decoded) {
          const now = this.now
          return decoded.exp * 1000 <= now + 60 * 1000 // 1 minute before expiration
        }
      }
      return false
    },
    status(): LoginStatus {
      if (this.user) {
        if (this.token) {
          if (this.isExpired) {
            return LoginStatus.LOCKED
          }
          const decoded = this.getTokenData
          if (!decoded) {
            return LoginStatus.LOCKED
          }

          if (decoded.sub.needToPassTwoFactor) {
            return LoginStatus.TWOFA_CHECK
          } else {
            return LoginStatus.LOGGED
          }
        } else {
          return LoginStatus.LOCKED
        }
      }
      return LoginStatus.NOT_LOGGED
    },
    isLoggedIn(): boolean {
      return this.status === LoginStatus.LOGGED
    },
    is2FA(): boolean {
      return this.status === LoginStatus.TWOFA_CHECK
    },
    isLocked(): boolean {
      return this.status === LoginStatus.LOCKED
    },
    getUser(): (User & { profile: Profile }) | null {
      return this.user
    },
    getProfile(): Profile | null {
      return this.getUser?.profile ?? null
    },
    visibleStatus(): Status {
      return this.getProfile?.status ?? Status.Offline
    },
    getCoalition(): Coalition {
      // @ts-expect-error : resolveCoalition, an action
      return this.resolveCoalition(this.getProfile)
    },
    getError(): { state: boolean; message: string } {
      return this.error
    }
  },
  actions: {
    setUser(user: User & { profile: Profile }) {
      this.user = user
      localStorage.setItem('__user__', JSON.stringify(user))
    },
    setToken(token: string) {
      this.token = token
      localStorage.setItem('__token__', token)
      if (this.timer) {
        clearInterval(this.timer)
      }
      this.timer = setInterval(() => {
        this.now = new Date().getTime()
      }, 10000) // 10 seconds before token expiration check
    },
    async refreshToken(): Promise<string> {
      const { data } = await axios.get('/auth/refresh', {
        headers: {
          'Content-Type': 'application/json'
        }
      })
      const { accessToken } = data as { accessToken: string }
      this.setToken(accessToken)
      return accessToken
    },
    removeToken() {
      localStorage.removeItem('__token__')
      this.token = null
    },
    removeUser() {
      localStorage.removeItem('__user__')
      this.user = null
    },
    async storageUpdated() {
      // check if token is still present in local storage
      const token = localStorage.getItem('__token__')
      if (!token && this.isLoggedIn) {
        // token is not present, logout
        await this.logout()
      }
    },
    async login(credentials: { username: string; password: string }): Promise<boolean> {
      this.error = { state: false, message: '' }
      try {
        const { data } = await axios.post<ILoginData>('auth/login', credentials, {
          headers: {
            'Content-Type': 'application/json'
          }
        })
        const { accessToken, user } = data
        this.setUser(user)
        this.setToken(accessToken)
        return true
      } catch (error) {
        if (isAxiosError(error)) {
          if (error.response && (error.response.status === 403 || error.response.status === 401)) {
            this.error = { state: true, message: error.response.data.message }
          }
        }
      }
      return false
    },
    async logout() {
      this.error = { state: false, message: '' }
      try {
        this.removeUser()
        this.removeToken()
        await axios.get('auth/logout')
      } catch (error) {
        if (isAxiosError(error)) {
          this.error = {
            state: true,
            message: error.response?.data.message ?? 'Echec de déconnexion'
          }
        }
      }
    },
    async register(userInfos: RegisterBody): Promise<boolean> {
      this.error = { state: false, message: '' }
      if (!userInfos || userInfos.password !== userInfos.passwordConfirmation) return false
      const body = {
        username: userInfos.username,
        email: userInfos.email,
        password: userInfos.password,
        firstName: userInfos.firstName,
        lastName: userInfos.lastName
      }
      try {
        const { data } = await axios.post('auth/signup', body, {
          headers: {
            'Content-Type': 'application/json'
          }
        })
        const { accessToken, user } = data as ILoginData
        this.setUser(user)
        this.setToken(accessToken)
        return true
      } catch (error) {
        if (isAxiosError(error)) {
          if (error.response && error.response.status === 403) {
            this.error = { state: true, message: error.response.data.message }
          }
        }
      }
      return false
    },
    async refreshCurrentUser() {
      this.error = { state: false, message: '' }
      try {
        const { data } = await axios.get<User & { profile: Profile }>('auth/me', {
          headers: {
            Authorization: `Bearer ${this.token}`
          }
        })
        this.setUser(data)
      } catch (e) {
        this.error = { state: false, message: 'Failed to refresh user data' }
      }
    },
    async generate2FAQrCode(): Promise<string | null> {
      this.error = { state: false, message: '' }
      try {
        const { data } = await axios.post('auth/2fa/generate')
        return data as string
      } catch (error) {
        this.error = { state: true, message: `Can't generate 2FA code` }
        return null
      }
    },
    /**
     * @name activate2FA
     * @param otpCode
     * @description Activate 2FA with the OTP code
     * @returns
     */
    async activate2FA(otpCode: string): Promise<boolean> {
      this.error = { state: false, message: '' }
      try {
        if (!this.user?.twoFactorEnabled) {
          await axios.post('auth/2fa/turn-on', {
            twoFactorAuthenticationCode: otpCode
          })
          await this.refreshCurrentUser()
        }
        return true
      } catch (error) {
        this.error = { state: true, message: `Can't validate OTP code` }
        return false
      }
    },

    /**
     * @name validate2FACode
     * @param totpCode
     * @description Validate 2FA code
     * @returns
     */
    async validate2FACode(totpCode: string): Promise<boolean> {
      this.error = { state: false, message: '' }
      try {
        const { data } = await axios.post('auth/2fa/authenticate', {
          twoFactorAuthenticationCode: totpCode
        })
        return data as boolean
      } catch (error) {
        this.error = { state: true, message: `Can't validate OTP code` }
        return false
      }
    },

    /**
     * @name deactivate2FA
     * @description Deactivate 2FA
     * @returns
     */
    async deactivate2FA(): Promise<boolean> {
      this.error = { state: false, message: '' }
      try {
        await axios.post('auth/2fa/turn-off')
        await this.refreshCurrentUser()
        return true
      } catch (error) {
        this.error = { state: true, message: `Can't deactivate 2FA` }
        return false
      }
    },

    /**
     * @name updatePassword
     * @param info
     * @description Update password
     * @returns
     */
    async updatePassword(info: {
      currentPassword: string
      newPassword: string
      confirmPassword: string
    }): Promise<boolean> {
      this.error = { state: false, message: '' }
      try {
        const { data } = await axios.post('auth/updatePassword', info)
        this.setUser(data)
        return true
      } catch (error) {
        if (isAxiosError(error)) {
          if (error.response && (error.response.status === 403 || error.response.status === 401)) {
            const message = JSON.stringify(error.response.data.message ?? 'error')
            this.error = { state: true, message }
          }
        } else {
          this.error = { state: true, message: `Can't update password` }
        }
        return false
      }
    },
    /**
     * @name updateUsername
     * @param username
     * @description Update username
     * @returns
     */
    async updateUsername(username: string) {
      this.error = { state: false, message: '' }
      try {
        const { data } = await axios.post<User & { profile: Profile }>('users/username/' + username)
        if (this.user) {
          this.setUser({ ...this.user, username: data.username })
        } else {
          this.setUser(data)
        }
        return true
      } catch (error) {
        if (isAxiosError(error)) {
          if (error.response && (error.response.status === 403 || error.response.status === 401)) {
            this.error = { state: true, message: error.response.data.message }
          }
        } else {
          this.error = { state: true, message: `Can't update username` }
        }
        return false
      }
    },

    /**
     * @name updateUserInfo
     * @param info
     * @description Update user info
     * @returns
     */
    async updateUserInfo(info: { firstName: string; lastName: string; bio: string }) {
      this.error = { state: false, message: '' }
      try {
        const { data } = await axios.post('auth/updateInfo', info)
        this.setUser(data)
        return true
      } catch (error) {
        if (isAxiosError(error)) {
          if (
            error.response &&
            (error.response.status === 400 ||
              error.response.status === 403 ||
              error.response.status === 401)
          ) {
            this.error = { state: true, message: error.response.data.message }
          }
        } else {
          this.error = { state: true, message: `Can't update user info` }
        }
        return false
      }
    },

    /**
     * @name changeMyStatus
     * @param value
     * @description Change user status
     * @returns
     */
    // eslint-disable-next-line @typescript-eslint/no-unused-vars
    async changeMyStatus(value: Status): Promise<'success' | 'error'> {
      try {
        return 'success'
      } catch (e) {
        return 'error'
      }
    },

    /**
     * @name updateAvatar
     * @param avatar
     * @description Update avatar
     * @returns
     */
    async updateAvatar(avatar: File): Promise<'success' | 'error'> {
      try {
        const formData = new FormData()
        formData.append('file', avatar)
        const { data } = await axios.post<Profile>('/files/avatar', formData, {
          headers: {
            'Content-Type': 'multipart/form-data'
          }
        })
        if (this.user) {
          this.user.profile = data
        }
        return 'success'
      } catch (e) {
        return 'error'
      }
    },

    /**
     * @name resolveAvatarBadgeVariant
     * @param status
     * @description Resolve avatar badge variant
     * @returns
     */
    resolveAvatarBadgeVariant(status: Status): 'success' | 'error' | 'warning' | 'secondary' {
      if (status === Status.Online) return 'success'
      else if (status === Status.Offline) return 'error'
      else if (status === Status.Busy) return 'warning'
      return 'secondary'
    },
    resolveCoalition(profile: Profile): Coalition {
      if (profile.oauth && profile.oauth?.coalitions) {
        if (profile.oauth.coalitions.length) {
          return profile.oauth.coalitions[0]
        }
      }
      return {
        color: '#cc0000',
        cover_url:
          'https://cdn.intra.42.fr/coalition/cover/243/42Q_035_22_BG_Coalitions_Legion_3000x2000.jpg',
        id: 243,
        image_url: 'https://cdn.intra.42.fr/coalition/image/243/42Q_035_22_Logo_Legion.svg',
        name: 'Les pongistes',
        score: 0,
        slug: 'Pongiste',
        user_id: 0
      }
    }
  }
})

export default useAuthStore
