#!/bin/bash

mysql -e "CREATE USER '${MARIA_ID}'@'localhost' IDENTIFIED BY '${MARIA_PW}';";
mysql -e "GRANT ALL PRIVILEGES ON *.* TO'${MARIA_ID}'@'%' IDENTIFIED BY '${MARIA_PW}';";
mysql -e "UPDATE mysql.user SET Password = PASSWORD('${MARIA_PW}') WHERE USER = 'root';"; &&\

cd /mysql/bin
mysqld
