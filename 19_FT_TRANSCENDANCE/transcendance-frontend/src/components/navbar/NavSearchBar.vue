<template>
  <div
    class="flex align-center cursor-pointer"
    v-bind="$attrs"
    @click="isAppSearchBarVisible = !isAppSearchBarVisible"
  >
    <VBtn
      icon
      variant="text"
      size="small"
    >
      <VIcon
        icon="tabler-search"
        size="24"
      />
    </VBtn>
    <span class="d-none d-md-flex align-center text-disabled">
      <span class="m-2">Recherche</span>
      <span class="text-orange-100 text-sm">&#8984;K</span>
    </span>
  </div>
  <VuetifyAppSearchBar
    v-model:search-query="searchQuery"
    v-model:isDialogVisible="isAppSearchBarVisible"
    :search-results="searchBarStore.getSearchResults"
    :suggestions="searchBarStore.getSuggestionGroups"
    :no-data-suggestion="searchBarStore.getNoDataSuggestions"
    @item-selected="redirectToSuggestedOrSearchedPage"
  />
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useSearchBarStore, { SearchItem } from '@/stores/SearchBarStore'
import VuetifyAppSearchBar from '@/vuetify/@core/components/AppBarSearch.vue'

export default defineComponent({
  name: 'NavSearchBar',
  components: {
    VuetifyAppSearchBar
  },
  setup() {
    const searchBarStore = useSearchBarStore()
    return {
      searchBarStore
    }
  },
  data() {
    return {
      searchQuery: '',
      isAppSearchBarVisible: false
    }
  },
  watch: {
    searchQuery(newValue, oldValue) {
      if (newValue.length > 0 && newValue !== oldValue) {
        this.startSearch()
      }
    }
  },
  methods: {
    redirectToSuggestedOrSearchedPage(selected: SearchItem) {
      if (selected.url) {
        this.$router.push(selected.url)
        this.isAppSearchBarVisible = false
      }
    },
    startSearch() {
      this.searchBarStore.search(this.searchQuery)
    }
  }
})
</script>

<style scoped lang="scss"></style>
