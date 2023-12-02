# FT_transcendance

FT_transcendance is a dynamic web application featuring a 1:1 online Pong game alongside a robust set of social and user interaction features. From OAuth authentication and 2FA to a comprehensive chat system, friend management, and personalized user profiles, FT_transcendance offers a diverse and engaging user experience.

## Key Features

- **User Authentication via OAuth (Intranet 42):**
  - Securely log in using OAuth through the Intranet 42 authentication system.

- **Unique Usernames and Avatars:**
  - Personalize your profile with unique usernames and avatars for a distinctive online presence.

- **Two-Factor Authentication (2FA) Support:**
  - Enhance account security with 2FA, adding an extra layer of protection to user accounts.

- **Friend List and Real-time Status Updates:**
  - Build a network of friends and receive real-time updates on their online status.

- **User Profiles with Stats and Match History:**
  - Explore detailed user profiles showcasing statistics and a comprehensive match history.

- **Chat Channels:**
  - Engage in public chat channels, create private channels, or set password-protected channels for exclusive conversations.

- **Direct Messaging:**
  - Communicate seamlessly through direct messages, fostering one-on-one interactions.

- **Blocking Users:**
  - Manage your online experience by blocking unwanted users.

## Technical Overview

- **Language:**
  - Typescript

- **Infrastructure:**
  - Docker
  - Docker Compose
  - Nginx

- **Frontend:**
  - Vue.js
  - Vite

- **Backend:**
  - NestJS
  - Socket.io
  - Prisma

- **Database:**
  - PostgreSQL

## Repository Structure

- **`/nginx`:**
  - Nginx configuration files.

- **`/transcendance-backend`:**
  - Git submodule for the backend [repository](https://github.com/ftmjr/transcendance-backend).

- **`/transcendance-frontend`:**
  - Git submodule for the frontend [repository](https://github.com/ftmjr/transcendance-frontend).

## Setup and Development

To set up the project:

1. Create a `.env` file with the necessary configuration.
2. Run `docker-compose up` to initiate the development environment.

Feel free to explore the backend and frontend repositories for more detailed information on each component.

Enjoy the immersive experience of FT_transcendance, where gaming meets social interaction in a feature-rich web application.
