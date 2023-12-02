import { defineStore } from 'pinia'
import axios from '@/utils/axios'
import { User } from '@/interfaces/User'
import { RouteLocationRaw } from 'vue-router'

export interface Suggestion {
  icon: string
  title: string
  url: RouteLocationRaw
}

interface SuggestionGroupContent extends Suggestion {
  category: string
}

export interface SuggestionGroup {
  title: string
  content: Suggestion[]
}

export type SearchItem = {
  id: number | string
  url: RouteLocationRaw
  icon: string
  title: string
  category: string
}

export type SearchHeader = {
  header: string
  title: string
}

export interface SearchBarState {
  suggestions: SuggestionGroupContent[]
  noDataSuggestions: Suggestion[]
  searchResults: Array<SearchItem | SearchHeader>
  loading: boolean
}

const useSearchBarStore = defineStore({
  id: 'searchBar',
  state: (): SearchBarState => ({
    suggestions: [
      {
        icon: 'tabler-chart-donut',
        title: "Tableau de bord d'analyse",
        url: { name: 'dashboard' },
        category: 'Recherches populaires'
      },
      {
        icon: 'tabler-users',
        title: "Liste d'utilisateur",
        url: { name: 'user-list' },
        category: 'Recherches populaires'
      },
      {
        icon: 'tabler-mail',
        title: 'messages Privé',
        url: { name: 'dm' },
        category: 'Recherches populaires'
      },
      {
        icon: 'noto-v1:game-die',
        title: 'Jeur contre le bot',
        url: { name: 'bot-game' },
        category: 'Jeu'
      },
      {
        icon: 'medical-icon:i-waiting-area',
        title: 'Rejoindre une file pour jouer',
        url: { name: 'waiting-room' },
        category: 'Jeu'
      },
      {
        icon: 'solar:ranking-linear',
        title: 'Leader Board',
        url: { name: 'leaderboard' },
        category: 'Jeu'
      },
      {
        icon: 'tabler-settings',
        title: 'Paramètres du compte',
        url: { name: 'settings', params: { tab: 'account' } },
        category: 'Profile'
      },
      {
        icon: 'tabler-calendar',
        title: 'Historique',
        url: { name: 'me', params: { tab: 'history' } },
        category: 'Profile'
      },
      {
        icon: 'bxs:contact',
        title: 'Mes Contacts',
        url: { name: 'me', params: { tab: 'friends' } },
        category: 'Profile'
      },
      {
        icon: 'tabler-lock',
        title: 'Sécurité',
        url: { name: 'settings', params: { tab: 'security' } },
        category: 'Profile'
      }
    ],
    noDataSuggestions: [
      {
        title: 'Tableau de bord',
        icon: 'tabler-chart-donut',
        url: { name: 'dashboard' }
      },
      {
        title: 'Paramètres du compte',
        icon: 'tabler-user',
        url: { name: 'settings', params: { tab: 'account' } }
      }
    ],
    searchResults: [],
    loading: false
  }),
  getters: {
    getSuggestionGroups(): SuggestionGroup[] {
      return this.suggestions.reduce(
        (acc: SuggestionGroup[], suggestion: SuggestionGroupContent) => {
          const group = acc.find((group) => group.title === suggestion.category)
          if (group) {
            group.content.push(suggestion)
          } else {
            acc.push({
              title: suggestion.category,
              content: [suggestion]
            })
          }
          return acc
        },
        []
      )
    },
    getNoDataSuggestions(): Suggestion[] {
      return this.noDataSuggestions
    },
    getSearchResults(): Array<SearchItem | SearchHeader> {
      return this.searchResults
    },
    isLoading(): boolean {
      return this.loading
    }
  },
  actions: {
    async search(query: string) {
      this.loading = true
      if (query.length > 0) {
        const results = await Promise.all([
          this.searchForUser(query),
          this.searchInPagesSuggestions(query)
        ])
        this.searchResults = results.flat()
      } else {
        this.searchResults = []
      }
      this.loading = false
    },
    async searchForUser(searchTerm: string): Promise<Array<SearchItem | SearchHeader>> {
      try {
        const { data } = await axios.get<User[]>('users/search', {
          params: {
            query: searchTerm
          }
        })
        const header = { header: 'users', title: 'Utilisateurs' }
        const users = data.map(
          (user) =>
            ({
              id: user.id,
              url: { name: 'user-profile', params: { userId: user.id } },
              icon: 'tabler-user',
              avatar: user.profile?.avatar ?? '',
              title: `${user.profile?.name} ${user.profile?.lastname} - @${user.username}`,
              category: header.title
            }) as SearchItem
        )
        return [header, ...users]
      } catch (error) {
        // console.error(error)
      }
      return []
    },
    async searchInPagesSuggestions(searchTerm: string): Promise<Array<SearchItem | SearchHeader>> {
      const suggestionsMatched: SuggestionGroupContent[] = this.suggestions.filter(
        (suggestion: SuggestionGroupContent) =>
          suggestion.title.toLowerCase().includes(searchTerm.toLowerCase())
      )
      return suggestionsMatched.reduce(
        (acc: Array<SearchItem | SearchHeader>, suggestion: SuggestionGroupContent) => {
          const header = acc.find((item) => item.title === suggestion.category)
          if (!header) {
            acc.push({
              header: suggestion.category,
              title: suggestion.category
            })
          }
          acc.push({
            id: suggestion.title,
            url: suggestion.url,
            icon: suggestion.icon,
            title: suggestion.title,
            category: suggestion.category
          })
          return acc
        },
        []
      )
    }
  }
})

export default useSearchBarStore
