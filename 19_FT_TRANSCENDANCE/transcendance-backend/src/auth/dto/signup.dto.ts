import { IsEmail, IsNotEmpty, IsString, Length } from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';

export class SignupDto {
  @ApiProperty()
  @Length(3, 20)
  @IsString()
  @IsNotEmpty()
  username: string;

  @ApiProperty()
  @IsEmail()
  @IsNotEmpty()
  email: string;

  @ApiProperty()
  @Length(6, 32)
  @IsString()
  @IsNotEmpty()
  password: string;

  @ApiProperty()
  @Length(3, 32)
  @IsString()
  @IsNotEmpty()
  firstName: string;

  @ApiProperty()
  @Length(3, 32)
  @IsString()
  @IsNotEmpty()
  lastName: string;
}
