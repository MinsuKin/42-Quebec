#!/bin/bash

# Remove images and containers
docker-compose down 
docker system prune -a

# Load environment variables
source ../../.env

# Host conversion operation to replace DNS
echo '127.0.0.1 minkim.42.fr' >> /etc/hosts 
echo '127.0.0.1 www.minkim.42.fr' >> /etc/hosts 
