FROM debian:buster

LABEL name="minkim"
LABEL email="minkim@student.42quebec.com"

RUN apt-get update
RUN apt-get install -y mariadb-server vim

COPY tools/setup.sh .
RUN chmod +x setup.sh

EXPOSE 3306
RUN rm /etc/mysql/mariadb.conf.d/50-server.cnf

# Swith off the bind address
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d
ENTRYPOINT [ "bash", "/setup.sh" ]
