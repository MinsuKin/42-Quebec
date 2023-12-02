<template>
  <div>
    <VTabs
      v-model="activeTab"
      class="v-tabs-pill"
    >
      <VTab
        v-for="item in tabs"
        :key="item.icon"
        :value="item.tab"
        :to="{ name: 'settings', params: { tab: item.tab } }"
      >
        <VIcon
          size="20"
          start
          :icon="item.icon"
        />
        {{ item.title }}
      </VTab>
    </VTabs>
    <VWindow
      v-model="activeTab"
      class="mt-6 disable-tab-transition"
      :touch="false"
    >
      <VWindowItem value="account">
        <VRow>
          <VCol cols="12">
            <VCard title="Information du profil">
              <VCardText class="flex">
                <VAvatar
                  rounded
                  size="100"
                  class="me-6"
                  :image="avatar"
                />
                <form
                  ref="refUpdateAvatarForm"
                  class="flex flex-column justify-center gap-4"
                  @submit.prevent
                >
                  <div class="flex flex-wrap gap-2">
                    <VBtn
                      color="primary"
                      @click="inputElement?.click()"
                    >
                      <VIcon
                        icon="tabler-cloud-upload"
                        class="d-sm-none"
                      />
                      <span class="d-none d-sm-block">Changer d'avatar</span>
                    </VBtn>

                    <input
                      ref="refInputEl"
                      type="file"
                      name="file"
                      accept=".jpeg,.png,.jpg,GIF"
                      hidden
                      @input="startUploadNewAvatar"
                    >
                  </div>
                  <p class="text-sm font-weight-light mb-0">
                    Fichier pris en charge: JPG, GIF or PNG
                  </p>
                </form>
              </VCardText>

              <VDivider />

              <VCardText class="pt-2">
                <VForm
                  class="mt-6"
                  @submit.prevent
                >
                  <VRow>
                    <VCol
                      md="6"
                      cols="12"
                    >
                      <VTextField
                        v-model="fields.username"
                        label="Username"
                        class="transparent-input-box"
                      />
                    </VCol>

                    <VCol
                      cols="12"
                      class="d-flex flex-wrap gap-4"
                    >
                      <VBtn @click.prevent="updateUsername">
                        Update
                      </VBtn>
                      <VBtn
                        color="secondary"
                        variant="tonal"
                        type="reset"
                        @click.prevent="resetForm"
                      >
                        Renitialiser
                      </VBtn>
                    </VCol>
                  </VRow>
                </VForm>
              </VCardText>

              <VCardText class="pt-2">
                <VForm
                  class="mt-6"
                  @submit.prevent
                >
                  <VRow>
                    <VCol
                      md="6"
                      cols="12"
                    >
                      <VTextField
                        v-model="fields.firstName"
                        label="Prénom"
                        class="transparent-input-box"
                      />
                    </VCol>

                    <VCol
                      md="6"
                      cols="12"
                    >
                      <VTextField
                        v-model="fields.lastName"
                        label="Nom de famille"
                        class="transparent-input-box"
                      />
                    </VCol>

                    <VCol
                      cols="12"
                      md="6"
                    >
                      <VTextarea
                        v-model="fields.bio"
                        label="Biographie"
                        class="transparent-input-box"
                      />
                    </VCol>

                    <VCol
                      cols="12"
                      class="d-flex flex-wrap gap-4"
                    >
                      <VBtn @click.prevent="updateUserInformation">
                        Enregistrer
                      </VBtn>
                      <VBtn
                        color="secondary"
                        variant="tonal"
                        type="reset"
                        @click.prevent="resetForm"
                      >
                        Renitialiser
                      </VBtn>
                    </VCol>
                  </VRow>
                </VForm>
              </VCardText>
            </VCard>
          </VCol>
        </VRow>
      </VWindowItem>
      <VWindowItem value="security">
        <SecuritySettings />
      </VWindowItem>
    </VWindow>
    <VSnackbar
      v-model="isInfoBarVisible"
      multi-line
      :timeout="1000"
      :color="infoColor"
    >
      {{ infoMsg }}
    </VSnackbar>
  </div>
</template>

<script lang="ts">
import { defineComponent, PropType } from 'vue'
import SecuritySettings from '@/views/User/SecuritySettings.vue'
import useAuthStore from '@/stores/AuthStore'

export default defineComponent({
  components: {
    SecuritySettings
  },
  props: {
    tab: {
      type: String as PropType<'account' | 'security'>,
      default: () => 'account'
    }
  },
  setup() {
    const authStore = useAuthStore()
    return { authStore }
  },
  data() {
    return {
      tabs: [
        { title: 'Compte', icon: 'tabler-users', tab: 'account' },
        { title: 'Paramètre de sécurité', icon: 'tabler-lock', tab: 'security' }
      ],
      isInfoBarVisible: false,
      infoMsg: '',
      infoColor: 'success',
      activeTab: this.tab,

      fields: {
        username: '',
        firstName: '',
        lastName: '',
        bio: ''
      }
    }
  },
  computed: {
    inputElement(): HTMLInputElement {
      return this.$refs.refInputEl
    },
    avatar(): string {
      return this.authStore.getProfile?.avatar ?? ''
    }
  },
  mounted() {
    this.hydrateFields()
  },
  methods: {
    hydrateFields() {
      this.fields = {
        username: this.authStore.getUser?.username || '',
        firstName: this.authStore.getProfile?.name || '',
        lastName: this.authStore.getProfile?.lastname || '',
        bio: this.authStore.getProfile?.bio || ''
      }
    },
    startUploadNewAvatar(fileInputEv: Event) {
      const file = (fileInputEv.target as HTMLInputElement).files?.[0]
      if (file) {
        this.authStore.updateAvatar(file)
      }
    },
    async updateUsername() {
      const worked = await this.authStore.updateUsername(this.fields.username)
      if (worked) {
        this.infoMsg = 'Vos informations ont été mises à jour avec succès'
        this.infoColor = 'success'
        this.isInfoBarVisible = true
      } else {
        this.infoMsg = 'Une erreur est survenue lors de la mise à jour de vos informations'
        this.infoColor = 'error'
        this.isInfoBarVisible = true
      }
    },
    async updateUserInformation() {
      const worked = await this.authStore.updateUserInfo({
        firstName: this.fields.firstName,
        lastName: this.fields.lastName,
        bio: this.fields.bio
      })
      if (worked) {
        this.infoMsg = 'Vos informations ont été mises à jour avec succès'
        this.infoColor = 'success'
        this.isInfoBarVisible = true
      } else {
        this.infoMsg = this.authStore.error.message
        this.infoColor = 'error'
        this.isInfoBarVisible = true
      }
    },
    resetForm() {
      this.hydrateFields()
    }
  }
})
</script>

<style lang="scss" scoped></style>
