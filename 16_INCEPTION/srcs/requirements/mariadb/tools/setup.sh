#!/bin/bash

if [ ! -d "/var/lib/mysql/wordpress" ]; then 
    
    mysql_install_db
    service mysql start
    
    mysql -e "CREATE USER '${MARIA_ID}'@'localhost' IDENTIFIED BY '${MARIA_PW}';"
	mysql -e "CREATE DATABASE IF NOT EXISTS wordpress;"
	mysql -e "GRANT ALL PRIVILEGES ON *.* TO '${MARIA_ID}'@'localhost' IDENTIFIED BY '${MARIA_PW}';"
	mysql -e "GRANT ALL PRIVILEGES ON *.* TO '${MARIA_ID}'@'%' IDENTIFIED BY '${MARIA_PW}';"
	mysql -e "UPDATE mysql.user SET password = PASSWORD('${MARIA_PW}') WHERE user = 'root';"
	mysql -e "FLUSH PRIVILEGES;"

    mysqladmin -uroot -p${MARIA_PW} shutdown
fi

sleep 3

exec mysqld_safe
