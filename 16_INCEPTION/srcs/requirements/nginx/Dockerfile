FROM debian:buster

LABEL name="minkim"
LABEL email="minkim@student.42quebec.com"

RUN apt-get update

# download packages
RUN apt-get -y install nginx openssl vim
RUN rm /etc/nginx/sites-available/default
RUN rm /etc/nginx/sites-enabled/default

# copy default routing path setting file in the container
COPY conf/nginx.conf /etc/nginx/sites-available/defualt
RUN ln -s /etc/nginx/sites-available/default /etc/nginx/sites-enabled/default
RUN mkdir /etc/nginx/ssl

# request SSL cert
RUN openssl req -newkey rsa:4096 -days 365 -nodes \
    -out /etc/nginx/ssl/www.minkim.42.fr.crt \
    -keyout /etc/nginx/ssl/www.minkim.42.kr.key \
    -subj "/C=CA/S=Quebec/L=QuebecCity/O=42Quebec/OU=incptn/CN=minkim"

# setting auth and ownership
RUN chmod 777 /etc/nginx/ssl/*
RUN chmod          777 -R /var/www
RUN chown -R www-data:www-data /var/www/

# port
EXPOSE 443
# foreground run
ENTRYPOINT [ "nginx", "-g", "daemon off;" ]
