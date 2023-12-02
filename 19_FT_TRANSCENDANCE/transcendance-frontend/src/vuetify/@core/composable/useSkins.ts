import { VThemeProvider } from 'vuetify/components'
import { AppContentLayoutNav } from '@layouts/enums'
import { useThemeConfig } from '@core/composable/useThemeConfig'
import { computed, h, watch } from 'vue'

export const useSkins = () => {
  const { isVerticalNavSemiDark, skin, appContentLayoutNav } = useThemeConfig()

  const layoutAttrs = computed(() => ({
    verticalNavAttrs: {
      wrapper: h(VThemeProvider, { tag: 'aside' }),
      wrapperProps: {
        withBackground: true,
        theme:
          isVerticalNavSemiDark.value && appContentLayoutNav.value === AppContentLayoutNav.Vertical
            ? 'dark'
            : undefined
      }
    }
  }))

  const injectSkinClasses = () => {
    const bodyClasses = document.body.classList
    const genSkinClass = (_skin?: string) => `skin--${_skin}`

    watch(
      skin,
      (val, oldVal) => {
        bodyClasses.remove(genSkinClass(oldVal))
        bodyClasses.add(genSkinClass(val))
      },
      { immediate: true }
    )
  }

  return {
    injectSkinClasses,
    layoutAttrs
  }
}
