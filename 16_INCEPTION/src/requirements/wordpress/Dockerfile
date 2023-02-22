FROM debian:buster

LABEL name="minkim"
LABEL email="minkim@student.42quebec.com"

RUN apt-get upadte
RUN apt-get upgrade

# download packages
RUN apt-get -y install mariadb-client vim
# to register user at wordpress
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
# download wordpress plugin and activate
RUN wp plugin install user-switching --actuvate

# set access to wp file and move it
RUN chmod +x wp-cli.phar
RUN mv wp-cli.phar /usr/local/bin/wp

# install and configure fastcgi and php-fpm
RUN apt-get install -y php7.3-fpm \
    php7.3-common \
    php7.3-mysql \
    php7.3-gmp \
    php7.3-curl \
    php7.3-intl \
    php7.3-mb-string \
    php7.3-xmlrpc \
    php7.3-gd \
    php7.3-xml \
    php7.3-cli \
    php7.3-zip \
    php7.3-soap \
    php7.3-imap \
    php7.3-fpm

# edit configure file
RUN echo "listen = 9000" >> /etc/php/7.3/fpm/pool.d/www.conf
# set access.log location
RUN echo "access.log = /var/log/$pool.access.log" >> /etc/php/7.3/fpm/pool.d/www.conf

# wordpress dir configuration and auth setting
RUN mkdir -p /var/www/wordpress
RUN chown -R www-data:www-data /var/www/wordpress/
RUN chmod 777 /var/www/wordpress/
RUN mkdir -p /run/php/

# port
EXPOSE 443

# wordpress setting
COPY tools/setup.sh /
RUN chmod 777 /setup.sh
WORKDIR /var/www/wordpress
ENTRYPOINT [ "bash", "/setupfile.sh" ]
