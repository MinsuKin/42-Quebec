#!/bin/sh

if [ "$BUILD_TYPE" = "production" ]; then
  cp /prod.conf /etc/nginx/conf.d/default.conf
else
  cp /dev.conf /etc/nginx/conf.d/default.conf
fi

# Start the default Nginx entrypoint
exec /docker-entrypoint.sh "$@"
