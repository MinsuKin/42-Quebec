import { fileURLToPath, URL } from 'node:url'
import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import vueJsx from '@vitejs/plugin-vue-jsx'
import vuetify from 'vite-plugin-vuetify'
import AutoImport from 'unplugin-auto-import/vite'
import Components from 'unplugin-vue-components/vite'

// https://vitejs.dev/config/
export default defineConfig({
  server: {
    host: '0.0.0.0',
    port: 3000
  },
  plugins: [
    vue(),
    vueJsx(),
    vuetify(),
    Components({
      dirs: ['/src/vuetify/@core', 'src/components'],
      dts: true,
    }),
    AutoImport({
      imports: ['vue', 'vue-router', '@vueuse/core', '@vueuse/math', 'pinia'],
      vueTemplate: true,
      dts: true,
    }),
  ],
  resolve: {
    alias: {
      '@': fileURLToPath(new URL('./src', import.meta.url)),
      '@views': fileURLToPath(new URL('./src/views', import.meta.url)),
      '@themeConfig': fileURLToPath(new URL('./src/vuetify/themeConfig.ts', import.meta.url)),
      '@core': fileURLToPath(new URL('./src/vuetify/@core', import.meta.url)),
      '@layouts': fileURLToPath(new URL('./src/vuetify/@layouts', import.meta.url)),
      '@styles': fileURLToPath(new URL('./src/vuetify/styles/', import.meta.url)),
      '@configured-variables': fileURLToPath(new URL('./src/vuetify/styles/variables/_template.scss', import.meta.url)),
    }
  },
  optimizeDeps: {
    exclude: ['vuetify'],
    entries: [
      './src/**/*.vue',
    ],
  },
  build: {
    minify: 'esbuild',
    rollupOptions: {
      output: {
        entryFileNames: `[name].js`,
        // chunkFileNames: `[name].js`,
        assetFileNames: `[name].[ext]`,
        manualChunks: {
          phaser: ['phaser'],
          chartjs: ['chart.js'],
          vuetify: ['vuetify']
        }
      }
    },
    emptyOutDir: false,
  }
})
