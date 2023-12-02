#!/bin/sh

#wait for db to be ready
sleep 5
# Check if database is ready
until nc -z -v -w30 db 5432
do
  echo "Waiting for database connection..."
  # wait for 5 seconds before check again
  sleep 5
done

# Execute Prisma generate
npx prisma generate

# Execute Prisma migrations
npx prisma migrate deploy

# Execute Prisma seed
npx prisma db seed

# Set uploads folder permissions
chmod -R 777 /app/uploads

# Check the BUILD_TYPE and execute appropriate command
if [ "$BUILD_TYPE" = "production" ]; then
  echo "Build code..."
  yarn build
  echo "Running production server..."
  exec yarn start
else
  echo "Running development server..."
  exec yarn start:dev
fi
