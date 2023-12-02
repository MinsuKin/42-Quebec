import { IsNotEmpty, IsNumber, IsString } from 'class-validator';
import { GameUserType } from '../interfaces';

export class GameUser {
  @IsNumber()
  @IsNotEmpty()
  userId: number;

  @IsString()
  @IsNotEmpty()
  username: string;

  @IsString()
  avatar?: string;
}

export class JoinGameEvent {
  @IsNumber()
  @IsNotEmpty()
  roomId: number;

  user: GameUser;

  @IsNumber()
  @IsNotEmpty()
  userType: GameUserType;
}
