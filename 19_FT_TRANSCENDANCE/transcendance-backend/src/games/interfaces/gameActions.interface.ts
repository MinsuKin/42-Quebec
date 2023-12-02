export enum PAD_DIRECTION {
  up,
  down,
  none,
}

export interface PadMovedData {
  userId: number;
  direction: PAD_DIRECTION;
  position: { x: number; y: number };
}

export interface BallServedData {
  userId: number;
  position: { x: number; y: number };
  speed: { x: number; y: number };
}
