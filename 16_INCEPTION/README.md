<h1 align="center">
	INCEPTION
</h1>

##  Summary

The Inception project is a system administration project that involves creating a virtual machine with Docker to virtualize multiple Docker images and set up a small infrastructure composed of different services under specific rules, including NGINX, WordPress, MariaDB, and volumes for databases and website files.

##  Usage

Run `set_for_docker.sh` and `make` in an Ubuntu environment and launch as follows:

    cd ./srcs/requirements/tools/set_for_docker.sh && make

***Makefile rules***

- Use `make setup` to prepare the environment.
- Use `make build` to build and run the Docker containers.
- Use `make stop` to stop the running Docker containers.
- Use `make clean` to clean up the Docker environment.
- Use `make fclean` to completely clean up the Docker environment and remove the ~/data/ directory.
- `make all` = `clean + setup + build`

## Project structure

    Inception/
    ├── Makefile
    └── srcs
        ├── docker-compose.yml
        └── requirements
            ├── mariadb
            │   ├── Dockerfile
            │   ├── conf
            │   │   └── 50-server.cnf
            │   └── tools
            │       └── setup.sh
            ├── nginx
            │   ├── Dockerfile
            │   └── conf
            │       └── nginx.conf
            ├── tools
            └── wordpress
                ├── Dockerfile
                └── tools
                    └── setup.sh

## Services
The Inception project consists of the following services:

- nginx -- a Docker container that contains NGINX with TLSv1.2 or TLSv1.3 only.
- WordPress -- a Docker container that contains WordPress + php-fpm.
- mariadb -- a Docker container that contains MariaDB.

## Notes
- No password must be present in the Dockerfiles.
- It is mandatory to use environment variables.
- The volumes will be available in the /home/login/data folder of the host machine using Docker.
- All credentials, API keys, environment variables, etc. must be saved locally in a .env file.

##  Screenshot
<img width="1286" alt="Screen Shot 2023-04-01 at 7 02 27 PM" src="https://user-images.githubusercontent.com/50944735/229320026-91cc356b-1457-4e57-ba89-3c9cd8b7da3e.png">
<img width="1287" alt="Screen Shot 2023-04-01 at 7 06 36 PM" src="https://user-images.githubusercontent.com/50944735/229320029-0553871a-ea50-4cc7-8cd5-cd84b49d53e4.png">


## Peer Evaluation(Code Review)

### As a Interviewee
<img width="566" alt="Screen Shot 2023-04-01 at 6 24 51 PM" src="https://user-images.githubusercontent.com/50944735/229316695-80d062d7-b3e3-4e95-83d0-12c7ea67647b.png">


### As a Interviewer
<img width="552" alt="Screen Shot 2023-04-01 at 6 25 17 PM" src="https://user-images.githubusercontent.com/50944735/229316699-b6b24de8-9241-46f1-b18d-cc26c853d89f.png">


# Inception : Service & Docker

## 배우는 것

- Service 가 무엇인지
- Docker 가 무엇인지
    - 장점
    - Docker Volume - binding
    - Docker Network - none, bridge, host, …
    - Docker Swarm
    - Docker Compose
- tmpfs
- 컨테이너 오케스트레이션의 필요성
- Nginx
- WordPress
- 쿠버네티스
- 프로비저닝
