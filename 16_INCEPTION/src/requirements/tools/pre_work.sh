#!/bin/bash

echo -e "\e[47;35m--Remove images and containers--\e[0m\n"

docker-compose down
docker system prune -a

echo -e "\e[44;33m@@@It's all been erased@@@\e[0m\n\n"

# load environment variables
source ../../.env

echo -e "\e[44;33@@@It's set up@@@\e[0m\n\n"

echo -e "\e[47;35m--Host conversion operation to replace DNS--\e[0m\n"

# Add DNS like localhost to change domain
echo '127.0.0.1 minkim.42.fr' >> /etc/hosts
echo '127.0.0.1 www.minkim.42.fr' >> /etc/hosts

echo -e "\e[44;33m@@@Host is set up@@@\e[0m\n\n"
