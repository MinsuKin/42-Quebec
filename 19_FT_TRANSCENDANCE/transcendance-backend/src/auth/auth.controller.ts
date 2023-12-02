import {
  Body,
  Controller,
  Get,
  HttpCode,
  Post,
  Redirect,
  Req,
  Request,
  Res,
  Response,
  UnauthorizedException,
  UseGuards,
} from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
import { AuthService } from './auth.service';
import { LoginDataDto, LoginDto, RefreshDataDto, SignupDto } from './dto';
import {
  ApiBearerAuth,
  ApiCookieAuth,
  ApiOperation,
  ApiResponse,
  ApiTags,
} from '@nestjs/swagger';
import { LocalAuthGuard } from './guards/local-auth.guard';
import { AuthenticatedGuard } from './guards';
import { ILoginData } from './interfaces';
import { UsersService } from '../users/users.service';
import { TwoFaDto } from './dto/twoFa.dto';
import { UpdatePasswordDto } from './dto/modifyPassword.dto';
import { UpdateUserInfoDto } from './dto/updateUserInfo.dto';
import { RequestWithUser } from '../users/users.controller';

@ApiTags('Authentication')
@Controller('auth')
export class AuthController {
  constructor(
    private authService: AuthService,
    private usersService: UsersService,
  ) {}

  @UseGuards(LocalAuthGuard)
  @Post('login')
  @ApiOperation({
    summary: 'login the user',
    description: `
      - send access token and user info: { accessToken, user }
      - If the user is not found, will return a 401 status code
    `,
  })
  @ApiResponse({
    status: 200,
    description: `
    - return the jwt access token and user data
    - create a new session in the database
    - create a new refresh token in the cookies
    `,
    type: LoginDataDto,
  })
  login(
    @Request() req,
    @Response({ passthrough: true }) res,
    @Body() loginDto: LoginDto,
  ) {
    return this.authService.signInLocalUser(req, res, loginDto);
  }

  @Post('signup')
  @ApiOperation({
    summary: 'manually create an account',
    description: `
      - send access token, and user info: { accessToken, user }
      - if the user already exists, will return a 403 status code
    `,
  })
  @ApiResponse({
    status: 200,
    description: `
    - return the jwt access token and user data
    - create a new session in the database
    - create a REFRESH_TOKEN in the cookies
    `,
    type: LoginDataDto,
  })
  async signup(
    @Request() req,
    @Response({ passthrough: true }) res,
    @Body() signUpDto: SignupDto,
  ): Promise<ILoginData> {
    return this.authService.signUpLocal(req, res, signUpDto);
  }

  @Get('refresh')
  @ApiCookieAuth('REFRESH_TOKEN')
  @ApiOperation({
    summary: 'refresh access token',
    description: `
      - send a string of the new access token
      - update the database session with the new refresh token and the cookie
      - it use the refresh token in the cookies to get the session
      - if the REFRESH_TOKEN in cookies is invalid, will return a 401
    `,
  })
  @ApiResponse({
    status: 200,
    type: RefreshDataDto,
    description: 'return the access token',
  })
  async refresh(
    @Request() req,
    @Response({ passthrough: true }) res,
  ): Promise<{ accessToken: string }> {
    const refreshToken = req.cookies['REFRESH_TOKEN'] ?? '';
    return this.authService.refreshAccessToken(refreshToken, res);
  }

  @Get('logout')
  @ApiOperation({
    summary: 'logout the user and destroy session',
    description: `
      - use access token, check in the cookies for the refresh token
      - will destroy the session and return a 200 status code
      - if the token is valid, but the session is not found, will return a 401 status code
    `,
  })
  @ApiResponse({ status: 200, description: 'logout successful' })
  async logout(
    @Request() req,
    @Response({ passthrough: true }) res,
  ): Promise<{ message: string }> {
    const refreshToken = req.cookies['REFRESH_TOKEN'] ?? '';
    return this.authService.logOut(refreshToken, res);
  }

  // Google auth
  @Get('google')
  @ApiOperation({
    summary: 'Google auth entry request route',
    description: 'Will make a call to google, and redirect',
  })
  @ApiResponse({
    status: 302,
    description: 'redirection to auth callback for google',
  })
  @UseGuards(AuthGuard('google'))
  // eslint-disable-next-line @typescript-eslint/no-empty-function
  googleLogin() {}

  @Redirect()
  @Get('google/callback')
  @ApiOperation({
    summary: 'Google Auth callback route',
    description: `
      - Will receive tokens from google
      - Profile data will be load and user found or created
    `,
  })
  @ApiResponse({
    status: 200,
    description: `
    - return the jwt access token and user data
    - create a new session in the database
    - create a REFRESH_TOKEN in the cookies
    `,
    type: LoginDataDto,
  })
  @UseGuards(AuthGuard('google'))
  async googleLoginCallback(
    @Request() req,
    @Response({ passthrough: true }) res,
  ) {
    const loginData = await this.authService.signInWithOauth(
      req,
      res,
      req.user,
    );
    const localUrl: string = process.env.URL;
    return {
      url: `https://${localUrl}/auth/oauth-auth?token=${loginData.accessToken}`,
      statusCode: 302,
    };
  }

