import {
  IsBoolean,
  IsInt,
  IsNotEmpty,
  IsOptional,
  IsString,
} from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';
import { ManagedTheme } from '../interfaces';

export class GameRulesDto {
  @ApiProperty()
  @IsNotEmpty()
  @IsInt()
  maxScore: number;

  @ApiProperty()
  @IsNotEmpty()
  @IsInt()
  maxTime: number;

  @ApiProperty()
  @IsOptional()
  @IsString()
  theme?: ManagedTheme;
}

export class CreateGameSessionDto {
  @ApiProperty()
  @IsNotEmpty()
  @IsBoolean()
  againstBot: boolean;

  @ApiProperty()
  @IsOptional()
  @IsInt()
  opponent?: number;

  @ApiProperty()
  @IsOptional()
  rules?: GameRulesDto;
}
