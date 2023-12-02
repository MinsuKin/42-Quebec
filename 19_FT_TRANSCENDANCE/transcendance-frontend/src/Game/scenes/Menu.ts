import { GameObjects, Scene } from 'phaser'
import { SceneInitData, Theme } from '@/Game/scenes/Boot'
import Button, { HomeButton } from '@/Game/Objects/Button'
import Monitor, { GAME_STATE } from '@/Game/network/Monitor'
import { GameUser, GameUserType } from '@/Game/network/GameNetwork'

enum MenuSection {
  Home,
  Instructions,
  Settings,
  Credits
}

export default class Menu extends Scene {
  sceneData!: SceneInitData
  private menuSection: MenuSection = MenuSection.Home
  private currentUser!: GameUser & { userType: GameUserType }
  private theme = Theme.Classic
  public monitor!: Monitor
  private switchingScene = false

  //home button
  private homeBtn!: HomeButton // Allow user to come back to home

  // panel section elements
  private boardText!: GameObjects.Text
  private startButton!: Button // to start, if game ended should be disabled

  // home box section
  private sections: MenuSectionBox[] = []
  private playerOneText!: GameObjects.Text
  private playerTwoText!: GameObjects.Text
  private statusNetworkText!: GameObjects.Text

  constructor() {
    super('Menu')
  }

  preload() {}

  init(data: SceneInitData) {
    this.sceneData = data
    this.monitor = data.gameMonitor
    this.monitor.cleanAllPhaserRoutines()
    this.currentUser = data.currentUser
    this.theme = data.theme
  }

  create() {
    this.switchingScene = false
    this.createBackgroundLayer()
    this.createHomeBtn()
    this.createPanelBox()
    this.createHomeBox()
    this.createInstructionsBox()
    this.updateSection()
    this.handleGameStateChange(this.monitor.state)
    this.playerListUpdate(this.monitor.players)
    switch (this.monitor.state) {
      case GAME_STATE.Play:
      case GAME_STATE.Pause:
        this.moveToPongScene()
        break
      case GAME_STATE.Ended:
        this.gameEndedUiUpdate()
        break
    }
    this.setupMonitorEventListeners()
  }

  createHomeBtn() {
    const homeBtn = new HomeButton(this, 150, 640, () => {
      this.menuSection = MenuSection.Home
      homeBtn.isHomePage = true
      this.updateSection()
    })
    this.add.existing(homeBtn)
    this.homeBtn = homeBtn
  }

  // creation of the background layer
  createBackgroundLayer() {
    const layer = this.add.layer()
    const keys = {
      background: 'Background',
      barTop: 'BarTopBlue',
      barDown: 'BarDownBlue',
      sideBar: 'SideBarBlue'
    }
    switch (this.theme) {
      case Theme.Soccer:
        keys.barTop = 'BarTopBrown'
        keys.barDown = 'BarDownBrown'
        keys.sideBar = 'SideBarBrown'
        break
      case Theme.Arcade:
        keys.barTop = 'BarTopPink'
        keys.barDown = 'BarDownPink'
        keys.sideBar = 'SideBarPink'
        break
    }
    const bg = this.add.image(667, 375, keys.background)
    const barTop = this.add.image(1334, 0, keys.barTop)
    // set barTap to match the screen width with scale
    const width = this.game.scale.width
    const scaleTop = width / barTop.width
    barTop.setScale(scaleTop, 1)
    barTop.setOrigin(1, 0)
    const barDown = this.add.image(0, 750, keys.barDown)
    const scaleDown = width / barDown.width
    barDown.setScale(scaleDown, 1)
    barDown.setOrigin(0, 1)
    const sideBar = this.add.image(43, 375, keys.sideBar)
    layer.add(bg)
    layer.add(barTop)
    layer.add(barDown)
    layer.add(sideBar)
    layer.setDepth(-1)
  }

