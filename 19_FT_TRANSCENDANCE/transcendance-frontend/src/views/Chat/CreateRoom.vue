<template>
  <div>
    <span>Créer un chat</span>
    <v-menu
      v-model="menu"
      transition="scale-transition"
      :close-on-content-click="false"
      location="end top"
      offset="10px -20px"
    >
      <template #activator="{ props }">
        <v-btn
          icon
          color="transparent"
          class="w-full p-2 text-left"
          v-bind="props"
        >
          <v-icon
            color="primary"
            icon="ic:round-add"
            size="24"
          />
        </v-btn>
      </template>
      <v-card>
        <v-list>
          <v-list-item>
            <div class="p-4">
              <v-sheet
                width="300"
                class="mx-auto"
              >
                <h2 class="mb-4 text-sm font-bold">
                  Création de room
                </h2>
                <v-form
                  v-model="form"
                  @submit.prevent="createRoom"
                >
                  <div class="flex flex-col gap-4">
                    <v-text-field
                      v-model="name"
                      :rules="rules.name"
                      label="nom"
                      placeholder="nom du salon"
                    />
                    <v-select
                      v-model="type"
                      :items="typeList"
                    />
                    <v-text-field
                      v-model="password"
                      :disabled="type === RoomType.PUBLIC"
                      :rules="type === RoomType.PUBLIC ? [] : rules.password"
                      label="mot de passe"
                      :type="passwordFieldsVisibility.password ? 'text' : 'password'"
                      :append-inner-icon="
                        passwordFieldsVisibility.password ? 'tabler-eye-off' : 'tabler-eye'
                      "
                      @click:append-inner="
                        passwordFieldsVisibility.password = !passwordFieldsVisibility.password
                      "
                    />
                    <v-text-field
                      v-model="confirmPassword"
                      :disabled="type === RoomType.PUBLIC"
                      :rules="type === RoomType.PUBLIC ? [] : rules.passwordConfirmation"
                      label="Verifiez le mot de passe"
                      :type="passwordFieldsVisibility.confirmPassword ? 'text' : 'password'"
                      :append-inner-icon="
                        passwordFieldsVisibility.confirmPassword ? 'tabler-eye-off' : 'tabler-eye'
                      "
                      @click:append-inner="
                        passwordFieldsVisibility.confirmPassword =
                          !passwordFieldsVisibility.confirmPassword
                      "
                    />
                    <v-btn
                      :loading="loading"
                      type="submit"
                      :block="true"
                      class="mt-2"
                      text="Créer"
                      :disabled="!form"
                    />
                  </div>
                </v-form>
                <NotificationPopUp
                  v-model:visible="showErrorPopUp"
                  message="Impossible de créer la salle de discussion"
                  color="error"
                />
              </v-sheet>
            </div>
          </v-list-item>
        </v-list>
      </v-card>
    </v-menu>
  </div>
</template>
<script setup lang="ts">
import { ref, reactive } from 'vue'
import NotificationPopUp from '@/components/notifications/NotificationPopUp.vue'
import useRoomsStore from '@/stores/RoomsStore'
import useAuthStore from '@/stores/AuthStore'
import { RoomType } from '@/utils/chatSocket'

const roomStore = useRoomsStore()
const authStore = useAuthStore()
const menu = ref(false)
const emit = defineEmits(['close'])
const showErrorPopUp = ref(false)
const name = ref('')
const password = ref('')
const confirmPassword = ref('')
const form = ref(false)

const typeList: RoomType[] = [RoomType.PUBLIC, RoomType.PROTECTED, RoomType.PRIVATE]
const type = ref(typeList[0])
const loading = ref(false)
const rules = reactive({
  name: [
    (v: string) => !!v || 'Le nom de la salle est requis',
    (v: string) =>
      (v && v.length <= 20) || 'Le nom de la salle doit être inférieur à 20 caractères',
    (v: string) => (v && v.length >= 3) || 'Le nom de la salle doit être supérieur à 3 caractères',
    (v: string) => !checkBadWord(v) || 'Le nom de la salle contient un mot interdit'
  ],
  password: [
    (v: string) => !!v || 'Le mot de passe est requis',
    (v: string) => (v && v.length <= 20) || 'Le mot de passe doit être inférieur à 20 caractères',
    (v: string) => (v && v.length >= 6) || 'Le mot de passe doit être supérieur à 6 caractères'
  ],
  passwordConfirmation: [
    (v: string) => !!v || 'La confirmation du mot de passe est requise',
    (v: string) =>
      (v && v.length <= 20) ||
      'La confirmation du mot de passe doit être inférieur à 20 caractères',
    (v: string) =>
      (v && v.length >= 6) || 'La confirmation du mot de passe doit être supérieur à 6 caractères',
    (v: string) => v === password.value || 'Les mots de passe ne correspondent pas'
  ]
})
const forbiddenWords = [
  'con',
  'connard',
  'salope',
  'pute',
  'merde',
  'enculé',
  'calis',
  'tabarnak',
  'sacrament',
  'ostie'
]

const passwordFieldsVisibility = reactive({
  password: false,
  confirmPassword: false
})

const checkBadWord = (str: string) => {
  const lowerCaseStr = str.toLowerCase()
  for (const word of forbiddenWords) {
    if (lowerCaseStr.includes(word.toLowerCase())) {
      return true
    }
  }
  return false
}

const resetForm = () => {
  name.value = ''
  type.value = RoomType.PUBLIC
  password.value = ''
  confirmPassword.value = ''
  showErrorPopUp.value = false
  return
}

const createRoom = async () => {
  loading.value = true
  const result = await roomStore.createRoom({
    name: name.value,
    ownerId: authStore.getUser?.id ?? 1,
    type: type.value,
    password:
      type.value === RoomType.PROTECTED || type.value === RoomType.PRIVATE
        ? password.value
        : undefined
  })
  if (result === 'success') {
    resetForm()
    loading.value = false
    emit('close')
    return
  }
  showErrorPopUp.value = true
  loading.value = false
  emit('close')
}
</script>
