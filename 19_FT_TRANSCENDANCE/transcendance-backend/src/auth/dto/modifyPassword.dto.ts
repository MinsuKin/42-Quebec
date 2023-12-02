import { IsNotEmpty, IsString, Length } from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';

export class UpdatePasswordDto {
  @ApiProperty()
  @Length(6, 32)
  @IsString()
  @IsNotEmpty()
  currentPassword: string;
  @ApiProperty()
  @Length(6, 32)
  @IsString()
  @IsNotEmpty()
  newPassword: string;
  @ApiProperty()
  @Length(6, 32)
  @IsString()
  @IsNotEmpty()
  confirmPassword: string;
}
