import { Injectable } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { Profile, Strategy, VerifyCallback } from 'passport-42';
import { AuthService } from '../auth.service';
import { OauthData } from '../interfaces';

@Injectable()
export class Strategy42 extends PassportStrategy(Strategy, '42') {
  constructor(private authService: AuthService) {
    const callback = 'https://' + process.env.URL + '/api/auth/42/callback';
    super({
      clientID: process.env.API42_CLIENT_ID,
      clientSecret: process.env.API42_CLIENT_SECRET,
      callbackURL: callback,
    });
  }

  async validate(
    accessToken: string,
    refreshToken: string,
    profile: Profile,
    done: VerifyCallback,
  ): Promise<any> {
    const { id, emails, name, _json } = profile;
    // generate a username based on the 42 profile, will only be used if the user doesn't have a username yet
    const generatedUsername = `42-${name.givenName}-${name.familyName}`;
    // transform the 42 profile into our OauthData interface
    const data: OauthData = {
      id,
      email: emails[0].value,
      username: generatedUsername,
      profile: {
        firstName: name.givenName,
        lastName: name.familyName,
        avatar: _json.image.link,
      },
      from: '42',
      data: {
        accessToken,
        refreshToken,
      },
    };
    const user = await this.authService.createOrFindUserWithOauthData(data);
    done(null, user);
  }
}
