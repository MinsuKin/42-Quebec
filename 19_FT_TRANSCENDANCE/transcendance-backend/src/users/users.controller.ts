import {
  Body,
  ConflictException,
  Controller,
  Delete,
  Get,
  NotFoundException,
  Param,
  ParseIntPipe,
  Post,
  Query,
  Request,
  UseGuards,
} from '@nestjs/common';
import { UsersService, UserWithData } from './users.service';
import {
  ApiBearerAuth,
  ApiOperation,
  ApiResponse,
  ApiTags,
} from '@nestjs/swagger';
import { AuthenticatedGuard } from '../auth/guards';
import { PaginationQuery, SearchQuery } from './dto';
import * as express from 'express';

export type RequestWithUser = express.Request & { user: UserWithData };

@ApiTags('UserActions')
@Controller('users')
export class UsersController {
  constructor(private readonly usersService: UsersService) {}
  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get()
  @ApiOperation({
    summary: 'get all users',
    description: `
      - fetch all users from the database
      - but not blocked users
    `,
  })
  @ApiResponse({ status: 200, description: 'return an array of users' })
  getUsers(
    @Request() req: RequestWithUser,
    @Query() queryParams: PaginationQuery,
  ) {
    const skip: number = parseInt(queryParams.skip);
    const take: number = parseInt(queryParams.take);
    const id: number = req.user.id;
    return this.usersService.getUsers(
      {
        skip,
        take,
        include: {
          profile: true,
          sessions: false,
          gameHistories: true,
        },
        where: {
          OR: [
            { blockedUsers: { none: { blockedUserId: id } } }, // Users who have blocked the current user
            { blockedFrom: { none: { userId: id } } }, // Users who are blocked by the current user
          ],
        },
      },
      req.user,
    );
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('all')
  @ApiOperation({
    summary: 'get all users',
    description: `
      - fetch all users from the database
      - fetch even blocked users
    `,
  })
  @ApiResponse({ status: 200, description: 'return an array of users' })
  getAllUsers(
    @Request() req: RequestWithUser,
    @Query() queryParams: PaginationQuery,
  ) {
    const skip: number = parseInt(queryParams.skip);
    const take: number = parseInt(queryParams.take);
    const orderBy = queryParams.orderBy;
    return this.usersService.getAllUsers({
      skip,
      take,
      orderBy,
      include: { profile: true, sessions: false },
    });
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('profile/:id')
  @ApiOperation({
    summary: 'get a user profile',
    description: `
      - fetch a user profile from the database
    `,
  })
  @ApiResponse({ status: 200, description: 'return a user profile' })
  async getUserProfile(
    @Request() req: RequestWithUser,
    @Param('id', ParseIntPipe) id: number,
  ) {
    const users = await this.usersService.getUserProfile(req.user, id);
    if (!users) {
      throw new NotFoundException('User not found, or blocked');
    }
    return users[0];
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('short-profile/:id')
  @ApiOperation({
    summary: 'get a user short profile',
    description: `
      - fetch a user profile status and avatar info from the database
    `,
  })
  @ApiResponse({ status: 200, description: 'return a user short profile' })
  async getUserShortProfile(
    @Request() req: RequestWithUser,
    @Param('id', ParseIntPipe) id: number,
  ) {
    const profile = await this.usersService.getUserShortProfile(id);
    if (!profile) {
      throw new NotFoundException();
    }
    return profile;
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('block')
  @ApiOperation({
    summary: 'get all blocked users',
    description: `
      - fetch all blocked users from the database
    `,
  })
  @ApiResponse({ status: 200, description: 'return an array of blocked users' })
  async getBlockedUsers(@Request() req: RequestWithUser) {
    return await this.usersService.getBlockedUsers(req.user.id);
  }
  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Post('block/:id')
  @ApiOperation({
    summary: 'block a user',
    description: `
      - block a user
    `,
  })
  @ApiResponse({ status: 200, description: 'return the blocked user' })
  async blockUser(
    @Request() req: RequestWithUser,
    @Param('id', ParseIntPipe) id: number,
  ) {
    return await this.usersService.blockUser(req.user, id);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Delete('unblock/:id')
  @ApiOperation({
    summary: 'remove a user from blocked users',
    description: `
      - remove a user from the blocked list
    `,
  })
  @ApiResponse({ status: 200, description: 'return  the unblocked user' })
  unblockUser(
    @Request() req: RequestWithUser,
    @Param('id', ParseIntPipe) id: number,
  ) {
    return this.usersService.unblockUser(req.user, id);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('check-blocked/:id')
  @ApiOperation({
    summary: 'Check if a user is blocked',
    description: `
      - check if a user is blocked
    `,
  })
  async checkBlocked(
    @Request() req: RequestWithUser,
    @Param('id', ParseIntPipe) id: number,
  ) {
    return await this.usersService.checkBlocked(req.user.id, id);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Post('check-blocked')
  @ApiOperation({
    summary: 'Check blocked status for a list of users',
    description: `
      - return the blocked status for a list of users
    `,
  })
  async checkBlockedForGroup(
    @Request() req: RequestWithUser,
    @Body() { userIds }: { userIds: number[] },
  ) {
    return await this.usersService.checkBlockedForMany(req.user.id, userIds);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Post('username/:username')
  @ApiOperation({
    summary: 'update a user username',
    description: `
      -tries to update the username
    `,
  })
  @ApiResponse({ status: 200, description: 'return  the updated user' })
  updateUsername(
    @Request() req: RequestWithUser,
    @Param('username') username: string,
  ) {
    if (username.startsWith('42-')) {
      throw new ConflictException('Username starting with 42- not allowed!');
    }
    return this.usersService.updateUser({
      where: {
        id: req.user.id,
      },
      data: {
        username: username,
      },
    });
  }
  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('leaderboard')
  @ApiOperation({
    summary: 'Get users ordered by game wins',
  })
  @ApiResponse({ status: 200, description: 'return the users leaderboard' })
  async getUsersOrderedByWins(@Query() queryParams: PaginationQuery) {
    const skip: number = parseInt(queryParams.skip);
    const take: number = parseInt(queryParams.take);
    return await this.usersService.getUsersOrderedByWins({ skip, take });
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('stats')
  @ApiOperation({
    summary: 'Get App statistics',
  })
  async getStatistic() {
    return await this.usersService.getAppStatistics();
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('search')
  @ApiOperation({
    summary: 'Search for users',
  })
  async searchUsers(@Query() queryParams: SearchQuery) {
    const skip: number = parseInt(queryParams.skip) || 0;
    const take: number = parseInt(queryParams.take) || 10;
    return await this.usersService.searchUsers({
      query: queryParams.query,
      skip,
      take,
      orderBy: queryParams.orderBy,
    });
  }
}
