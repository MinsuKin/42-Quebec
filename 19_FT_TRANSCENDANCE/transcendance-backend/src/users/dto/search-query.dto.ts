import { ApiProperty } from '@nestjs/swagger';
import { IsOptional, IsString } from 'class-validator';

type SortOrder = 'asc' | 'desc';

export class SearchQuery {
  @ApiProperty({
    description: 'The search query',
    required: true,
  })
  @IsString()
  query: string;

  @ApiProperty({
    description:
      'The number of records to skip before starting to collect the result set.',
    required: false,
    default: '0',
  })
  @IsOptional()
  skip?: string = '0';

  @ApiProperty({
    description: 'The number of records to take.',
    required: false,
    default: '10',
  })
  @IsOptional()
  take?: string = '10';

  @IsOptional()
  orderBy: {
    username?: SortOrder;
    email?: SortOrder;
    profile?: {
      name?: SortOrder;
      lastname?: SortOrder;
      status?: SortOrder;
    };
    createdAt?: SortOrder;
    updatedAt?: SortOrder;
  };
}
