import { ApiBearerAuth, ApiOperation, ApiTags } from '@nestjs/swagger';
import {
  Controller,
  Delete,
  Get,
  ParseIntPipe,
  Patch,
  Query,
  Req,
} from '@nestjs/common';
import { ChatService } from './chat.service';
import {
  CreateRoomDto,
  JoinRoomDto,
  RemoveFromRoomDto,
  UpdatePasswordDto,
  UpdateRoomInfoDto,
  UpdateRoleDto,
} from './dto';
import { AuthenticatedGuard } from '../auth/guards';
import { Body, Post, Param, UseGuards } from '@nestjs/common';
import { RequestWithUser } from '../users/users.controller';
import { ChatRoomMessage } from '@prisma/client';

@ApiTags('ChatActions')
@Controller('chat')
export class ChatController {
  constructor(private service: ChatService) {}

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Post('create-room')
  async createRoom(
    @Req() req: RequestWithUser,
    @Body() createRoomDto: CreateRoomDto,
  ) {
    return this.service.createRoom(createRoomDto);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Post('join-room/:roomId')
  async joinRoom(
    @Req() req: RequestWithUser,
    @Param('roomId', ParseIntPipe) roomId: number,
    @Body() joinRoomDto: JoinRoomDto,
  ) {
    // const actorId = req.user.id; // replace with actual actorId
    return this.service.addUserToARoom({
      roomId,
      ...joinRoomDto,
    });
  }

  @UseGuards(AuthenticatedGuard)
  @Get('messages/:roomId')
  @ApiOperation({})
  async getRoomMessage(
    @Req() req: RequestWithUser,
    @Param('roomId', ParseIntPipe) roomId: number,
    @Query('skip', ParseIntPipe) skip: number,
    @Query('take', ParseIntPipe) take: number,
  ): Promise<ChatRoomMessage[]> {
    return this.service.getRoomMessages(roomId, req.user.id, {
      skip,
      take,
    });
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Patch('update-password')
  async updateRoomPassword(
    @Req() req: RequestWithUser,
    @Body() updatePasswordDto: UpdatePasswordDto,
  ) {
    const userId = req.user.id;
    return this.service.updateRoomPassword(updatePasswordDto, userId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Patch('update-room-info')
  async updateRoomInfo(
    @Req() req: RequestWithUser,
    @Body() updateRoomInfoDto: UpdateRoomInfoDto,
  ) {
    const userId = req.user.id;
    return this.service.updateRoomInfo(updateRoomInfoDto, userId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('leave-room/:roomId')
  async leaveRoom(
    @Req() req: RequestWithUser,
    @Param('roomId', ParseIntPipe) roomId: number,
  ) {
    return this.service.removeMyselfFromRoom(roomId, req.user.id);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Post('remove-member/:roomId')
  async removeFromRoom(
    @Req() req: RequestWithUser,
    @Body() deleteFromRoomDto: RemoveFromRoomDto,
  ) {
    const { roomId, userId } = deleteFromRoomDto;
    return this.service.removeUserFromRoom(roomId, userId, req.user.id);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Delete('delete-room/:roomId')
  async deleteRoom(
    @Req() req: RequestWithUser,
    @Param('roomId', ParseIntPipe) roomId: number,
  ) {
    const userId = req.user.id;
    return this.service.deleteRoom(roomId, userId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @Get('public')
  async getPublicRooms() {
    return this.service.getPublicRooms();
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @ApiOperation({ summary: 'Get all rooms where user is a member' })
  @Get('rooms')
  async getRooms(@Req() req: RequestWithUser) {
    const userId = req.user.id;
    return this.service.getUserRooms(userId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @ApiOperation({
    summary: 'Get current role if member of room or null if not a member',
    description: 'state: (true or false) if member and,  role, type of room',
  })
  @Get('room-role/:roomId')
  async getRoomRole(
    @Req() req: RequestWithUser,
    @Param('roomId', ParseIntPipe) roomId: number,
  ) {
    const userId = req.user.id;
    return this.service.checkUserMembership(roomId, userId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @ApiOperation({
    summary:
      'Get all room members, can failed if user not a member, for private room',
    description: 'return array of members',
  })
  @Get('room/:roomId')
  async getRoomInfo(
    @Req() req: RequestWithUser,
    @Param('roomId', ParseIntPipe) roomId: number,
  ) {
    const userId = req.user.id;
    return this.service.getRoomMembers(roomId, userId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @ApiOperation({
    summary: 'update the role of a user',
  })
  @Post('promote/:roomId')
  async changeMemberRole(
    @Req() req: RequestWithUser,
    @Param('roomId', ParseIntPipe) roomId: number,
    @Body() updateMemberDto: UpdateRoleDto,
  ) {
    const actorId = req.user.id;
    return this.service.changeMemberRole(roomId, updateMemberDto, actorId);
  }

  @ApiBearerAuth()
  @UseGuards(AuthenticatedGuard)
  @ApiOperation({
    summary: 'send an invitation to rejoin the room',
  })
  @Post('invite')
  async inviteUserToRoom(
    @Req() req: RequestWithUser,
    @Body() inviteUserDto: { userId: number; roomId: number },
  ) {
    const { userId, roomId } = inviteUserDto;
    return this.service.inviteUserToRoom(roomId, userId, req.user);
  }
}
