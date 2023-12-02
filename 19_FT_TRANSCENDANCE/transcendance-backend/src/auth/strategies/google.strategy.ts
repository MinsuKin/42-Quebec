import { Injectable } from '@nestjs/common';
import { PassportStrategy } from '@nestjs/passport';
import { Strategy, VerifyCallback } from 'passport-google-oauth20';
import { AuthService } from '../auth.service';
import { OauthData } from '../interfaces';

interface GoogleProfile {
  id: string;
  displayName: string;
  name: { familyName: string; givenName: string };
  emails: Array<{ value: string; verified: boolean }>;
  photos: Array<{ value: string }>;
  provider: string;
  _raw: string;
  _json: {
    sub: string;
    name: string;
    given_name: string;
    family_name: string;
    picture: string;
    email: string;
    email_verified: boolean;
    locale: string;
  };
}

@Injectable()
export class GoogleStrategy extends PassportStrategy(Strategy, 'google') {
  constructor(private authService: AuthService) {
    super({
      clientID: process.env.GOOGLE_CLIENT_ID,
      clientSecret: process.env.GOOGLE_CLIENT_SECRET,
      callbackURL: process.env.BACKEND_URL + '/auth/google/callback',
      scope: ['email', 'profile'],
    });
  }

  async validate(
    accessToken: string,
    refreshToken: string,
    profile: GoogleProfile,
    done: VerifyCallback,
  ): Promise<any> {
    const { id, emails, name, photos } = profile;
    // generate a username based on the Google profile, will only be used if the user doesn't have a username yet
    const generatedUsername = `g-${name.givenName}-${name.familyName}`;

    // transform the Google profile into our OauthData interface
    const data: OauthData = {
      id,
      email: emails[0].value,
      username: generatedUsername,
      profile: {
        firstName: name.givenName,
        lastName: name.familyName,
        avatar: photos[0].value,
      },
      from: 'google',
      data: {
        accessToken,
        refreshToken,
      },
    };
    const user = await this.authService.createOrFindUserWithOauthData(data);
    done(null, user);
  }
}
