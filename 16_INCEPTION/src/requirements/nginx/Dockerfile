FROM debian:buster

RUN apt-get upadte
RUN apt-get upgrade

# download packages
RUN apt-get install nginx
RUN apt-get -y install openssl

# copy default routing path setting file in the container

# request SSL cert
RUN openssl req -newkey rsa:4096 -days 365 -nodes -x509 -subj "/C=CA/S=Quebec/L=QuebecCity/O=42Quebec/OU=incptn/CN=minkim" -keyout localhost.dev.key -out localhost.dev.crt
RUN mv localhost.dev.crt etc/ssl/certs/
RUN mv localhost.dev.key etc/ssl/private/

# setting auth and ownership
RUN chmod 600 etc/ssl/certs/localhost.dev.crt etc/ssl/private/localhost.dev.key

# port

# foreground run
RUN nginx -g daemon off;