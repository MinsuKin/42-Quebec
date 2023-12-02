import { Scene, GameObjects, Geom } from 'phaser'
import Menu from '@/Game/scenes/Menu'

export default class Button extends GameObjects.Container {
  private textLabel: GameObjects.Text
  private btnBg: GameObjects.Image
  private _btnActive: boolean = true

  constructor(
    scene: Scene,
    position: { x: number; y: number },
    private interactiveArea: { x: number; y: number; width: number; height: number },
    textureKey: string,
    text: string,
    private onClick: () => void
  ) {
    super(scene, position.x, position.y)
    this.btnBg = this.scene.add.image(0, 0, textureKey)
    this.add(this.btnBg)

    this.textLabel = this.scene.add.text(0, 0, text, this.getDefaultTextStyle())
    this.textLabel.setOrigin(0.5, 0.5)
    this.add(this.textLabel)
    this.setupInteractivity()
  }

  private getDefaultTextStyle(): Phaser.Types.GameObjects.Text.TextStyle {
    return {
      align: 'center',
      fontSize: '24px',
      fontStyle: 'bold',
      stroke: '#ae1616ff',
      strokeThickness: 1,
      shadow: { stroke: true }
    }
  }

  private setupInteractivity(): void {
    this.setInteractive(
      new Geom.Rectangle(
        this.interactiveArea.x,
        this.interactiveArea.y,
        this.interactiveArea.width,
        this.interactiveArea.height
      ),
      Geom.Rectangle.Contains
    )

    this.on('pointerdown', () => this.handlePointerDown())
    this.on('pointerover', () => this.handlePointerOver())
    this.on('pointerout', () => this.handlePointerOut())
  }

  private handlePointerDown(): void {
    if (this._btnActive) this.onClick()
  }

  private handlePointerOver(): void {
    if (!this._btnActive) return
    this.btnBg.setTint(0x888888)
    this.btnBg.angle -= 2
  }

  private handlePointerOut(): void {
    if (!this._btnActive) return
    this.btnBg.clearTint()
    this.btnBg.angle += 2
  }

  get textLabelText(): string {
    return this.textLabel.text
  }

  set textLabelText(text: string) {
    this.textLabel.setText(text)
  }

  get textLabelStyle(): Phaser.Types.GameObjects.Text.TextStyle {
    return this.textLabel.style
  }

  set textLabelStyle(style: Phaser.Types.GameObjects.Text.TextStyle) {
    this.textLabel.setStyle(style)
  }

  get btnActiveStatus(): boolean {
    return this._btnActive
  }

  set btnActiveStatus(status: boolean) {
    this._btnActive = status
    this.btnBg.setTint(status ? 0xffffff : 0x000000)
    this.setActive(status).setInteractive(status)
  }
}

export class HomeButton extends GameObjects.Image {
  private readonly namedKeys = {
    homeInactive: 'Btn_Home',
    homeActive: 'Btn_Home_Active'
  }
  private _btnActive: boolean = true
  public isHomePage = true
  constructor(
    scene: Menu,
    x: number,
    y: number,
    public _onClick: () => void
  ) {
    super(scene, x, y, 'Btn_Home_Active')
    this.setupInteractivity()
  }

  private setupInteractivity(): void {
    this.setInteractive(
      new Phaser.Geom.Rectangle(25, 10, 95.3076719479974, 91.4272822913519),
      Phaser.Geom.Rectangle.Contains
    )
    this.on('pointerdown', () => this.handlePointerDown())
    this.on('pointerover', () => this.handlePointerOver())
    this.on('pointerout', () => this.handlePointerOut())
  }

  private handlePointerDown(): void {
    if (this._btnActive) this._onClick()
  }

  private handlePointerOver(): void {
    const inverseKey = this.isHomePage ? this.namedKeys.homeInactive : this.namedKeys.homeActive
    this.flipX = true
    this.setTexture(inverseKey)
  }

  private handlePointerOut(): void {
    const inverseKey = this.isHomePage ? this.namedKeys.homeActive : this.namedKeys.homeInactive
    this.flipX = false
    this.setTexture(inverseKey)
  }

  get btnInteractiveStatus(): boolean {
    return this._btnActive
  }

  set btnInteractiveStatus(status: boolean) {
    this._btnActive = status
    this.setActive(status).setInteractive(status)
  }
}
