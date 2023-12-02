import {
  ForbiddenException,
  Injectable,
  UnauthorizedException,
} from '@nestjs/common';
import { Status, User } from '@prisma/client';
import { JwtService } from '@nestjs/jwt';
import { PrismaService } from '../prisma/prisma.service';
import { LoginDto, SignupDto } from './dto';
import { Request, Response } from 'express';
import * as argon from 'argon2';
import { ILoginData, OauthData, Tokens } from './interfaces';
import { UsersService, UserWithData } from '../users/users.service';
import { authenticator } from 'otplib';
import { toDataURL } from 'qrcode';
import { UpdatePasswordDto } from './dto/modifyPassword.dto';
import { UpdateUserInfoDto } from './dto/updateUserInfo.dto';

export interface JwtPayload {
  email: string;
  sub: {
    userId: number;
    sessionId: number;
    needToPassTwoFactor: boolean;
  };
}

@Injectable()
export class AuthService {
  constructor(
    private readonly prisma: PrismaService,
    private jwtService: JwtService,
    private usersService: UsersService,
  ) {}

  async signUpLocal(
    req: Request,
    res: Response,
    signUpDto: SignupDto,
  ): Promise<ILoginData> {
    try {
      const userCreated = await this.usersService.createUserWithProfile({
        username: signUpDto.username,
        email: signUpDto.email,
        password: signUpDto.password, // will be hashed in user service layer
        name: signUpDto.firstName,
        lastName: signUpDto.lastName,
      });
      const user = await this.usersService.getUserWithData(userCreated);
      return await this.loginAndRefreshTokens(req, res, user);
    } catch (err) {
      if (err?.code === 'P2002' && err?.meta?.target) {
        throw new ForbiddenException(`${err.meta?.target} already exists`);
      } else {
        throw err;
      }
    }
  }

  async createOrFindUserWithOauthData(data: OauthData) {
    try {
      const findUser = await this.usersService.getUserWithData({
        email: data.email,
      });
      if (findUser) {
        if (findUser.googleId !== data.id && data.from === 'google') {
          return this.updateToAGoogleUser(findUser, data);
        } else if (findUser.api42Id !== data.id && data.from === '42') {
          return this.updateToA42User(findUser, data);
        }
        return findUser;
      }
      return this.usersService.createUserWithProfile({
        username: data.username,
        email: data.email,
        password: `oauth-${data.from}-${data.id}`,
        name: data.profile.firstName,
        lastName: data.profile.lastName,
        avatar: data.profile.avatar,
        provider: data.from,
        providerId: data.id,
        data: data.data,
      });
    } catch (err) {
      if (err?.code === 'P2002' && err?.meta?.target) {
        throw new ForbiddenException(`${err.meta?.target} already exists`);
      } else {
        throw err;
      }
    }
  }

  async signInLocalUser(
    req: Request,
    res: Response,
    loginDto: LoginDto,
  ): Promise<ILoginData> {
    const user = await this.usersService.getUserWithData({
      username: loginDto.username,
    });
    if (!user) {
      throw new UnauthorizedException('Invalid credentials');
    }
    const isValid = await argon.verify(user.password, loginDto.password);
    if (!isValid) {
      throw new UnauthorizedException('Invalid credentials, wrong password');
    }
    return this.loginAndRefreshTokens(req, res, user);
  }

  async signInWithOauth(
    req: Request,
    res: Response,
    user: User,
  ): Promise<ILoginData> {
    return this.loginAndRefreshTokens(req, res, user);
  }

  async logOut(refreshToken: string, res: Response) {
    try {
      if (refreshToken) {
        const isValid = this.jwtService.verify(refreshToken) as JwtPayload;
        if (!isValid) {
          throw new UnauthorizedException('Invalid credentials');
        }
        const { userId, sessionId } = isValid.sub;
        await this.destroySession(sessionId);
        this.destroyCookieForRefreshToken(res);
      } else {
        this.destroyCookieForRefreshToken(res);
      }
      return {
        message: 'Successfully logged out, bye bye',
      };
    } catch (err) {
      if (err?.code === 'P2025') {
        throw new UnauthorizedException('Invalid credentials');
      } else {
        throw err;
      }
    }
  }

  async loginAndRefreshTokens(
    req: Request,
    res: Response,
    user: User,
  ): Promise<ILoginData> {
    const { ip, userAgent } = this.getRequestInfo(req);
    const session = await this.usersService.createSession({
      user,
      token: 'jwt-signIn-token',
      ipAddress: ip,
      userAgent: userAgent,
      expiresAt: new Date(),
    });
    const needTwoFactor = user.twoFactorEnabled;
    const tokens = await this.getTokens(
      user.email,
      user.id,
      session.id,
      needTwoFactor,
    ); // for the first login we sent  token that contain a 2FA flag
    await this.refreshSession(session.id, tokens.refreshToken, res);
    const userWithoutPassword = this.usersService.removePassword(user);
    await this.usersService.changeStatus(user.id, Status.Online);
    return {
      accessToken: tokens.accessToken,
      user: userWithoutPassword,
    };
  }

  async refreshAccessToken(
    refreshToken: string,
    res: Response,
  ): Promise<{ accessToken: string }> {
    if (!refreshToken) {
      throw new UnauthorizedException('No refresh token found');
    }
    const isValid = this.jwtService.verify(refreshToken) as JwtPayload;
    if (!isValid) {
      throw new UnauthorizedException('Invalid credentials');
    }
    const { userId, sessionId } = isValid.sub;
    const user = await this.usersService.getUser({ id: userId });
    if (!user) {
      throw new UnauthorizedException('Invalid credentials');
    }
    const session = await this.usersService.getSessionById(sessionId);
    if (!session) {
      throw new UnauthorizedException('Invalid credentials, no session found');
    }
    const tokens = await this.getTokens(user.email, user.id, session.id);
    await this.refreshSession(session.id, tokens.refreshToken, res);
    return {
      accessToken: tokens.accessToken,
    };
  }

