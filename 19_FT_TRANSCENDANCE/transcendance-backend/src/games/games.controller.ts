import {
  ApiBearerAuth,
  ApiOperation,
  ApiResponse,
  ApiTags,
} from '@nestjs/swagger';
import {
  Body,
  Controller,
  Delete,
  Get,
  Param,
  ParseIntPipe,
  Post,
  Req,
  UseGuards,
} from '@nestjs/common';
import { GamesService } from './games.service';
import { CreateGameSessionDto } from './dto';
import { AuthenticatedGuard } from '../auth/guards';
import {
  GameSessionQResponse,
  GameSessionService,
  GameSessionShort,
} from './game-session.service';
import { GameMonitorState, WaitingGameSession } from './interfaces';
import { RequestWithUser } from '../users/users.controller';

@ApiTags('Game')
@Controller('game')
export class GamesController {
  constructor(
    private gameSessionService: GameSessionService,
    private gamesService: GamesService,
  ) {}

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Post('start')
  @ApiOperation({ summary: 'Start a new game session' })
  @ApiResponse({
    status: 200,
    description: 'Game session started successfully.',
  })
  async startGameSession(
    @Body() data: CreateGameSessionDto,
    @Req() req: RequestWithUser,
  ): Promise<GameSessionShort | WaitingGameSession | GameSessionQResponse> {
    const user = req.user;
    if (data.againstBot) {
      return this.gameSessionService.startGameSessionAgainstBot(data, user);
    } else if (data.opponent) {
      return this.gameSessionService.prepareOpponentGame(data, user);
    }
    return this.gameSessionService.prepareQueListGame(user);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('game-state/:gameId')
  @ApiOperation({ summary: 'Get a game session state' })
  @ApiResponse({
    status: 200,
    description: 'Game session state retrieved successfully.',
  })
  async getGameSessionState(
    @Param('gameId', ParseIntPipe) gameId: number,
  ): Promise<GameMonitorState> {
    return this.gameSessionService.gameSessionState(gameId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Post('accept-invitation')
  @ApiOperation({ summary: 'Accept Invitation to a game' })
  @ApiResponse({
    status: 200,
    description: 'Accepted the invitation successfully.',
  })
  async acceptInvitation(
    @Req() req: RequestWithUser,
    @Body() { challengeId }: { challengeId: number },
  ): Promise<GameSessionShort> {
    const user = req.user;
    return this.gameSessionService.acceptGameChallengeInvite(challengeId, user);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('is-valid-challenge/:challengeId')
  @ApiOperation({ summary: 'Check if a challenge is still valid' })
  @ApiResponse({
    status: 200,
    description: 'Returned the validity of the challenge successfully.',
  })
  async isValidChallenge(
    @Param('challengeId', ParseIntPipe) challengeId: number,
  ) {
    return this.gameSessionService.isValidChallenge(challengeId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Delete('/reject-invitation')
  @ApiOperation({ summary: 'Reject Challenge to a Game' })
  @ApiResponse({
    status: 200,
    description: 'Rejected the invitation successfully.',
  })
  async rejectInvitation(
    @Req() req: RequestWithUser,
    @Body() { challengeId }: { challengeId: number },
  ) {
    const user = req.user;
    return this.gameSessionService.rejectGameChallengeInvite(challengeId, user);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('quit-waiting-queue')
  @ApiOperation({ summary: 'Quit waiting queue' })
  async quitWaitingQueue(@Req() req: RequestWithUser) {
    const user = req.user;
    return this.gameSessionService.quitWaitingRoom(user);
  }
  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('show-waiting-queue')
  @ApiOperation({ summary: 'Show waiting queue' })
  async showWaitingQueue(@Req() req: RequestWithUser) {
    return this.gameSessionService.showWaitingRoom();
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('watch-game/:gameId')
  @ApiOperation({ summary: 'Watch a game' })
  @ApiResponse({
    status: 200,
    description: 'Added to game session observers successfully.',
  })
  async watchGame(
    @Req() req: RequestWithUser,
    @Param('gameId', ParseIntPipe) gameId: number,
  ): Promise<GameSessionShort> {
    return this.gameSessionService.addViewerToGameSessionHttp(gameId, req.user);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('is-someone-in-queue')
  @ApiOperation({ summary: 'Check if someone is in queue' })
  @ApiResponse({
    status: 200,
    description: 'Checked if someone is in queue successfully.',
  })
  async isSomeoneInQueue(): Promise<boolean> {
    return this.gameSessionService.isSomeoneWaitingForAnOpponent();
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('/status/:userId')
  @ApiOperation({ summary: 'Get the gaming status of a user' })
  @ApiResponse({
    status: 200,
    description: 'Retrieved the status successfully.',
  })
  async getUserStatus(@Param('userId', ParseIntPipe) userId: number): Promise<{
    status: 'playing' | 'inQueue' | 'free';
    gameSession?: GameSessionShort;
  }> {
    return this.gameSessionService.getUserGameStatus(userId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Post('status')
  @ApiOperation({ summary: 'Get the gaming status of many users' })
  @ApiResponse({
    status: 200,
    description: 'Retrieved the status successfully.',
  })
  async getUsersStatus(@Body() { userIds }: { userIds: number[] }): Promise<
    {
      status: 'playing' | 'inQueue' | 'free';
      gameSession?: GameSessionShort;
    }[]
  > {
    return this.gameSessionService.getUserGameStatusForMany(userIds);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('history/:userId')
  @ApiOperation({ summary: 'Get the game history of a user' })
  @ApiResponse({
    status: 200,
    description: 'Retrieved the game history successfully.',
  })
  async getUserGameHistory(@Param('userId', ParseIntPipe) userId: number) {
    return this.gamesService.getCompleteUserGameHistories(userId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('simple-history/:userId')
  @ApiOperation({ summary: 'Get the game simple history of a user' })
  @ApiResponse({
    status: 200,
    description: 'Retrieved the game history successfully.',
  })
  async getUserSimpleGameHistory(
    @Param('userId', ParseIntPipe) userId: number,
  ) {
    return this.gamesService.getUserGameHistories(userId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('sessions')
  @ApiOperation({ summary: 'Get all game sessions of the user not ended' })
  @ApiResponse({
    status: 200,
    description: 'Retrieved all game sessions successfully.',
  })
  async getAllGameSessions(
    @Req() req: RequestWithUser,
  ): Promise<GameSessionShort[] | string> {
    const user = req.user;
    return this.gameSessionService.getUserGameSessions(user.id);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('sessions/:gameId')
  @ApiOperation({ summary: 'Get a game session state by id' })
  @ApiResponse({
    status: 200,
    description: 'Retrieved the game session state successfully.',
  })
  async getGameSession(
    @Param('gameId', ParseIntPipe) gameId: number,
  ): Promise<GameMonitorState> {
    return this.gameSessionService.gameSessionState(gameId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Delete('sessions')
  @ApiOperation({ summary: 'Quit a game session' })
  @ApiResponse({
    status: 200,
    description:
      'Set a game session as Ended, or remove from participant successfully.',
  })
  async quitGameSession(
    @Req() req: RequestWithUser,
    @Body() { gameId }: { gameId: number },
  ) {
    const user = req.user;
    return this.gameSessionService.quitGameSession(gameId, user.id);
  }
}
