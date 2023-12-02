<template>
  <VRow>
    <VCol
      v-if="!isExternalAuth"
      cols="12"
    >
      <VCard title="Modifier le mot de passe">
        <VForm @submit.prevent="changePassword">
          <VCardText class="pt-0">
            <VRow class="mb-3">
              <VCol
                cols="12"
                md="6"
              >
                <VTextField
                  v-model="passwordFields.currentPassword"
                  class="transparent-input-box"
                  :rules="[rules.required, rules.min]"
                  :type="passwordFieldsVisibility.currentPassword ? 'text' : 'password'"
                  :append-inner-icon="
                    passwordFieldsVisibility.currentPassword ? 'tabler-eye-off' : 'tabler-eye'
                  "
                  label="Mot de passe actuel"
                  @click:append-inner="
                    passwordFieldsVisibility.currentPassword =
                      !passwordFieldsVisibility.currentPassword
                  "
                />
              </VCol>
            </VRow>
            <VRow>
              <VCol
                cols="12"
                md="6"
              >
                <VTextField
                  v-model="passwordFields.newPassword"
                  class="transparent-input-box"
                  :rules="[rules.required, rules.min, rules.upperCase]"
                  :type="passwordFieldsVisibility.newPassword ? 'text' : 'password'"
                  :append-inner-icon="
                    passwordFieldsVisibility.newPassword ? 'tabler-eye-off' : 'tabler-eye'
                  "
                  label="Nouveau mot de passe"
                  @click:append-inner="
                    passwordFieldsVisibility.newPassword = !passwordFieldsVisibility.newPassword
                  "
                />
              </VCol>
              <VCol
                cols="12"
                md="6"
              >
                <VTextField
                  v-model="passwordFields.confirmPassword"
                  class="transparent-input-box"
                  :rules="[rules.required, rules.min, rules.upperCase, rules.match]"
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
            </VRow>
          </VCardText>
          <VCardText class="flex flex-wrap gap-4">
            <VBtn @click="changePassword">
              Modifier
            </VBtn>
          </VCardText>
        </VForm>
      </VCard>
    </VCol>

    <VCol cols="12">
      <VCard title="Double facteur">
        <VCardText v-if="!isDoubleFactorEnabled">
          <h6 class="text-base font-weight-semibold mb-3">
            L'authentification à deux facteurs n'est pas encore activée.
          </h6>
          <p class="text-sm">
            L'authentification à deux facteurs ajoute une couche de sécurité supplémentaire à votre
            compte en nécessitant plus qu'un simple mot de passe pour se connecter. Nous vous
            recommandons fortement d'activer cette option.
          </p>

          <VBtn
            class="mt-1"
            @click="isDoubleFactorDialogVisible = true"
          >
            Activez
          </VBtn>
        </VCardText>
        <VCardText v-else>
          <VAlert
            color="warning"
            variant="tonal"
            class="mb-4"
          >
            <VAlertTitle class="mb-1 text-sm">
              Double facteur<span class="text-white pl-1"> activé</span>, etes-vous sur de vouloir
              le désactiver ?
            </VAlertTitle>
          </VAlert>
          <div>
            <v-checkboxBtn
              v-model="allowTwoFactorDisable"
              color="primary"
              true-icon="tabler-check"
              false-icon="tabler-x"
              label="Je confirme la désactivation du double facteur"
            />
          </div>
          <VBtn
            :disabled="!allowTwoFactorDisable"
            color="error"
            class="mt-3"
            @click="deactivateTwoFactor"
          >
            Désactiver
          </VBtn>
        </VCardText>
      </VCard>
    </VCol>

    <VCol cols="12">
      <VCard
        title="Sessions récentes"
        :loading="loadingSessions"
      >
        <VDivider />
        <VTable class="bg-transparent">
          <thead>
            <tr>
              <th scope="col">
                Navigateur
              </th>
              <th scope="col">
                Terminal
              </th>
              <th scope="col">
                Location/IP
              </th>
              <th scope="col">
                Créer le
              </th>
              <th scope="col">
                Etat
              </th>
            </tr>
          </thead>
          <tbody>
            <tr
              v-for="session in lastSessions"
              :key="session.id"
            >
              <td class="flex align-center">
                <template
                  v-for="iconObj in icons"
                  :key="iconObj.title"
                >
                  <VIcon
                    v-if="getPlatform(session.userAgent) === iconObj.title"
                    :icon="iconObj.icon"
                    :color="iconObj.color"
                  />
                </template>
                <span>{{ getNavigatorName(session.userAgent) }} -
                  {{ getPlatform(session.userAgent) }}</span>
              </td>
              <td class="text-base font-weight-semibold">
                {{ getDeviceName(session.userAgent) }}
              </td>
              <td>{{ session.ipAddress }}</td>
              <td>{{ formatDate(session.createdAt) }}</td>
              <td>
                <v-chip
                  class="ma-2"
                  label
                  :color="
                    checkSessionExpiryStatus(session.expiresAt) === 'active' ? 'success' : 'error'
                  "
                >
                  {{ checkSessionExpiryStatus(session.expiresAt) }} | exp:
                  {{ formatDate(session.expiresAt) }}
                </v-chip>
              </td>
            </tr>
          </tbody>
        </VTable>
      </VCard>
    </VCol>
  </VRow>
  <DoubleFactorModal v-model:is-dialog-visible="isDoubleFactorDialogVisible" />
  <VSnackbar
    v-model="isInfoBarVisible"
    multi-line
    :timeout="2000"
    :color="infoColor"
  >
    {{ infoMsg }}
  </VSnackbar>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import axiosInstance from '@/utils/axios'
