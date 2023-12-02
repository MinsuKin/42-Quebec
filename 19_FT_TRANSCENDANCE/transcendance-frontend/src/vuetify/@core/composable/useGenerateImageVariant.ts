import { useThemeConfig } from '@core/composable/useThemeConfig'
import { computed } from 'vue'

const { theme, skin } = useThemeConfig()

export const useGenerateImageVariant = (
  imgLight: string,
  imgDark: string,
  imgLightBordered?: string,
  imgDarkBordered?: string,
  bordered = false
) => {
  return computed(() => {
    if (theme.value === 'light') {
      if (skin.value === 'bordered' && bordered) return imgLightBordered
      else return imgLight
    } else {
      if (skin.value === 'bordered' && bordered) return imgDarkBordered
      else return imgDark
    }
  })
}
