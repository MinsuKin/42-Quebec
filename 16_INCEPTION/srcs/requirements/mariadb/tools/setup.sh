#!/bin/bash

if [ ! -d "/var/lib/mysql/wordpress" ]; then

    mysql -e "CREATE USER '${MARIA_ID}'@'localhost' IDENTIFIED BY '${MARIA_PW}';" &&\
    mysql -e "CREATE DATABASE IF NOT EXISTS wordpress;" &&\
    mysql -e "GRANT ALL PRIVILEGES ON *.* TO '${MARIA_ID}'@localhost IDENTIFIED BY '${MARIA_PW}';" &&\
    mysql -e "GRANT ALL PRIVILEGES ON *.* TO '${MARIA_ID}'@'%' IDENTIFIED BY '${MARIA_PW}';" &&\
    mysql -e "UPDATE mysql.user SET Password = PASSWORD('${MARIA_PW}') WHERE USER = 'root';" &&\ 
    mysql -e "FLUSH PRIVILGES;"    
    service mysql stop
fi

sleep 3

mysqld
