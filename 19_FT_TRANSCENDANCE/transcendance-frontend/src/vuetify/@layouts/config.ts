import { breakpointsVuetify } from '@vueuse/core'
import { AppContentLayoutNav, ContentWidth, FooterType, NavbarType } from '@layouts/enums'
import type { Config } from '@layouts/types'
import { h, ref } from 'vue'
import { VIcon } from 'vuetify/components'

export const config: Config = {
  app: {
    title: 'Pong',
    // @ts-expect-error img not reconized
    logo: h('img', { src: '/src/assets/logo.png' }, null),
    contentWidth: ref(ContentWidth.Boxed),
    contentLayoutNav: ref(AppContentLayoutNav.Vertical),
    overlayNavFromBreakpoint: breakpointsVuetify.sm + 16,
    enableI18n: false,
    isRtl: ref(false),
    iconRenderer: VIcon
  },
  navbar: {
    type: ref(NavbarType.Sticky),
    navbarBlur: ref(true)
  },
  footer: { type: ref(FooterType.Static) },
  verticalNav: {
    isVerticalNavCollapsed: ref(false),
    defaultNavItemIconProps: { icon: 'tabler-circle' }
  },
  horizontalNav: {
    type: ref('sticky')
  },
  icons: {
    chevronDown: { icon: 'tabler-chevron-down' },
    chevronRight: { icon: 'tabler-chevron-right' },
    close: { icon: 'tabler-x' },
    verticalNavPinned: { icon: 'tabler-circle-dot' },
    verticalNavUnPinned: { icon: 'tabler-circle' },
    sectionTitlePlaceholder: { icon: 'tabler-minus' }
  }
}
