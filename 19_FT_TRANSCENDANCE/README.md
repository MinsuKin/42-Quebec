# Transcendance

Transcendance is a web application for participating in a Pong competition. The web application will allow users to play Pong with each other, providing a user interface, chat, and real-time multiplayer online matches.

## Features

- User authentication via OAuth (Intranet 42)
- Unique usernames and avatars
- Two-factor authentication (2FA) support
- Friend list and real-time status updates
- User profiles with stats and match history
- Chat channels (public, private, password-protected)
- Direct messaging between users
- Blocking users

## Technical Overview

- Backend: NestJS
- Frontend: Vue.js
- Database: PostgreSQL

## Repository Structure

- `/nginx`: Nginx configuration files
- `/transcendance-backend`: Git submodule for the backend [repository](https://github.com/ftmjr/transcendance-backend)
- `/transcendance-frontend`: Git submodule for the frontend [repository](https://github.com/ftmjr/transcendance-frontend)

## Setup and Development

To set up the project, write the .env file and  run `docker-compose up`.
