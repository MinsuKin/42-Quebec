#!/bin/bash

# sleep 10
for ((i=10000; i>=0; i--))
do
    echo -e "\e[31mloading...\e[0m\n"
done

    for ((i=10000; i>=0; i--))
    do
        echo -e "\e[31mloading...\e[0m\n"
    done

    wp core --allow-root download --locale=en_CA --force

    while [ ! -f /var/www/wordpress/wp-config.php ]; do
        # allow wp-cli admin auth, setup db admin
        wp core config --allow-root \
            --dbname=wordpress --dbuser=${MARIA_ID} --dbpass=${MARIA_PW} --dbhost=mariadb:3306
    done

    # create wordpress table in database
    wp core install config --allow-root \
        --url='minkim.42.fr' --title='WordPress for Inception' \
        --admin_user=${WP_ID} --admin_password=${WP_PW} --admin_email="minkim@student.42quebec.com" \
        --path='/var/www/wordpress';

    # create user
    wp user create --allow-root \
        ${WP_USER_ID} minus9521@gmail.com -- user_pass=${WP_USER_PW} --role=author
fi

# not sending process to background, pid remains 1 while the process stays in foreground
php-fpm7.3 --nodaemonize
