<template>
  <div class="relative -top-6 ml-1 h-16 w-16 flex items-center justify-center">
    <svg
      id="banner"
      xmlns="http://www.w3.org/2000/svg"
      xmlns:xlink="http://www.w3.org/1999/xlink"
      version="1.1"
      x="0px"
      y="0px"
      viewBox="0 0 68 104"
      :style="style"
      xml:space="preserve"
      class="absolute h-16 w-16"
    >
      <g id="banner-content">
        <g
          id="UI-Intranet-banner-content"
          transform="translate(-96.000000, -60.000000)"
        >
          <g
            id="banner-content-g-1"
            transform="translate(96.000000, 60.000000)"
          >
            <polygon
              id="banner-content-polygon-1"
              points="0,0 0,80.5 34.3,104 68,80.5 68,0"
            />
          </g>
        </g>
      </g>
    </svg>
    <img
      :src="image"
      class="absolute w-8 h-8 fill-white"
    >
  </div>
</template>

<script setup lang="ts">
import { computed } from 'vue'

const props = defineProps({
  color: {
    type: String,
    required: true,
    default: '#c6c6c6'
  },
  image: {
    type: String,
    required: false,
    default: 'https://cdn.intra.42.fr/coalition/image/243/42Q_035_22_Logo_Legion.svg'
  }
})
// computed style value
const style = computed(() => {
  return `enable-background:new 0 0 68 104; fill: ${props.color};`
})
</script>

<style scoped lang="scss"></style>
