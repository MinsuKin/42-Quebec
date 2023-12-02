import { ApiProperty } from '@nestjs/swagger';
import { UserDto } from '../../users/dto';

export class LoginDataDto {
  @ApiProperty()
  accessToken: string;
  @ApiProperty({ type: () => UserDto })
  user: UserDto;
}
