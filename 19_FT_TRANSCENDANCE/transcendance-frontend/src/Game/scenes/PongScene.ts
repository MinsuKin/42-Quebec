import { Scene } from 'phaser'
import { Ball } from '@/Game/Objects/Ball'
import { PADDLE_HEIGHT, Player, PlayerType } from '@/Game/Objects/Player'
import { SceneInitData, Theme } from '@/Game/scenes/Boot'
import Monitor, { GAME_STATE } from '@/Game/network/Monitor'
import { GameUser, GameUserType } from '@/Game/network/GameNetwork'

export type ScoreBoard = { digit1: Phaser.GameObjects.Image; digit2: Phaser.GameObjects.Image }
export default class PongScene extends Scene {
  public ball!: Ball
  private players!: Player[]
  public monitor!: Monitor
  public currentUser!: GameUser & { userType: GameUserType }
  public theme!: Theme
  public cursorKeys: Phaser.Types.Input.Keyboard.CursorKeys | undefined
  public escKey: Phaser.Input.Keyboard.Key | undefined
  public QKey: Phaser.Input.Keyboard.Key | undefined
  private scoreImages!: { player1: ScoreBoard; player2: ScoreBoard }
  private playerOneScoreText!: Phaser.GameObjects.BitmapText
  private playerTwoScoreText!: Phaser.GameObjects.BitmapText
  private scoreRoutineOn = false
  private soundConfig: Phaser.Types.Sound.SoundConfig = { mute: false, volume: 0.2 }
  constructor() {
    super('PongGame')
  }

  init(data: SceneInitData) {
    this.currentUser = data.currentUser
    this.theme = data.theme
    this.monitor = data.gameMonitor
    this.monitor.cleanAllPhaserRoutines()
  }

  create() {
    // this.physics.world.createDebugGraphic()
    this.physics.world.setBounds(0, 0, 1334, 750)
    // create inputs for keyboard and mouse
    this.QKey = this.input.keyboard?.addKey('Q')
    this.cursorKeys = this.input.keyboard?.createCursorKeys()
    // @ts-expect-error no usage, just for testing
    this.input?.keyboard?.on('keydown', function (_event) {
      // console.log('check key down event recieved')
    })
    this.createPlayers()
    this.ball = new Ball(this, this.theme, { x: 667, y: 375 })
    this.createScores()
    this.buildThemeLayer()
    this.buildCollisionsEffects()
    this.monitor._phaserBallMovedRoutine = (data, latency) => {
      this.ball.newPosition(data.position, data.speed)
    }
    this.monitor._phaserPlayerMovedRoutine = (data, latency) => {
      this.players.forEach((player) => {
        if (player.info.userId === data.userId) {
          player.newPaddlePosition(data)
        }
      })
    }
    this.monitor._phaserGameMonitorStateChangedRoutine = (state) => {
      if (state === GAME_STATE.Ended) {
        this.time.delayedCall(275, () => {
          this.scene.start('Menu', {
            currentUser: this.currentUser,
            theme: this.theme,
            gameMonitor: this.monitor
          })
        })
      }
    }
    this.monitor._phaserNewScoreRoutine = (scores, withEffect) => {
      if (this.monitor.state !== GAME_STATE.Play) return
      this.updatedScoreBoard(scores)
      if (withEffect) this.scoredRoutine()
    }
    this.monitor._phaserNewPlayerListRoutine = (users) => {}
    this.monitor._phaserNewViewerListRoutine = (users) => {}
    this.monitor._phaserPlayerLeftRoutine = (player) => {
      // show a message that the player left
      const message = this.add.bitmapText(667, 375, 'atari', 'Player Left')
      message.setOrigin(0.5, 0.5)
      message.setDepth(2)
      this.time.delayedCall(250, () => {
        message?.setVisible(false)
      })
    }
    this.monitor._phaserBallPaddleCollisionRoutine = (paddleUserId) => {
      this.paddleBallCollisionRoutine(paddleUserId)
    }
    this.scoreRoutineOn = false
  }

  createPlayers() {
    this.players = []
    const middle = 375 - PADDLE_HEIGHT / 2
    this.monitor.players.forEach((player) => {
      let playerType =
        player.userId === this.currentUser.userId ? PlayerType.Local : PlayerType.Online
      const isHost = player.userId === this.monitor.hostId
      if (player.userId === 0) playerType = PlayerType.AI
      if (isHost) {
        this.players.push(
          new Player(this, playerType, { x: 100, y: middle }, isHost, this.theme, player)
        )
      } else {
        this.players.push(
          new Player(this, playerType, { x: 1234, y: middle }, isHost, this.theme, player)
        )
      }
    })
  }

