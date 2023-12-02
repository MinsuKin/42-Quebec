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
- Frontend: TypeScript framework of your choice
- Database: PostgreSQL
- Single-page application (SPA)
- Compatible with the latest stable version of Google Chrome and another browser of your choice

## Repository Structure

- `/nginx`: Nginx configuration files
- `/transcendance-backend`: Git submodule for the backend [repository](https://github.com/ftmjr/transcendance-backend)
- `/transcendance-frontend`: Git submodule for the frontend [repository](https://github.com/ftmjr/transcendance-frontend)

## Setup and Development

1. Clone the repository including submodules:
```shell
git clone --recursive https://github.com/ftmjr/transcendance.git
```

2. To set up the project, write the .env file and  run `docker-compose up`.

While developing, it's a good idea to open the submodule (either backend or frontend) in a separate editor to ensure correct linting.

## Contributors

This project is developed and maintained by the FTMJR - Team organization. Special thanks to our contributors:

- Tokutaro Shimoda - [@Rurikide](https://github.com/Rurikide)
- Josias kasongo josiaskas - [@josiaskas](https://github.com/josiaskas)
- Francis Lahoud - [@FrancisL93](https://github.com/FrancisL93)
- Gederooney - [@Gederooney](https://github.com/Gederooney)
- Minsu - [@MinsuKin](https://github.com/MinsuKin)

## Project Management

We use a [GitHub project board](https://github.com/orgs/ftmjr/projects/1/views/1) to manage and track the progress of the project. All changes to the `main` branch in the submodules and `master` branch in the main repository should be made via pull requests from the `develop` branch.

## PreBuild Version

- you may need to run yarn build in frontend to see the website.
- remove lines in nginx config to use in dev or prod 


