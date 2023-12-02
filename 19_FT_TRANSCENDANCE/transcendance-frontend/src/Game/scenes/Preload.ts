import { Scene } from 'phaser'
import { SceneInitData } from '@/Game/scenes/Boot'
import Monitor, { GAME_STATE } from '@/Game/network/Monitor'

export default class Preload extends Scene {
  sceneData!: SceneInitData
  private readonly uiPackUrl = '/pong/ui-pack.json'
  private readonly sportPackUrl = '/pong/sport-pack.json'
  private readonly arcadePackUrl = '/pong/arcade-pack.json'
  private readonly classicPackUrl = '/pong/classic-pack.json'
  private progressBar!: Phaser.GameObjects.Rectangle
  private monitor!: Monitor

  constructor() {
    super({
      key: 'Preload'
    })
  }
  preload() {
    this.load.pack('ui-pack', this.uiPackUrl)
    this.load.pack('sport-pack', this.sportPackUrl)
    this.load.pack('arcade-pack', this.arcadePackUrl)
    this.load.pack('classic-pack', this.classicPackUrl)
    this.load.bitmapFont('atari', '/pong/fonts/atari-classic.png', '/pong/fonts/atari-classic.xml')
    this.load.bitmapFont('nokia', '/pong/fonts/nokia16.png', '/pong/fonts/nokia16.xml')
  }

  init(data: SceneInitData) {
    this.sceneData = data
    this.monitor = data.gameMonitor
    this.monitor.cleanAllPhaserRoutines()
  }

  create() {
    // background
    const background = this.add.image(667, 375, 'winter_train_hd')
    background.scaleX = 0.475
    background.scaleY = 0.48
    // school_logo_white
    const school_logo_white = this.add.image(667, 200, 'school-logo-white')
    school_logo_white.scaleX = 2.5
    school_logo_white.scaleY = 2.5
    // progressBarOut
    const progressBarOut = this.add.rectangle(667, 375, 500, 50)
    progressBarOut.isStroked = true
    progressBarOut.lineWidth = 5
    // progressBar
    const progressBar = this.add.rectangle(667, 375, 498, 48)
    progressBar.isFilled = true
    progressBar.fillColor = 216674
    progressBar.isStroked = true
    progressBar.strokeColor = 12783889
    this.progressBar = progressBar
    const fullWidth = this.progressBar.width
    this.load.on(Phaser.Loader.Events.PROGRESS, (p: number) => {
      this.progressBar.width = fullWidth * p
    })
    this.events.emit('preload')
  }

  update() {
    if (this.load.progress === 1) {
      if (this.monitor.state === GAME_STATE.Play || this.monitor.state === GAME_STATE.Pause) {
        this.scene.start('PongGame', this.sceneData)
      } else {
        this.monitor.sendGameState(GAME_STATE.Menu)
        this.scene.start('Menu', this.sceneData)
      }
    }
  }
}
