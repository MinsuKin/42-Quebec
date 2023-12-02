export enum Status {
  Online = 'Online',
  Offline = 'Offline',
  Away = 'Away',
  Busy = 'Busy'
}

export enum Role {
  BAN = 'BAN',
  MUTED = 'MUTED',
  USER = 'USER',
  OWNER = 'OWNER',
  ADMIN = 'ADMIN',
  SUPER_MODERATOR = 'SUPER_MODERATOR'
}

export enum GameEvent {
  GAME_STARTED = 'GAME_STARTED',
  GAME_ENDED = 'GAME_ENDED',
  PLAYER_JOINED = 'PLAYER_JOINED',
  PLAYER_LEFT = 'PLAYER_LEFT',
  ACTION_PERFORMED = 'ACTION_PERFORMED',
  IA_ACTION_PERFORMED = 'IA_ACTION_PERFORMED',
  MATCH_WON = 'MATCH_WON',
  MATCH_LOST = 'MATCH_LOST'
}

export interface Coalition {
  id: number
  name: string
  slug: string
  cover_url: string
  image_url: string
  color: string
  score: number
  user_id: number
}

export interface Profile {
  id: number
  userId: number
  name: string
  lastname: string
  avatar: string
  bio?: string
  oauth?: {
    accessToken: string
    refreshToken: string
    coalitions: Coalition[]
  }
  status: Status
}

export interface GameHistory {
  id: number
  gameId: number
  event: GameEvent
  userId: number
  timestamp: string
}

export interface User {
  id: number
  username: string
  email: string
  role: Role
  profile?: Profile
  sessions: [] //Session[]
  games: [] //Game[]
  groups: [] //             Group[]
  twoFactorEnabled: boolean
  gameHistories?: GameHistory[]
  createdAt: string
  updatedAt: string
}
export interface ProfileHeaderData {
  coalition?: Coalition
  avatar: string
  fullName: string
  username: string
  joiningDate: string
  isCurrentUser: boolean
  status: Status
}
export interface ProfileData {
  id: number
  header: ProfileHeaderData
  profile: Profile
  email: string
}
export interface AuthState {
  token: string | null
  user: (User & { profile: Profile }) | null
  error: {
    state: boolean
    message: string
  }
  isRefreshingToken: boolean
  timer: NodeJS.Timeout | null
  now: number
}
export interface RegisterBody {
  lastName: string
  firstName: string
  email: string
  password: string
  username: string
  passwordConfirmation: string
}

export interface ILoginData {
  accessToken: string
  user: User & { profile: Profile }
}