  // 42 Auth
  @Get('42')
  @ApiOperation({
    summary: '42 auth entry request route',
    description: 'Will make a call to4 2, and redirect',
  })
  @ApiResponse({
    status: 302,
    description: 'redirection to auth callback for 42',
  })
  @UseGuards(AuthGuard('42'))
  Login42() {
    // empty
  }

  @Redirect()
  @Get('42/callback')
  @UseGuards(AuthGuard('42'))
  @ApiOperation({
    summary: '42 Auth callback route',
    description: `
      - Will receive tokens from 42
      - Profile data will be load and user found or created
    `,
  })
  @ApiResponse({
    status: 200,
    description: `
    - return the jwt access token and user data
    - create a new session in the database
    - create a REFRESH_TOKEN in the cookies
    `,
    type: LoginDataDto,
  })
  async api42LoginCallback(
    @Request() req,
    @Response({ passthrough: true }) res,
  ) {
    const loginData = await this.authService.signInWithOauth(
      req,
      res,
      req.user,
    );
    const localUrl: string = process.env.URL;
    return {
      url: `https://${localUrl}/auth/oauth-auth?token=${loginData.accessToken}`,
      statusCode: 302,
    };
  }

  @Post('2fa/turn-on')
  @UseGuards(AuthenticatedGuard)
  @ApiBearerAuth()
  @ApiOperation({
    summary: 'Enables Google Authenticator 2FA',
    description: 'Set "two"twoFactorEnabled" to true,',
  })
  async turnOnTwoFactorAuthentication(@Req() request, @Body() body: TwoFaDto) {
    const isCodeValid = this.authService.isTwoFactorAuthenticationCodeValid(
      body.twoFactorAuthenticationCode,
      request.user,
    );
    if (!isCodeValid) {
      throw new UnauthorizedException('Wrong authentication code');
    }

    await this.usersService.turnOnTwoFactorAuthentication(request.user.id);
  }

  @Post('2fa/authenticate')
  @HttpCode(200)
  @UseGuards(AuthenticatedGuard)
  @ApiBearerAuth()
  @ApiOperation({
    summary: 'Verify Google Authenticator 2FA code',
    description:
      'code is valid => return true | code is not valid => Exception',
  })
  async authenticate(@Request() request, @Body() body) {
    const isCodeValid = this.authService.isTwoFactorAuthenticationCodeValid(
      body.twoFactorAuthenticationCode,
      request.user,
    );

    if (!isCodeValid) {
      throw new UnauthorizedException('Wrong authentication code');
    }

    return true;
  }

  @Post('2fa/generate')
  @UseGuards(AuthenticatedGuard)
  @ApiBearerAuth()
  @ApiOperation({
    summary: 'Generates QRcode for Google Authenticator 2FA registry',
    description: 'Set "twoFactorSecret"',
  })
  async register(@Res() response, @Req() request) {
    const { otpAuthUrl } =
      await this.authService.generateTwoFactorAuthenticationSecret(
        request.user,
      );

    return response.json(
      await this.authService.generateQrCodeDataURL(otpAuthUrl),
    );
  }

  @Post('2fa/turn-off')
  @UseGuards(AuthenticatedGuard)
  @ApiBearerAuth()
  @ApiOperation({
    summary: 'Disable 2FA',
    description: 'Set "two"twoFactorEnabled" to false,',
  })
  async turnOffTwoFactorAuthentication(@Req() request: RequestWithUser) {
    return this.usersService.turnOffTwoFactorAuthentication(request.user.id);
  }

  @UseGuards(AuthenticatedGuard)
  @ApiBearerAuth()
  @ApiOperation({
    summary: 'Return my info',
  })
  @Get('me')
  async getMe(@Request() request: RequestWithUser) {
    return request.user;
  }

  @Post('updatePassword')
  @UseGuards(AuthenticatedGuard)
  @ApiBearerAuth()
  @ApiOperation({
    summary: 'modify User password to a new one',
    description: 'return true when it is done',
  })
  async modifyPassword(
    @Req() request: RequestWithUser,
    @Body() body: UpdatePasswordDto,
  ) {
    return this.authService.modifyPassword(request.user, body);
  }

  @Post('updateInfo')
  @UseGuards(AuthenticatedGuard)
  @ApiBearerAuth()
  @ApiOperation({
    summary: 'modify User info, firstName, lastName and biography',
    description: 'return user',
  })
  async modifyUserInfo(
    @Req() request: RequestWithUser,
    @Body() body: UpdateUserInfoDto,
  ) {
    return this.authService.updateUserInfo(request.user, body);
  }

  @UseGuards(AuthenticatedGuard)
  @ApiBearerAuth()
  @ApiOperation({
    summary: 'Return last user sessions',
  })
  @Get('sessions')
  async getLastSessions(@Request() request: RequestWithUser) {
    return this.authService.getLastSessions(request.user.id);
  }
}
