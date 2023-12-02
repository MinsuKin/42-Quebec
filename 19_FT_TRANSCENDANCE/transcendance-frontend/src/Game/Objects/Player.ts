import { GameUser } from '@/Game/network/GameNetwork'
import PongScene from '@/Game/scenes/PongScene'
import { PAD_DIRECTION, PaddleEngineData } from '@/Game/network/Monitor'
import { Theme } from '@/Game/scenes/Boot'

export enum PlayerType {
  Local,
  Online,
  AI
}

const PADDLE_WIDTH = 32 // Width of the paddle
export const PADDLE_HEIGHT = 128 // Height of the paddle
export class Player {
  public averageSpeed = 750
  private usernameText: Phaser.GameObjects.Text
  public paddle: Phaser.Types.Physics.Arcade.SpriteWithDynamicBody

  constructor(
    public scene: PongScene,
    private type: PlayerType,
    startPosition: { x: number; y: number },
    private isHost: boolean,
    private theme: Theme,
    public readonly info: GameUser
  ) {
    // create a rectangle for the paddle and add it to the group
    let key = 'paddle'
    switch (this.theme) {
      case Theme.Arcade:
        key = isHost ? 'pad_left' : 'pad_right'
        break
      case Theme.Soccer:
        key = isHost ? 'pad_left' : 'pad_right'
        break
    }
    this.paddle = scene.physics.add.sprite(startPosition.x, startPosition.y, key)
    this.paddle.setOrigin(0, 0)
    this.paddle.setDisplaySize(PADDLE_WIDTH, PADDLE_HEIGHT)
    this.paddle.setCollideWorldBounds(true)
    this.paddle.setBounce(0, 1.2)
    this.paddle.setImmovable(true)
    this.paddle.setPushable(false)
    const space = isHost ? 100 : 1150
    this.usernameText = this.scene.add.text(space, 30, info.username, {
      fontFamily: 'Arial',
      fontSize: 20,
      color: info.userId === scene.currentUser.userId ? '#f26a4b' : '#ffffff'
    })
    this.usernameText.setOrigin(0, 0)
    this.usernameText.setDepth(1)
  }

  // called when network send the new position of the paddle
  newPaddlePosition(data: PaddleEngineData) {
    const { position, speed } = data
    this.paddle.setPosition(position.x, position.y)
    this.paddle.setVelocity(speed.x, speed.y)
  }

  applyDeceleration() {
    if (this.type === PlayerType.AI) {
      const deceleration = 0.2
      const currentVelocity = this.paddle.body?.velocity.y ?? 0
      if (currentVelocity === 0) return
      this.paddle.setVelocityY(currentVelocity * deceleration)
    } else {
      const deceleration = 0.9
      const currentVelocity = this.paddle.body?.velocity.y ?? 0
      if (currentVelocity === 0) return
      this.paddle.setVelocityY(currentVelocity * deceleration)
    }
  }

  update() {
    if (this.type === PlayerType.Local) {
      this.updateLocalPlayer()
    }
    this.applyDeceleration()
  }

  updateLocalPlayer() {
    if (this.scene.cursorKeys?.up.isDown) {
      this.sendPaddlePositionToServer(PAD_DIRECTION.up)
    } else if (this.scene.cursorKeys?.down.isDown) {
      this.sendPaddlePositionToServer(PAD_DIRECTION.down)
    }
  }

  sendPaddlePositionToServer(dir: PAD_DIRECTION) {
    if (this.info.userId !== this.scene.currentUser.userId) return
    this.scene.monitor.sendPadMove({
      userId: this.info.userId,
      direction: dir,
      position: { x: this.paddle.x, y: this.paddle.y }
    })
  }
}
