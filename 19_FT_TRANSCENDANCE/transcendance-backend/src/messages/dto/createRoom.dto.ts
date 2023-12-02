import { ApiProperty } from '@nestjs/swagger';
import { IsNotEmpty, IsOptional } from 'class-validator';
import { RoomType } from '@prisma/client';

export class CreateRoomDto {
  @ApiProperty()
  @IsNotEmpty()
  ownerId: number; // the id of the owner of the room

  @ApiProperty()
  @IsNotEmpty()
  name: string;

  @ApiProperty()
  @IsNotEmpty()
  type: RoomType; //  PUBLIC: 'PUBLIC', PRIVATE: 'PRIVATE', PROTECTED: 'PROTECTED'

  @ApiProperty()
  @IsOptional()
  password?: string;

  @ApiProperty()
  @IsOptional()
  avatar?: string;
}
