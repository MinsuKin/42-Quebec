/** @type {import('tailwindcss').Config} */
/* eslint-disable no-undef */
module.exports = {
  content: ['src/**/*.vue', 'src/App.vue'],
  theme: {
    container: {
      center: true,
      padding: '2rem'
    },
    extend: {
      maxWidth: {
        '1/2': '50%',
        '2/3': '60%',
      },
      color: {
        darkBlue: '#010626',
        white: '#F2F3F4',
        black: '#000002',
        secondary: '#797E9E'
      },
      backgroundColor: {
        darkBlue: '#010626',
        light: '#B3B4BE',
        black: '#000002',
        orange: '#F26A4B',
        lightDarkBlue: '#071040',
        skyBlue: '#50F2E2',
        purpleBlue: '#8C1B85'
      },
      borderColor: {
        light: '#B3B4BE',
        darkBlue: '#010626',
        orange: '#F26A4B'
      },
      boxShadow: {
        lg: 'rgba(0, 0, 2, .7) 0px 3px 10px'
      },
      keyframes: {
        slidein: {
          '0%': {
            display: 'none',
            opacity: 0,
          },
          '1%': {
            display: 'block',
            opacity: 0,
            transform: "translate(-5px)"
          },
          '100%': {
            opacity: 1,
            transform: "translate(0)"
          }
        }
      },
      animation: {
        'anime-in': 'slidein 200ms linear',
      },
    }
  },
  plugins: []
}
