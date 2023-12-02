import { IsNotEmpty, IsString, Length } from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';

export class TwoFaDto {
  @ApiProperty()
  @IsString()
  @IsNotEmpty()
  twoFactorAuthenticationCode: string;
}
