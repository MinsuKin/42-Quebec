import { Module } from '@nestjs/common';
import { AuthModule } from './auth/auth.module';
import { PrismaModule } from './prisma/prisma.module';
import { GamesModule } from './games/games.module';
import { UsersModule } from './users/users.module';
import { MessagesModule } from './messages/messages.module';
import { CacheModule } from '@nestjs/cache-manager';
import { FilesModule } from './files/files.module';
import { FriendsModule } from './friends/friends.module';
import { NotificationsModule } from './notifications/notifications.module';

@Module({
  imports: [
    PrismaModule,
    UsersModule,
    NotificationsModule,
    AuthModule,
    MessagesModule,
    GamesModule,
    FriendsModule,
    FilesModule,
    CacheModule.register(),
  ],
  controllers: [],
  providers: [],
})
export class AppModule {}
