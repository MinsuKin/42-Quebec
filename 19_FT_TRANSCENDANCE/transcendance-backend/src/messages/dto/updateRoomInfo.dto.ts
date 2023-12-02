import {
  IsInt,
  IsNotEmpty,
  IsOptional,
  IsString,
  MinLength,
} from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';
import { RoomType } from '@prisma/client';

export class UpdateRoomInfoDto {
  @ApiProperty()
  @IsInt()
  @IsNotEmpty()
  roomId: number;

  @ApiProperty()
  @IsString()
  @IsNotEmpty()
  roomType: RoomType;

  @ApiProperty()
  @IsString()
  @IsOptional()
  oldPassword: string;

  @ApiProperty()
  @IsString()
  @IsOptional()
  @MinLength(6, {
    message: 'Password must be at least 6 characters long',
  })
  password: string;
}
