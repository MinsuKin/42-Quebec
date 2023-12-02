<template>
  <VCard
    color="transparent"
    :loading="isLoading"
  >
    <v-tabs
      v-model="activeTab"
      color="red"
      fixed-tabs
      align-tabs="end"
      class="w-full"
    >
      <VTab
        v-for="item in tabs"
        :key="item.tab"
        :value="item.tab"
      >
        <VIcon
          v-if="item.tab === activeTab"
          size="24"
          start
          :icon="item.icon"
        />
        <template v-if="item.tab !== activeTab">
          {{ item.callToAction }}
        </template>
      </VTab>
    </v-tabs>
    <VDivider />
    <VWindow v-model="activeTab">
      <VWindowItem
        :value="tabs[0].tab"
        class="px-4 pt-12"
      >
        <VCardText>
          <h4 class="mb-4 text-2xl font-semibold text-center">
            Connexion
          </h4>
        </VCardText>
        <VForm @submit.prevent="login">
          <VRow>
            <VCol cols="12">
              <VTextField
                v-model="loginFields.username"
                class="transparent-input-box"
                label="Pseudo"
                type="text"
                :rules="[rules.required, rules.min]"
              />
            </VCol>
            <VCol cols="12">
              <VTextField
                v-model="loginFields.password"
                class="transparent-input-box"
                label="Mot de passe"
                :rules="[rules.required]"
                :type="passwordFieldsVisibility.password ? 'text' : 'password'"
                :append-inner-icon="
                  passwordFieldsVisibility.password ? 'tabler-eye-off' : 'tabler-eye'
                "
                @click:append-inner="
                  passwordFieldsVisibility.password = !passwordFieldsVisibility.password
                "
              />
              <VAlert
                v-if="authStore.getError.state"
                variant="tonal"
                color="error"
                class="mt-4"
              >
                {{ authStore.getError.message }}
              </VAlert>
              <VBtn
                type="submit"
                block
                class="mt-4 mb-8"
              >
                Se Connecter
              </VBtn>
            </VCol>
            <VCol
              cols="12"
              class="flex align-center"
            >
              <VDivider />
              <span class="mx-4 font-medium text-gray-400 rounded-md">Avec</span>
              <VDivider />
            </VCol>
            <VCol
              cols="12"
              class="text-center"
            >
              <div class="flex-wrap justify-center gap-3 d-flex">
                <VBtn
                  class=""
                  variant="tonal"
                  color="cyan"
                  rounded
                  size="large"
                  href="/api/auth/42"
                >
                  <VIcon
                    icon="simple-icons:42"
                    class="mr-1"
                  />
                  Best school
                </VBtn>
                <VBtn
                  variant="outlined"
                  color="#dd4b39"
                  rounded
                  size="large"
                  href="/api/auth/google"
                >
                  <VIcon
                    icon="flat-color-icons:google"
                    class="mr-1"
                  />
                  Google
                </VBtn>
              </div>
            </VCol>
          </VRow>
        </VForm>
      </VWindowItem>
      <VWindowItem
        :value="tabs[1].tab"
        class="px-4 pt-12"
      >
        <VCardText>
          <h4 class="mb-4 text-2xl font-semibold text-center">
            Création de compte
          </h4>
        </VCardText>
        <VForm
          v-model="validSignUpForm"
          @submit.prevent="signUp"
        >
          <VRow>
            <VCol
              cols="12"
              md="6"
            >
              <VTextField
                v-model="signUpFields.firstName"
                :rules="[rules.required, rules.min]"
                label="Prenom"
              />
            </VCol>
            <VCol
              cols="12"
              md="6"
            >
              <VTextField
                v-model="signUpFields.lastName"
                :rules="[rules.required, rules.min]"
                label="Nom de famille"
              />
            </VCol>

            <VCol cols="12">
              <VTextField
                v-model="signUpFields.username"
                :rules="[rules.required, rules.min]"
                label="Pseudo"
              />
            </VCol>
            <VCol cols="12">
              <v-text-field
                v-model="signUpFields.email"
                :rules="[rules.required, rules.email]"
                label="Email"
              />
            </VCol>
            <VCol cols="12">
              <VTextField
                v-model="signUpFields.password"
                :rules="[rules.required, rules.minPass, rules.upperCase]"
                :type="passwordFieldsVisibility.newPassword ? 'text' : 'password'"
                :append-inner-icon="
                  passwordFieldsVisibility.newPassword ? 'tabler-eye-off' : 'tabler-eye'
                "
                label="Mot de passe"
                @click:append-inner="
                  passwordFieldsVisibility.newPassword = !passwordFieldsVisibility.newPassword
                "
              />
            </VCol>
            <VCol cols="12">
              <VTextField
                v-model="signUpFields.passwordConfirmation"
                :rules="[rules.required, rules.minPass, rules.upperCase, rules.match]"
                :type="passwordFieldsVisibility.confirmPassword ? 'text' : 'password'"
                :append-inner-icon="
                  passwordFieldsVisibility.confirmPassword ? 'tabler-eye-off' : 'tabler-eye'
                "
                label="Confirmer le mot de passe"
                @click:append-inner="
                  passwordFieldsVisibility.confirmPassword =
                    !passwordFieldsVisibility.confirmPassword
                "
              />
            </VCol>
            <VCol cols="12">
              <VAlert
                v-if="authStore.getError.state"
                variant="tonal"
                color="error"
                class="mt-4"
              >
                {{ authStore.getError.message }}
              </VAlert>
              <VBtn
                type="submit"
                block
                class="mt-4 mb-8"
                :disabled="!validSignUpForm"
              >
                Créer le compte <VIcon icon="tabler-edit" />
              </VBtn>
            </VCol>
          </VRow>
        </VForm>
      </VWindowItem>
    </VWindow>
  </VCard>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import useAuthStore, { LoginStatus } from '@/stores/AuthStore'

