<template>
  <VCard
    color="transparent"
    :loading="isLoading"
  >
    <VCardText>
      <h5 class="text-h5 text-center font-semibold mb-4">
        Verification à double facteur
      </h5>
      <p class="text-center font-light">
        Veuillez entrer le code de vérification inscrit dans votre application d'authentification.
      </p>
    </VCardText>
    <VCardText>
      <VForm @submit.prevent="validateCode">
        <VCol>
          <VOtpInput v-model="verificationCode" />
          <p
            v-if="errorMessage"
            class="text-error text-center font-lighter"
          >
            {{ errorMessage }}
          </p>
        </VCol>
        <VCol cols="12">
          <VBtn
            block
            type="submit"
          >
            Valider
          </VBtn>
        </VCol>
      </VForm>
      <VBtn
        variant="text"
        color="secondary"
        @click="logout"
      >
        Déconnexion
      </VBtn>
    </VCardText>
  </VCard>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore from '@/stores/AuthStore'

export default defineComponent({
  name: 'TwoFactors',
  setup() {
    const authStore = useAuthStore()
    return { authStore }
  },
  data() {
    return {
      verificationCode: '',
      errorMessage: '',
      isLoading: false
    }
  },
  beforeMount() {},
  methods: {
    async validateCode() {
      this.isLoading = true
      const worked = await this.authStore.validate2FACode(this.verificationCode)
      if (worked) {
        this.authStore.refreshToken()
        this.$router.push({ name: 'dashboard' })
      } else {
        this.errorMessage = 'Le code est invalide'
      }
      this.isLoading = false
    },
    async logout() {
      this.isLoading = true
      await this.authStore.logout()
      this.isLoading = false
      this.$router.push({ name: 'auth' })
    }
  }
})
</script>

<style></style>