import useAuthStore from '@/stores/AuthStore'
import DoubleFactorModal from '@/components/profile/DoubleFactorModal.vue'

interface Session {
  id: number
  userAgent: string
  ipAddress: string
  createdAt: string
  expiresAt: string
}
export default defineComponent({
  name: 'SecuritySettings',
  components: {
    DoubleFactorModal
  },
  setup() {
    const authStore = useAuthStore()
    return {
      authStore
    }
  },
  data() {
    return {
      lastSessions: [] as Session[],
      loadingSessions: false,
      icons: [
        { icon: 'tabler-brand-windows', color: 'blue', title: 'Windows' },
        { icon: 'tabler-brand-apple', color: 'secondary', title: 'MacOS' },
        { icon: 'tabler-brand-android', color: 'green', title: 'Android' },
        { icon: 'tabler-brand-apple', color: 'secondary', title: 'IPhone' }
      ],
      isDoubleFactorDialogVisible: false,
      isInfoBarVisible: false,
      infoMsg: '',
      infoColor: 'success',
      passwordFieldsVisibility: {
        currentPassword: false,
        newPassword: false,
        confirmPassword: false
      },
      passwordFields: {
        currentPassword: '',
        newPassword: '',
        confirmPassword: ''
      },
      rules: {
        required: (value: number) => !!value || 'Ce champ est requis',
        min: (v: string) => v.length >= 6 || 'Minimum 6 caractères',
        match: () => {
          return (
            this.passwordFields.newPassword === this.passwordFields.confirmPassword ||
            'Les mots de passe ne correspondent pas'
          )
        },
        upperCase: (v: string) => /[A-Z]/.test(v) || 'Doit contenir au moins une lettre majuscule'
      },
      allowTwoFactorDisable: false
    }
  },
  computed: {
    isDoubleFactorEnabled() {
      const user = this.authStore.getUser
      if (!user) return false
      return user.twoFactorEnabled ?? false
    },
    isExternalAuth(): boolean {
      // check if user have api42 or google auth
      return (
        this.authStore.getUser?.api42Id ||
        this.authStore.getUser?.googleId ||
        this.authStore.getUser?.facebookId
      )
    }
  },
  mounted() {
    this.getSessions()
  },
  methods: {
    async getSessions() {
      this.loadingSessions = true
      try {
        const data = (await axiosInstance.get('/auth/sessions')).data
        this.lastSessions = data
      } catch (e) {
        console.log(e)
      }
      this.loadingSessions = false
    },
    async disconnectSession(session: Session) {
      console.info('try disconnecting session', session)
    },
    async changePassword() {
      const worked = await this.authStore.updatePassword(this.passwordFields)
      if (worked) {
        this.infoMsg = 'Votre mot de passe a été mis à jour avec succès'
        this.infoColor = 'success'
        this.isInfoBarVisible = true
        this.passwordFields = {
          currentPassword: '',
          newPassword: '',
          confirmPassword: ''
        }
      } else {
        this.infoMsg = this.authStore.getError.message
        this.infoColor = 'error'
        this.isInfoBarVisible = true
      }
    },
    async deactivateTwoFactor() {
      const worked = await this.authStore.deactivate2FA()
      if (worked) {
        this.infoMsg = `L'authentification à deux facteurs a été désactivée avec succès`
        this.infoColor = 'success'
        this.isInfoBarVisible = true
        this.allowTwoFactorDisable = false
      } else {
        this.infoMsg = `Une erreur est survenue lors de la désactivation de l'authentification à deux facteurs`
        this.infoColor = 'error'
        this.isInfoBarVisible = true
      }
    },
    getPlatform(userAgent: string) {
      if (userAgent.includes('Windows')) {
        return 'Windows'
      } else if (userAgent.includes('Mac OS X') || userAgent.includes('Macintosh')) {
        return 'MacOS'
      } else if (userAgent.includes('Android')) {
        return 'Android'
      } else if (userAgent.includes('iPhone')) {
        return 'IPhone'
      } else {
        return 'Unknown'
      }
    },
    getNavigatorName(userAgent: string) {
      if (userAgent.includes('Edge')) {
        return 'Edge'
      } else if (userAgent.includes('Opera') || userAgent.includes('OPR')) {
        return 'Opera'
      } else if (userAgent.includes('Chrome')) {
        return 'Chrome'
      } else if (userAgent.includes('Safari') && !userAgent.includes('Chrome')) {
        return 'Safari'
      } else if (userAgent.includes('Firefox')) {
        return 'Firefox'
      } else if (userAgent.includes('MSIE') || userAgent.includes('Trident/7.0')) {
        return 'Internet Explorer'
      } else {
        return 'Unknown'
      }
    },
    getDeviceName(userAgent: string) {
      if (userAgent.includes('Android')) {
        return 'Android'
      } else if (userAgent.includes('iPad')) {
        return 'iPad'
      } else if (userAgent.includes('iPhone')) {
        return 'iPhone'
      } else if (userAgent.includes('Mac OS X') || userAgent.includes('Macintosh')) {
        return 'Mac'
      } else if (userAgent.includes('Windows')) {
        return 'Windows'
      } else if (userAgent.includes('Linux')) {
        return 'Linux'
      } else {
        return 'Unknown'
      }
    },
    formatDate(dateStr: string): string {
      const date = new Date(dateStr)
      return new Intl.DateTimeFormat('fr-CA', {
        weekday: 'long',
        year: 'numeric',
        month: 'long',
        day: 'numeric'
      }).format(date)
    },
    checkSessionExpiryStatus(expiryDateStr: string) {
      const expiryDate = new Date(expiryDateStr)
      return expiryDate.getTime() > Date.now() ? 'active' : 'expired'
    }
  }
})
</script>

<style scoped></style>