type Tab = 'connect' | 'register'
const tabList: Array<{ title: string; callToAction: string; icon: string; tab: Tab }> = [
  { title: 'Connexion', callToAction: `Vous connectez`, icon: 'tabler-lock', tab: 'connect' },
  {
    title: 'Création de compte',
    callToAction: `Créer un compte`,
    icon: 'fluent:form-new-48-regular',
    tab: 'register'
  }
]

export default defineComponent({
  name: 'AuthView',
  components: {},
  setup() {
    const authStore = useAuthStore()
    return { authStore }
  },
  data() {
    return {
      isLoading: false,
      tabs: tabList,
      activeTab: tabList[0].tab,
      loginFields: {
        username: '',
        password: ''
      },
      signUpFields: {
        lastName: '',
        firstName: '',
        email: '',
        password: '',
        username: '',
        passwordConfirmation: ''
      },
      passwordFieldsVisibility: {
        password: false,
        newPassword: false,
        confirmPassword: false
      },
      validSignUpForm: false,
      rules: {
        email: (value: string) => {
          const pattern = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/
          return pattern.test(value) || 'Adresse email invalide'
        },
        required: (v: string) => !!v || 'Ce champ est requis',
        minPass: (v: string) => v.length >= 6 || 'Minimum 6 caractères',
        min: (v: string) => v.length >= 3 || 'Minimum 3 caractères',
        match: () => {
          return (
            this.signUpFields.password === this.signUpFields.passwordConfirmation ||
            'Les mots de passe ne correspondent pas'
          )
        },
        upperCase: (v: string) => /[A-Z]/.test(v) || 'Doit contenir au moins une lettre majuscule'
      }
    }
  },
  mounted() {
    this.moveToCorrectRoute()
  },
  methods: {
    async moveToCorrectRoute() {
      this.isLoading = true
      switch (this.authStore.status) {
        case LoginStatus.LOCKED:
          this.$router.push({ name: 'locked-screen' })
          break
        case LoginStatus.TWOFA_CHECK:
          this.$router.push({ name: 'two-factors' })
          break
        default:
        // nothing
      }
      this.isLoading = false
    },
    async login() {
      this.isLoading = true
      const worked = await this.authStore.login(this.loginFields)
      if (worked) {
        this.$router.push({ name: 'dashboard' })
      }
      this.isLoading = false
    },
    async signUp() {
      this.isLoading = true
      const worked = await this.authStore.register(this.signUpFields)
      if (worked) {
        this.$router.push({ name: 'dashboard' })
      }
      this.isLoading = false
      return
    }
  }
})
</script>

<style></style>
