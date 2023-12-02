import { Module } from '@nestjs/common';
import { UsersService } from './users.service';
import { UsersController } from './users.controller';
import { PrismaModule } from '../prisma/prisma.module';
import { UsersRepository } from './users.repository';
import { FriendsModule } from '../friends/friends.module';
import { SchoolNetworkService } from './schoolNetwork.service';

@Module({
  imports: [PrismaModule, FriendsModule],
  providers: [UsersRepository, UsersService, SchoolNetworkService],
  controllers: [UsersController],
  exports: [UsersService],
})
export class UsersModule {}
