import { ApiProperty } from '@nestjs/swagger';

export class RefreshDataDto {
  @ApiProperty()
  accessToken: string;
}
