import { Module } from '@nestjs/common';
import { UsersModule } from '../users/users.module';
import { ChatService } from './chat.service';
import { ChatController } from './chat.controller';
import { ChatRepository } from './chat.repository';
import { NotificationsModule } from '../notifications/notifications.module';
import { ChatGateway } from './chat.gateway';
import { MessageController } from './message.controller';
import { MessageService } from './message.service';
import { MessageRepository } from './message.repository';
import { JwtModule } from '@nestjs/jwt';

@Module({
  imports: [
    JwtModule.register({
      secret: process.env.JWT_SECRET,
    }),
    UsersModule,
    NotificationsModule,
  ],
  providers: [
    ChatRepository,
    ChatService,
    ChatGateway,
    MessageRepository,
    MessageService,
  ],
  controllers: [ChatController, MessageController],
  exports: [ChatService, MessageService],
})
export class MessagesModule {}
