FROM node:20-alpine

WORKDIR /app

#copy everything, dockerignore will ignore node_modules
COPY . .

# set prisma migration and sync with database
COPY entrypoint.sh .
RUN chmod +x entrypoint.sh

RUN yarn install

RUN yarn prisma generate

# we watch change only in source
VOLUME /app/src
VOLUME /app/prisma

EXPOSE 3001

ENTRYPOINT ["/app/entrypoint.sh"]
