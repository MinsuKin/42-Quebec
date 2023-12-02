export interface NewRoom {
  name: string;
  password: string | null;
  protected: boolean;
  private: boolean;
  ownerId: number;
}

export interface User {
  userId: string;
  userName: string;
  socketId: string;
}

export interface Message {
  message: string;
  roomName: string;
}

export interface Room {
  name: string;
  host: User;
  users: User[];
}

// Interface for when server emits events to clients.
export interface ServerToClientEvents {
  chat: (e: Message) => void;
}

// Interface for when clients emit events to the server.
export interface ClientToServerEvents {
  chat: (e: Message) => void;
  join_room: (e: { user: User; roomName: string }) => void;
}
