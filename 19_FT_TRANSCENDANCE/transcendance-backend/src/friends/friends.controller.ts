import {
  Controller,
  Delete,
  Get,
  Param,
  ParseIntPipe,
  Post,
  Request,
  UseGuards,
} from '@nestjs/common';
import { FriendsService } from './friends.service';
import { ApiBearerAuth, ApiOperation } from '@nestjs/swagger';
import { AuthenticatedGuard } from '../auth/guards';
import { RequestWithUser } from '../users/users.controller';

@Controller('friends')
export class FriendsController {
  constructor(private readonly friendsService: FriendsService) {}

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get()
  @ApiOperation({
    summary: 'Retrieve all friends of connected user',
  })
  async getFriends(@Request() req: RequestWithUser) {
    return await this.friendsService.getFriends(req.user.id);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('check/:id')
  @ApiOperation({
    summary: 'Check if a user is a friend',
  })
  async checkFriend(
    @Request() req: RequestWithUser,
    @Param('id', ParseIntPipe) id: number,
  ) {
    return await this.friendsService.checkFriend(req.user.id, id);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('sent')
  @ApiOperation({
    summary: 'Retrieve all sent friends requests',
  })
  async getSentFriendRequests(@Request() req: RequestWithUser) {
    return await this.friendsService.getSentFriendRequests(req.user.id);
  }
  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('received')
  @ApiOperation({
    summary: 'Retrieve all received friends requests',
  })
  async getReceivedFriendRequests(@Request() req: RequestWithUser) {
    return await this.friendsService.getReceivedFriendRequests(req.user.id);
  }
  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Delete(':id')
  @ApiOperation({
    summary: 'Remove a friend',
  })
  async removeFriend(
    @Request() req: RequestWithUser,
    @Param('id', ParseIntPipe) id: number,
  ) {
    return this.friendsService.removeFriend(req.user, id);
  }
  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Post('request-friendship-with/:id')
  @ApiOperation({
    summary: 'send a friend request',
  })
  async addFriendRequest(
    @Request() req: RequestWithUser,
    @Param('id', ParseIntPipe) id: number,
  ) {
    return this.friendsService.addFriendRequest(req.user, id);
  }
  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Delete('sent/:id')
  @ApiOperation({
    summary: 'Cancel friend request I SENT',
  })
  async cancelFriendRequest(@Param('id', ParseIntPipe) requestId: number) {
    return await this.friendsService.cancelFriendRequest(requestId);
  }
  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Post('approve-friendship-request-for/:id')
  @ApiOperation({
    summary: 'Accept friend request I RECEIVED',
  })
  async approveFriendRequest(
    @Request() req: RequestWithUser,
    @Param('id', ParseIntPipe) id: number,
  ) {
    return await this.friendsService.approveFriendRequest(req.user, id);
  }
  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Delete('reject/:id')
  @ApiOperation({
    summary: 'Decline friend request I RECEIVED',
  })
  async rejectFriendRequest(
    @Request() req: RequestWithUser,
    @Param('id', ParseIntPipe) id: number,
  ) {
    return await this.friendsService.rejectFriendRequest(req.user, id);
  }
}
