import { Scene } from 'phaser'
import Monitor, { GAME_STATE } from '@/Game/network/Monitor'
import { GameUser, GameUserType } from '@/Game/network/GameNetwork'

export enum Theme {
  Classic = 'Classic',
  Arcade = 'Arcade',
  Soccer = 'Soccer'
}

export interface SceneInitData {
  currentUser: GameUser & { userType: GameUserType }
  theme: Theme
  gameMonitor: Monitor
}
export default class Boot extends Scene {
  sceneData!: SceneInitData

  constructor() {
    super({
      key: 'Boot'
    })
  }

  init(data: SceneInitData) {
    this.sceneData = data
    data.gameMonitor.cleanAllPhaserRoutines()
    if (
      this.game.device.os.iOS ||
      this.game.device.os.android ||
      this.game.device.os.windowsPhone
    ) {
      if (Math.min(window.screen.width, window.screen.height) < this.game.scale.width) {
        this.scale.lockOrientation('landscape')
      }
    }
    data.gameMonitor.sendGameState(GAME_STATE.Preloading)
  }

  preload() {
    this.load.pack('backgrounds-assets', '/pong/backgrounds-pack.json')
  }

  create() {
    this.scene.start('Preload', this.sceneData)
  }
}
