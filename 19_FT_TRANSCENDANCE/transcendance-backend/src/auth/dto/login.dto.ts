import { IsNotEmpty, IsString, Length } from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';

export class LoginDto {
  @ApiProperty()
  @Length(3, 20)
  @IsString()
  @IsNotEmpty()
  username: string;

  @ApiProperty()
  @Length(6, 32)
  @IsString()
  @IsNotEmpty()
  password: string;
}