  createScores() {
    const middle = this.scale.width / 2
    if (this.theme !== Theme.Soccer) {
      const bitmapKey = 'atari'
      this.playerOneScoreText = this.add.bitmapText(middle - 50, 70, bitmapKey, '0')
      this.playerOneScoreText.setOrigin(0.5, 0.5)
      this.playerTwoScoreText = this.add.bitmapText(middle + 50, 70, bitmapKey, '0')
      this.playerTwoScoreText.setOrigin(0.5, 0.5)
      // align at the center
      return
    }
    const numberSpriteKey = 'numbers_score'
    this.scoreImages = {
      player1: {
        digit2: this.add.image(middle - 120, 70, numberSpriteKey, '0'),
        digit1: this.add.image(middle - 70, 70, numberSpriteKey, '0')
      },
      player2: {
        digit1: this.add.image(middle + 70, 70, numberSpriteKey, '0'),
        digit2: this.add.image(middle + 120, 70, numberSpriteKey, '0')
      }
    }
    // disable the second digit
    this.scoreImages.player1.digit1.setVisible(false)
    this.scoreImages.player2.digit1.setVisible(false)
    // put image of scores on another layer
    this.scoreImages.player1.digit1.setDepth(1)
    this.scoreImages.player1.digit2.setDepth(1)
    this.scoreImages.player2.digit1.setDepth(1)
    this.scoreImages.player2.digit2.setDepth(1)
  }

  private updateSoccerScoreBoard(scores: { userId: number; score: number }[]) {
    if (scores.length < 2) return
    const digitsScore1 = scores[0].score.toString().split('')
    const digitsScore2 = scores[1].score.toString().split('')
    if (digitsScore1.length > 1) {
      this.scoreImages.player1.digit1.setVisible(true)
      this.scoreImages.player1.digit1.setFrame(digitsScore1[0])
      this.scoreImages.player1.digit2.setFrame(digitsScore1[1])
    } else {
      this.scoreImages.player1.digit2.setFrame(digitsScore1[0])
    }
    if (digitsScore2.length > 1) {
      this.scoreImages.player2.digit1.setVisible(true)
      this.scoreImages.player2.digit1.setFrame(digitsScore2[0])
      this.scoreImages.player2.digit2.setFrame(digitsScore2[1])
    } else {
      this.scoreImages.player2.digit2.setFrame(digitsScore2[0])
    }
  }
  private updatedScoreBoard(scores: { userId: number; score: number }[]) {
    if (this.theme === Theme.Soccer) {
      this.updateSoccerScoreBoard(scores)
      return
    }
    this.playerOneScoreText.text = this.monitor.getPlayer1Score().toString()
    this.playerTwoScoreText.text = this.monitor.getPlayer2Score().toString()
  }

  private buildMiddleLine(color: number) {
    const middle = this.scale.width / 2
    const dashLength = 20 // Length of each dash
    const gapLength = 10 // Length of the gap between dashes
    const totalLength = 750 // Total length of the line
    const graphics = this.add.graphics({
      lineStyle: {
        width: 5,
        color: color
      }
    })
    // put graphics on another layer
    graphics.setDepth(-1)
    const numberOfDashes = Math.floor(totalLength / (dashLength + gapLength))
    for (let i = 0; i < numberOfDashes; i++) {
      const startY = i * (dashLength + gapLength)
      const endY = startY + dashLength
      const line = new Phaser.Geom.Line(middle - 2.5, startY, middle - 2.5, endY)
      graphics.strokeLineShape(line)
    }
  }

  private buildThemeLayer() {
    if (this.theme === Theme.Classic) {
      this.buildMiddleLine(0xffffff)
    } else if (this.theme === Theme.Soccer) {
      const soccer_court = this.add.image(667, 375, 'soccer_court')
      soccer_court.scaleX = 1.2853801967467613
      soccer_court.scaleY = 1.2427411843889709
      //put image on another layer
      soccer_court.setDepth(-1)
    } else if (this.theme === Theme.Arcade) {
      // put a pink middle line
      this.buildMiddleLine(0xff00ff)
      // put a dark blue background
      this.cameras.main.setBackgroundColor('#000033')
    }
  }

  buildCollisionsEffects() {
    // this.physics.add.collider(this.ball.getSprite(), this.leftLine)
    // this.physics.add.collider(this.ball.getSprite(), this.rightLine)
  }

  private scoredRoutine() {
    this.scoreRoutineOn = true
    const goal = this.add.image(667, 375, 'text_goal')
    goal.setDepth(2)
    this.sound.play('goal_sound', this.soundConfig)
    this.time.delayedCall(500, () => {
      goal.destroy()
      this.scoreRoutineOn = false
    })
    // shake the camera
    this.cameras.main.shake(400, 0.03)
    this.ball.newPosition({ x: 667, y: 375 }, { x: 0, y: 0 })
  }

  private paddleBallCollisionRoutine(_paddleUserId: number) {
    if (this.theme !== Theme.Soccer) {
      this.sound.play('pad_hit_sound', this.soundConfig)
    } else {
      this.sound.play('pad_hit_soccer_sound', this.soundConfig)
    }
  }

  update() {
    this.players.forEach((player) => {
      player.update()
    })
    this.ball.update()
    if (!this.scoreRoutineOn) {
      if (this.cursorKeys?.space.isDown) {
        this.monitor.serveBall()
      }
    }
    // listen to esc key or Q key to quit the game
    if (this.escKey?.isDown || this.QKey?.isDown) {
      this.monitor.quitAndMoveToHistory()
    }
  }
}
