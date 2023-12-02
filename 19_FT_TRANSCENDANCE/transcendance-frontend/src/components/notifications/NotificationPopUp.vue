<template>
  <VSnackbar
    v-model="isSnackbarVisible"
    transition="scale-transition"
    location="top"
    :color="color"
    :timeout="2000"
  >
    {{ snackbarMsg }}
    <template #actions>
      <VBtn
        color="error"
        @click="isSnackbarVisible = false"
      >
        Fermer
      </VBtn>
    </template>
  </VSnackbar>
</template>

<script lang="ts">
import { defineComponent } from 'vue'

export default defineComponent({
  name: 'NotificationPopUp',
  props: {
    snackbarMsg: {
      type: String,
      default: () => ''
    },
    visible: {
      type: Boolean,
      default: () => false
    },
    color: {
      type: String,
      default: () => 'default'
    }
  },
  emits: ['update:visible'],
  computed: {
    isSnackbarVisible: {
      get(): boolean {
        return this.visible
      },
      set(val: boolean) {
        this.$emit('update:visible', val)
      }
    }
  }
})
</script>

<style scoped></style>
