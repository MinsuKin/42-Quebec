FROM node:20-alpine

WORKDIR /app

#copy everything, dockerignore will ignore node_modules
COPY . .

RUN yarn install

# set prisma migration and sync with database
COPY entrypoint.sh .
RUN chmod +x entrypoint.sh

# final version will not have this line
VOLUME /app/src
# final version will not have this line
VOLUME /app/public

EXPOSE 3000

ENTRYPOINT ["/app/entrypoint.sh"]
