import { ApiProperty } from '@nestjs/swagger';
import { ProfileDto } from './profile.dto';
import { SessionDto } from './session.dto';

enum Role {
  USER = 'USER',
  // Include other roles here
}

export class UserDto {
  @ApiProperty()
  id: number;

  @ApiProperty()
  username: string;

  @ApiProperty()
  email: string;

  @ApiProperty({ enum: Role })
  role: Role;

  @ApiProperty({ type: () => ProfileDto })
  profile?: ProfileDto;

  @ApiProperty({ type: () => [SessionDto] })
  sessions?: SessionDto[];

  // Include definitions for other types, etc. if needed.

  @ApiProperty()
  googleId?: string;

  @ApiProperty()
  facebookId?: string;

  @ApiProperty()
  api42Id?: string;

  @ApiProperty()
  twoFactorSecret?: string;

  @ApiProperty()
  twoFactorEnabled: boolean;

  @ApiProperty()
  createdAt: Date;

  @ApiProperty()
  updatedAt: Date;
}
