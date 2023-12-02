import { PassportStrategy } from '@nestjs/passport';
import { ExtractJwt, Strategy } from 'passport-jwt';
import { AuthService, JwtPayload } from '../auth.service';
import { Injectable } from '@nestjs/common';
import * as process from 'process';

@Injectable()
export class JtwStrategy extends PassportStrategy(Strategy, 'jwt') {
  constructor(private readonly authService: AuthService) {
    super({
      jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
      secretOrKey: process.env.JWT_SECRET,
      ignoreExpiration: false,
    });
  }

  // called when user is already logged, and we want to get his data
  async validate(payload: JwtPayload) {
    const { userId, sessionId } = payload.sub;
    return await this.authService.getUserFromJwt(userId, sessionId);
  }
}
