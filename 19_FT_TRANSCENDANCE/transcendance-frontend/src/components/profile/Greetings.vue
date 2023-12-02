<template>
  <div class="w-full">
    <div class="px-8 py-4">
      <h1 class="">
        <span class=""> {{ greetMe() }}, </span>
        <span class="text-2xl font-bold">
          {{
            `${authStore.user?.profile?.name.split(' ').shift()} ${authStore.user?.profile?.lastname
              .split(' ')
              .shift()}! `
          }}
        </span>
      </h1>
      <div>
        <div class="flex flex-col justify-between gap-4 md:flex-row">
          <div>
            <p
              v-if="dateObject.hours"
              class="font-thin text-7xl"
            >
              {{ `${dateObject.hours}:${dateObject.minutes}:${dateObject.seconds}` }}
            </p>
          </div>
          <div class="">
            <p class="">
              Partie Rapide
            </p>
            <div class="flex gap-2">
              <button
                class="inline-block px-4 py-2 text-sm border rounded-md bg-none hover:bg-orange/10"
                @click.prevent="goToPlayWithBot"
              >
                <span class="flex items-center gap-1">
                  <v-avatar
                    rounded
                    variant="tonal"
                    color="orange"
                    icon="mdi-gamepad-circle-up"
                  />
                  <span>Contre l'IA</span>
                </span>
              </button>
              <button
                class="inline-block px-4 py-2 text-sm border rounded-md bg-none hover:bg-cyan-400/10"
                @click.prevent="goToWaitingRoom"
              >
                <v-avatar
                  rounded
                  variant="tonal"
                  color="cyan"
                  icon="medical-icon:i-waiting-area"
                />
                <span> Salle d'attente </span>
              </button>
              <button
                class="inline-block px-4 py-2 text-sm border rounded-md bg-none hover:bg-yellow-400/10"
                @click.prevent="challenge"
              >
                <v-avatar
                  rounded
                  variant="tonal"
                  color="yellow"
                  icon="mdi-goal"
                />
                <span> Challenger </span>
              </button>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>
<script setup lang="ts">
import useAuthStore from '@/stores/AuthStore'
import { ref, onMounted, onBeforeUnmount } from 'vue'
import { useRouter } from 'vue-router'

const authStore = useAuthStore()
const router = useRouter()
const greetMe = () => {
  const now = new Date()
  if (now.getHours() >= 6 && now.getHours() < 12) {
    return 'Bonjour'
  } else if (now.getHours() >= 12 && now.getHours() < 18) {
    return 'Bon après-midi'
  } else if (now.getHours() >= 18 && now.getHours() < 24) {
    return 'Bonsoir'
  } else if (now.getHours() >= 0 && now.getHours() < 6) {
    return 'Bonne nuit'
  }
}

type DateObject = {
  now: Date
  hours: number | string
  minutes: number | string
  seconds: number | string
}
const now = new Date()
let dateObject = ref<DateObject>({
  now,
  hours: now.getHours(),
  minutes: now.getMinutes(),
  seconds: now.getSeconds()
})

const getDate = (dateObject: DateObject) => {
  dateObject['now'] = new Date()
  return dateObject
}
const getHours = (dateObject: DateObject) => {
  dateObject['hours'] = dateObject.now.getHours()
  return dateObject
}
const getMinutes = (dateObject: DateObject) => {
  dateObject['minutes'] = dateObject.now.getMinutes()
  return dateObject
}
const getSeconds = (dateObject: DateObject) => {
  dateObject['seconds'] = dateObject.now.getSeconds()
  return dateObject
}
const formatTime = (dateObject: DateObject) => {
  const { hours, minutes, seconds } = dateObject
  if (+hours < 10) dateObject['hours'] = `0${hours}`
  if (+minutes < 10) dateObject['minutes'] = `0${minutes}`
  if (+seconds < 10) dateObject['seconds'] = `0${seconds}`
  return dateObject
}

const compose =
  (...fns: Array<(dateObject: DateObject) => DateObject>) =>
  (dateObject: DateObject) =>
    fns.reduceRight((acc, fn) => fn(acc), dateObject)

const makeDate = compose(formatTime, getSeconds, getMinutes, getHours, getDate)
let timer: NodeJS.Timeout | null = null

// const getUserPosLonLat = async () => {
//   if (navigator.geolocation) {
//     navigator.geolocation.getCurrentPosition((position) => {
//       console.log(position)
//     })
//   }
// }

onMounted(() => {
  timer = setInterval(() => {
    dateObject.value = makeDate(dateObject.value)
  }, 1000)
})

onBeforeUnmount(() => {
  if (timer) clearInterval(timer)
})

const goToPlayWithBot = () => {
  router.push({ name: 'bot-game' })
}
const goToWaitingRoom = () => {
  router.push({ name: 'waiting-room' })
}

const challenge = () => {
  router.push({ name: 'user-list' })
}
</script>
