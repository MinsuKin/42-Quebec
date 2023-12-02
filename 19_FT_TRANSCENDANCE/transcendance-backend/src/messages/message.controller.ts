import {
  Controller,
  Post,
  Get,
  Body,
  Param,
  Query,
  UseGuards,
  Req,
  ParseIntPipe,
} from '@nestjs/common';
import { MessageService } from './message.service';
import { CreateMessageDto } from './dto';
import { PrivateMessage } from '@prisma/client';
import { AuthenticatedGuard } from '../auth/guards';
import { UserWithoutSensitiveInfo } from '../users/users.service';
import { ApiTags } from '@nestjs/swagger';
import { RequestWithUser } from '../users/users.controller';

@ApiTags('PrivateMessagesActions')
@Controller('messages')
export class MessageController {
  constructor(private readonly messageService: MessageService) {}

  @UseGuards(AuthenticatedGuard)
  @Post()
  async createPrivateMessage(
    @Body() createMessageDto: CreateMessageDto,
    @Req() req: RequestWithUser,
  ): Promise<PrivateMessage> {
    return this.messageService.createPrivateMessage(
      createMessageDto,
      req.user.id,
    );
  }
  @UseGuards(AuthenticatedGuard)
  @Get()
  async getUniqueConversations(
    @Req() req: RequestWithUser,
  ): Promise<UserWithoutSensitiveInfo[]> {
    return this.messageService.getUniqueConversations(req.user.id);
  }

  @UseGuards(AuthenticatedGuard)
  @Get('/:userTwoId')
  async getPrivateMessages(
    @Param('userTwoId', ParseIntPipe) userTwoId: number,
    @Query('skip', ParseIntPipe) skip: number,
    @Query('take', ParseIntPipe) take: number,
    @Req() req: RequestWithUser,
  ): Promise<PrivateMessage[]> {
    return this.messageService.getPrivateMessages(req.user.id, userTwoId, {
      skip,
      take,
    });
  }
}