  createPanelBox() {
    const currentUserType = this.currentUser.userType
    const panelBox = new MenuSectionBox(MenuSection.Home, this, { x: 776, y: 108 })
    const bgPanelBox = this.add.image(0, 0, 'BgPanelBox2')
    bgPanelBox.setOrigin(0, 0)
    panelBox.add(bgPanelBox)
    const boardText = this.add.text(180, 24, '', {})
    boardText.setOrigin(0.5, 0.5)
    boardText.text = 'PONG'
    boardText.setStyle({ align: 'center', fontFamily: 'Mono', fontSize: '18px', fontStyle: 'bold' })
    panelBox.add(boardText)
    this.boardText = boardText
    // start Btn
    this.startButton = new Button(
      this,
      { x: 180, y: 150 },
      { x: -110, y: -40, width: 221, height: 80 },
      'B5',
      currentUserType === GameUserType.Player ? 'START GAME' : 'WATCH',
      () => {
        this.monitor.sendGameState(GAME_STATE.Ready)
      }
    )
    panelBox.add(this.startButton)
    const infoBtn = new Button(
      this,
      { x: 180, y: 250 },
      { x: -110, y: -40, width: 221, height: 80 },
      'B15',
      'INSTRUCTIONS',
      () => {
        this.menuSection = MenuSection.Instructions
        this.homeBtn.isHomePage = false
        this.updateSection()
      }
    )
    panelBox.add(infoBtn)
    const quitBtn = new Button(
      this,
      { x: 180, y: 350 },
      { x: -110, y: -40, width: 221, height: 80 },
      'B15',
      'QUIT',
      () => {
        this.monitor.quitAndMoveToHistory()
      }
    )
    panelBox.add(quitBtn)
    this.add.existing(panelBox)
    this.sections.push(panelBox)
  }

  createHomeBox() {
    const homeBox = new MenuSectionBox(MenuSection.Home, this, { x: 362, y: 407 })
    const heroLander = this.add.image(0, 1, 'HeroLander')
    heroLander.setOrigin(0.5, 0)
    homeBox.add(heroLander)
    const blueLight = this.add.image(0, 0, 'BlueLight')
    blueLight.setOrigin(0.5, 1)
    homeBox.add(blueLight)
    this.playerOneText = this.add.text(0, -250, '', {})
    this.playerOneText.setOrigin(0.5, 0.5)
    this.playerOneText.text = ''
    this.playerOneText.setStyle({ align: 'center', fontFamily: 'Arial', fontSize: '18px' })
    homeBox.add(this.playerOneText)
    this.statusNetworkText = this.add.text(-37, 70, '', {})
    this.statusNetworkText.setOrigin(0.5, 0.5)
    this.statusNetworkText.text = 'Network'
    this.statusNetworkText.setStyle({
      align: 'center',
      color: '#6fb4f2ff',
      fontFamily: 'Mono',
      fontSize: '14px'
    })
    homeBox.add(this.statusNetworkText)
    this.playerTwoText = this.add.text(1, -188, '', {})
    this.playerTwoText.setOrigin(0.5, 0.5)
    this.playerTwoText.text = ''
    this.playerTwoText.setStyle({ align: 'center', fontFamily: 'Arial', fontSize: '18px' })
    homeBox.add(this.playerTwoText)
    this.add.existing(homeBox)
    this.sections.push(homeBox)
  }

  createInstructionsBox() {
    const instructionsBox = new MenuSectionBox(MenuSection.Instructions, this, { x: 667, y: 375 })
    // add bg image
    const bgInstructions = this.add.image(0, 0, 'BgInstructionBox')
    bgInstructions.setOrigin(0.5, 0.5)
    instructionsBox.add(bgInstructions)
    // add text
    const instructionsTitleText = this.add.text(0, -200, '', {})
    instructionsTitleText.setOrigin(0.5, 0.5)
    instructionsTitleText.text = 'Instructions'
    instructionsTitleText.setStyle({
      align: 'center',
      fontFamily: 'Arial',
      fontSize: '30px',
      fontStyle: 'bold'
    })
    instructionsBox.add(instructionsTitleText)
    const instructionsText = this.add.text(
      0,
      -50,
      '[-] The goal of the game is to score more points than your opponent.\n' +
        '[-] The game is played with two players, each controlling a paddle.\n' +
        '[-] The ball is served with a random speed.\n' +
        '[-] The ball will bounce off the walls and the paddles.\n' +
        '[-] To move the paddle, use the arrow keys.\n' +
        '[-] Press Q during the game to Quit\n',
      {
        fontFamily: 'Courier',
        fontSize: '20px',
        wordWrap: { width: 600 }
      }
    )
    instructionsText.setOrigin(0.5, 0.5)
    instructionsBox.add(instructionsText)
    this.add.existing(instructionsBox)
    this.sections.push(instructionsBox)
  }

