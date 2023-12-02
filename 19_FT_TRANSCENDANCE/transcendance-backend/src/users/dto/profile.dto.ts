import { ApiProperty } from '@nestjs/swagger';
import { AwardDto } from './award.dto';

export class ProfileDto {
  @ApiProperty()
  id: number;

  @ApiProperty()
  userId: number;

  @ApiProperty()
  name: string;

  @ApiProperty()
  lastname: string;

  @ApiProperty()
  avatar?: string;

  @ApiProperty()
  bio?: string;

  @ApiProperty()
  oauth?: any; // TODO: define oauth interface in the future

  @ApiProperty({ type: () => [AwardDto] })
  awards: AwardDto[];
}