  async getUserFromJwt(
    userId: number,
    sessionId: number,
  ): Promise<UserWithData> {
    const user = await this.usersService.getUserWithData({ id: userId });
    if (!user) {
      throw new UnauthorizedException('Invalid credentials');
    }
    return user;
  }

  async modifyPassword(user: User, data: UpdatePasswordDto) {
    const isValid = await argon.verify(user.password, data.currentPassword);
    if (!isValid) {
      throw new UnauthorizedException('Invalid credentials, wrong password');
    }
    if (data.newPassword !== data.confirmPassword) {
      throw new ForbiddenException(
        'new password and confirm password mismatch',
      );
    }
    const hashedPassword = await argon.hash(data.newPassword);
    return this.usersService.updateUser({
      where: { id: user.id },
      data: { password: hashedPassword },
      include: {
        profile: true,
        blockedUsers: true,
        blockedFrom: true,
      },
    });
  }

  async updateUserInfo(user: User, data: UpdateUserInfoDto) {
    try {
      return this.usersService.updateUser({
        where: { id: user.id },
        data: {
          username: data.userName ?? user.username,
          profile: {
            update: {
              name: data.firstName,
              lastname: data.lastName,
              bio: data.bio,
            },
          },
        },
        include: {
          profile: true,
          blockedUsers: true,
          blockedFrom: true,
        },
      });
    } catch (err) {
      if (err?.code === 'P2002' && err?.meta?.target) {
        throw new ForbiddenException(`${err.meta?.target} already exists`);
      } else {
        throw err;
      }
    }
  }

  async getLastSessions(userId: number) {
    return this.usersService.getAllUserSessions({ userId, limit: 10 });
  }
  async refreshSession(sessionId: number, refreshToken: string, res: Response) {
    const data = this.jwtService.decode(refreshToken);
    const expiresAt = new Date((data as any).exp * 1000);
    await this.usersService.updateSession(sessionId, refreshToken, expiresAt);
    this.setCookieForRefreshToken(refreshToken, res);
  }

  async destroySession(sessionId: number) {
    await this.usersService.deleteSession({ id: sessionId });
  }

  setCookieForRefreshToken(refreshToken: string, res: Response) {
    res.cookie('REFRESH_TOKEN', refreshToken, {
      httpOnly: true,
      sameSite: 'lax',
    });
  }

  destroyCookieForRefreshToken(res: Response) {
    res.cookie('REFRESH_TOKEN', '', {
      httpOnly: true,
      sameSite: 'lax',
      expires: new Date(0),
    });
  }

  // build tokens and return them as a promise
  async getTokens(
    email: string,
    userId: number,
    sessionId: number,
    needToPassTwoFactor = false,
  ): Promise<Tokens> {
    const payload: JwtPayload = {
      email: email,
      sub: {
        userId: userId,
        sessionId: sessionId,
        needToPassTwoFactor,
      },
    };
    const tokens = await Promise.all([
      this.jwtService.signAsync(payload, { expiresIn: '12m' }), // 12 minutes
      this.jwtService.signAsync(payload, { expiresIn: '7d' }), // 7 days
    ]);

    return {
      accessToken: tokens[0],
      refreshToken: tokens[1],
    };
  }

  getRequestInfo(req: Request) {
    const ip = req.ip;
    const userAgent = req.get('user-agent');
    return {
      ip,
      userAgent,
    };
  }

  async generateTwoFactorAuthenticationSecret(user: User) {
    const secret = authenticator.generateSecret();
    const otpAuthUrl = authenticator.keyuri(user.email, 'FTMJR', secret);
    await this.usersService.setTwoFactorAuthenticationSecret(secret, user.id);
    return {
      secret,
      otpAuthUrl,
    };
  }

  async generateQrCodeDataURL(otpAuthUrl: string) {
    return toDataURL(otpAuthUrl);
  }

  async updateToAGoogleUser(findUser: User, data: OauthData) {
    if (findUser.googleId !== data.id && data.from === 'google') {
      await this.usersService.updateUserProviderId(
        findUser,
        data.from,
        data.id,
      );
      findUser.googleId = data.id;
    }
    return findUser;
  }

  async updateToA42User(findUser: User, data: OauthData) {
    if (findUser.api42Id !== data.id && data.from === '42') {
      await this.usersService.updateUserProviderId(
        findUser,
        data.from,
        data.id,
      );
      findUser.api42Id = data.id;
    }
    return findUser;
  }

  isTwoFactorAuthenticationCodeValid(
    twoFactorAuthenticationCode: string,
    user: User,
  ) {
    return authenticator.verify({
      token: twoFactorAuthenticationCode,
      secret: user.twoFactorSecret,
    });
  }

  canListenStatus(token: string, userId: number): boolean {
    try {
      const isValid = this.jwtService.verify(token) as JwtPayload;
      if (!isValid) {
        throw new UnauthorizedException('Invalid credentials');
      }
      // check if the user is the same as the one in the token
      if (isValid.sub.userId !== userId) {
        throw new UnauthorizedException('Invalid credentials');
      }
      return true;
    } catch (e) {
      return false;
    }
  }
}
