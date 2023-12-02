import { Injectable, UnauthorizedException } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { Strategy } from 'passport-local';
import { AuthService } from '../auth.service';
import * as argon from 'argon2';
import { UsersService } from '../../users/users.service';

@Injectable()
export class LocalStrategy extends PassportStrategy(Strategy) {
  constructor(
    private authService: AuthService,
    private usersService: UsersService,
  ) {
    super(); // config
  }
  async validate(username: string, password: string): Promise<any> {
    const user = await this.usersService.getUserWithData({
      username: username,
    });
    if (!user) {
      throw new UnauthorizedException('Invalid credentials');
    }
    const isValid = await argon.verify(user.password, password);
    if (!isValid) {
      throw new UnauthorizedException('Invalid credentials, wrong password');
    }
    return user;
  }
}
