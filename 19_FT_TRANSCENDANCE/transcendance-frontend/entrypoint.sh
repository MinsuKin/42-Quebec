#!/bin/sh

# Check the BUILD_TYPE and execute appropriate command
if [ "$BUILD_TYPE" = "production" ]; then
  echo "Build frontend code..."
  yarn build
  echo "Stop and let Nginx serve files..."
else
  echo "Try build for dist folder..."
  yarn build
  echo "Running development server with vite..."
  exec yarn dev
fi
