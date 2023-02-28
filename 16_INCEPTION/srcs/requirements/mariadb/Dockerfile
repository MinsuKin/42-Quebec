FROM debian:buster

LABEL name="minkim"
LABEL email="minkim@student.42quebec.com"

RUN apt-get upadte
RUN apt-get install -y mariadb-server vim

COPY tools/setupfile.sh .
RUN chmod +x setupfile.sh

EXPOSE 3306
RUN rm /etc/mysql/mariadb.conf.d/50-server.cnf
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d
ENTRYPOINT [ "bash", "/setupfile.sh" ]
