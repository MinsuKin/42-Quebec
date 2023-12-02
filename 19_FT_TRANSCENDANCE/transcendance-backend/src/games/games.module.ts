import { Module } from '@nestjs/common';
import { GamesService } from './games.service';
import { PrismaModule } from '../prisma/prisma.module';
import { GamesRepository } from './games.repository';
import { GamesController } from './games.controller';
import { NotificationsModule } from '../notifications/notifications.module';
import { UsersModule } from '../users/users.module';
import { GameSessionService } from './game-session.service';
import { GameRealtimeService } from './gameRealtime.service';
import { GameGateway } from './game.gateway';
import { JwtModule } from '@nestjs/jwt';

@Module({
  imports: [
    JwtModule.register({
      secret: process.env.JWT_SECRET,
    }),
    PrismaModule,
    UsersModule,
    NotificationsModule,
  ],
  providers: [
    GamesRepository,
    GamesService,
    GameSessionService,
    GameRealtimeService,
    GameGateway,
  ],
  controllers: [GamesController],
  exports: [GamesService],
})
export class GamesModule {}
