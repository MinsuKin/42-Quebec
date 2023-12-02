# ft_irc - Internet Relay Chat

## Project Overview

The **ft_irc** project focuses on creating a custom IRC (Internet Relay Chat) server, adhering to established internet standards and protocols. IRC is a widely-used communication protocol that enables real-time text messaging between users on a network. In this project, the goal is to implement a server capable of handling multiple clients simultaneously, with a specific emphasis on non-blocking I/O operations.

## Project Requirements

The key requirements for the **ft_irc** project are as follows:

1. The server must handle multiple clients concurrently without hanging.
2. Forking is not allowed; all I/O operations must be non-blocking.
3. Only one poll() (or equivalent) can be used for handling read, write, listen, etc.
4. Communication between the server and clients must be done via TCP/IP (v4 or v6).
5. The project must select a reference IRC client for evaluation purposes.
6. The reference client should connect to the server without encountering errors.
7. Implemented features include authentication, setting a nickname, username, joining a channel, sending and receiving private messages.
8. Messages sent to a channel must be forwarded to every client in that channel.
9. Support for operators and regular users, with specific commands for operators.
10. macOS-specific considerations, such as using fcntl() for non-blocking mode.

## Specific Features to Implement

1. **Authentication and User Setup:**
   - Set a nickname and a username.
   - Join a channel.
   - Send and receive private messages.

2. **Channel Operations:**
   - Forward messages from one client to all others in the channel.
   - Implement operators and regular users.
   - Channel-specific operator commands:
      - KICK: Eject a client from the channel.
      - INVITE: Invite a client to a channel.
      - TOPIC: Change or view the channel topic.
      - MODE: Change the channel's mode (i, t, k, o, l).
