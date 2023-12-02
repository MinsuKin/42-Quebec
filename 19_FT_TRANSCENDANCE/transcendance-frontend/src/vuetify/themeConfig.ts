import { breakpointsVuetify } from '@vueuse/core'
import { VIcon } from 'vuetify/components'
import { defineThemeConfig } from '@core'
import { RouteTransitions, Skins } from '@core/enums'
import { AppContentLayoutNav, ContentWidth, FooterType, NavbarType } from '@layouts/enums'
import { h } from 'vue'

export const { themeConfig, layoutConfig } = defineThemeConfig({
  app: {
    title: 'Pong',
    // @ts-expect-error img prop is not defined in type
    logo: h('img', { src: '/logo.png' }, null),
    contentWidth: ContentWidth.Boxed,
    contentLayoutNav: AppContentLayoutNav.Vertical,
    overlayNavFromBreakpoint: breakpointsVuetify.sm + 16,
    enableI18n: false,
    theme: 'dark',
    isRtl: false,
    skin: Skins.Bordered,
    routeTransition: RouteTransitions['Slide Y Reverse'],
    iconRenderer: VIcon
  },
  navbar: {
    type: NavbarType.Sticky,
    navbarBlur: false
  },
  footer: { type: FooterType.Static },
  verticalNav: {
    isVerticalNavCollapsed: true,
    defaultNavItemIconProps: { icon: 'tabler-circle', size: 10 },
    isVerticalNavSemiDark: false
  },
  horizontalNav: {
    type: 'sticky',
    transition: 'slide-y-reverse-transition'
  },
  icons: {
    chevronDown: { icon: 'tabler-chevron-down' },
    chevronRight: { icon: 'tabler-chevron-right', size: 18 },
    close: { icon: 'tabler-x' },
    verticalNavPinned: { icon: 'tabler-circle-dot' },
    verticalNavUnPinned: { icon: 'tabler-circle' },
    sectionTitlePlaceholder: { icon: 'tabler-separator' }
  }
})
