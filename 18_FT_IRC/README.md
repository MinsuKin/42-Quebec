# ft_irc - Internet Relay Chat

## Project Overview

A customized IRC(Internet Relay Chat) server. IRC is a widely-utilized communication protocol facilitating real-time text messaging among users on a network. The primary objective of this project is to develop a server capable of handling multiple clients simultaneously, placing a specific emphasis on non-blocking I/O operations.

## Project Requirements

The key requirements for the ft_irc project include:

- **Concurrent Client Handling:** The server must manage multiple clients concurrently without hanging.
- **Non-blocking I/O Operations:** Forking is not allowed; all I/O operations must be non-blocking.
- **Single Poll():** Only one poll() (or equivalent) can be used for handling read, write, listen, etc.
- **TCP/IP Communication:** Communication between the server and clients must be done via TCP/IP (v4 or v6).
- **Reference IRC Client:** Choose a reference IRC client for evaluation purposes; it should connect to the server without encountering errors.
- **Implemented Features:** Features to implement include authentication, setting a nickname, username, joining a channel, and sending/receiving private messages.
- **Channel Messaging:** Messages sent to a channel must be forwarded to every client in that channel.
- **Operator Support:** Support for operators and regular users, with specific commands for operators.

## Specific Features to Implement

### Authentication and User Setup:

- **Set Nickname and Username:** Users should be able to set a nickname and a username.
- **Channel Joining:** Implement the ability to join a channel.
- **Private Messaging:** Allow users to send and receive private messages.

### Channel Operations:

- **Message Forwarding:** Forward messages from one client to all others in the channel.
- **User Roles:** Implement operators and regular user roles.
- **Operator Commands:** Include specific commands for operators, such as:
  - **KICK:** Eject a client from the channel.
  - **INVITE:** Invite a client to a channel.
  - **TOPIC:** Change or view the channel topic.
  - **MODE:** Change the channel's mode (i, t, k, o, l).
