// Thanks: https://css-tricks.com/the-trick-to-viewport-units-on-mobile/
import { ref } from 'vue'
import { tryOnBeforeMount, useEventListener } from '@vueuse/core'

export const useDynamicVhCssProperty = () => {
  const vh = ref(0)

  const updateVh = () => {
    vh.value = window.innerHeight * 0.01
    document.documentElement.style.setProperty('--vh', `${vh.value}px`)
  }

  tryOnBeforeMount(() => {
    updateVh()
    useEventListener('resize', updateVh)
  })
}