  update(time: number, delta: number) {
    // activate the correct section and deactivate the others
  }
  setupMonitorEventListeners(): void {
    this.monitor._phaserGameMonitorStateChangedRoutine = (state) => {
      this.handleGameStateChange(state)
      if (state === GAME_STATE.Play || state === GAME_STATE.Pause) {
        this.moveToPongScene()
      }
    }
    this.monitor._phaserNewPlayerListRoutine = (players) => {
      this.playerListUpdate(players)
    }
    this.monitor._phaserPlayerLeftRoutine = (player) => {
      this.playerLeftUpdate(player)
    }
  }
  updateSection() {
    this.sections.forEach((section) => {
      section.updateSection(this.menuSection)
    })
  }

  playerListUpdate(playerList: GameUser[]) {
    const player1 = playerList[0]
    const player2 = playerList[1]
    if (player1) {
      this.playerOneText.text = `${player1.username}`
    } else {
      this.playerOneText.text = ''
    }
    if (player2) {
      this.playerTwoText.text = `${player2.username}`
    } else {
      this.playerTwoText.text = ''
    }
    if (player1 && player2) {
      this.startButton.setVisible(true).btnActiveStatus = true
    } else {
      this.startButton.setVisible(false)
    }
  }

  handleGameStateChange(state: GAME_STATE) {
    switch (state) {
      case GAME_STATE.Waiting:
        this.statusNetworkText.text = this.monitor.isNetworkOperational()
          ? 'Init, game'
          : 'Game not found on server'
        this.boardText.text = 'PONG'
        this.startButton.setVisible(true).btnActiveStatus = true
        break
      case GAME_STATE.Menu:
        this.startButton.setVisible(true).btnActiveStatus = true
        this.boardText.text = 'Pong Menu'
        this.statusNetworkText.text = 'Menu'
        break
      case GAME_STATE.Ready:
        this.boardText.text = 'Ready'
        this.startButton.setVisible(true).btnActiveStatus = false
        this.statusNetworkText.text = 'Waiting opponent to start'
        break
      case GAME_STATE.Play:
        this.statusNetworkText.text = 'Playing'
        this.boardText.text = `Let's Go`
        this.startButton.setVisible(true).btnActiveStatus = false
        this.moveToPongScene()
        break
      case GAME_STATE.Ended:
        this.statusNetworkText.text = 'Game ended'
        this.boardText.text = 'Game ended'
        this.startButton.setVisible(false).btnActiveStatus = false
        this.gameEndedUiUpdate()
        break
    }
  }

  playerLeftUpdate(player: GameUser) {
    this.statusNetworkText.text = `${player.username} left`
  }

  moveToPongScene() {
    if (this.switchingScene) return
    this.switchingScene = true
    this.monitor.cleanAllPhaserRoutines()
    this.scene.start('PongGame', this.sceneData)
  }

  gameEndedUiUpdate() {
    this.startButton.btnActiveStatus = false
    const player1Score = this.monitor.getPlayer1Score()
    const player2Score = this.monitor.getPlayer2Score()
    if (player1Score && this.monitor.players[0]) {
      this.playerOneText.text = `${this.monitor.players[0].username} : ${player1Score}`
    }
    if (player2Score && this.monitor.players[1]) {
      this.playerTwoText.text = `${this.monitor.players[1].username} : ${player2Score}`
    }
    if (this.monitor.players.length <= 1) {
      this.playerTwoText.text = 'No opponent'
    }
    // color them according the winner
    if (player1Score > player2Score) {
      this.playerOneText.setStyle({ color: '#00ff00' })
      this.playerTwoText.setStyle({ color: '#ff0000' })
    } else if (player1Score < player2Score) {
      this.playerOneText.setStyle({ color: '#ff0000' })
      this.playerTwoText.setStyle({ color: '#00ff00' })
    } else {
      this.playerOneText.setStyle({ color: '#ffffff' })
      this.playerTwoText.setStyle({ color: '#ffffff' })
    }
  }
}

class MenuSectionBox extends GameObjects.Container {
  private visibleSection: boolean = false

  constructor(
    public sectionType: MenuSection,
    scene: Menu,
    position: { x: number; y: number }
  ) {
    super(scene, position.x, position.y)
    this.setVisible(false).setActive(false)
  }

  get isVisible() {
    return this.visibleSection
  }
  set isVisible(status: boolean) {
    this.visibleSection = status
    this.setVisible(status).setActive(status)
  }

  updateSection(currentSection: MenuSection) {
    this.isVisible = this.sectionType === currentSection
  }
}
