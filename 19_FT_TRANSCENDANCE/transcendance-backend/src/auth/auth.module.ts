import { Module } from '@nestjs/common';
import { AuthController } from './auth.controller';
import { AuthService } from './auth.service';
import { PassportModule } from '@nestjs/passport';
import { JtwStrategy } from './strategies';
import { JwtModule } from '@nestjs/jwt';
import { UsersModule } from '../users/users.module';
import { GoogleStrategy } from './strategies/google.strategy';
import { LocalStrategy } from './strategies/local.strategy';
import { Strategy42 } from './strategies/42.strategy';
import { ConfigModule } from '@nestjs/config';
import { StatusGateway } from './status.gateway';

@Module({
  imports: [
    PassportModule,
    JwtModule.register({
      secret: process.env.JWT_SECRET,
    }),
    UsersModule,
  ],
  controllers: [AuthController],
  providers: [
    AuthService,
    LocalStrategy,
    JtwStrategy,
    GoogleStrategy,
    Strategy42,
    ConfigModule,
    StatusGateway,
  ],
  exports: [AuthService, JwtModule],
})
export class AuthModule {}
