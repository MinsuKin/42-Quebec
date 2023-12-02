import { ApiProperty } from '@nestjs/swagger';
import { IsInt, IsNotEmpty } from 'class-validator';

export class RemoveFromRoomDto {
  @ApiProperty()
  @IsNotEmpty()
  @IsInt()
  roomId: number;

  @ApiProperty()
  @IsNotEmpty()
  @IsInt()
  userId: number;
}
