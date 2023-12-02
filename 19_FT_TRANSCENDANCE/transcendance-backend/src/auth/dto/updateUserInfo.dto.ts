import { IsNotEmpty, IsOptional, IsString, Length } from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';

export class UpdateUserInfoDto {
  @ApiProperty()
  @Length(3, 20)
  @IsString()
  @IsOptional()
  userName?: string;
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
  @ApiProperty()
  @Length(3, 32)
  @IsString()
  @IsNotEmpty()
  bio: string;
}
