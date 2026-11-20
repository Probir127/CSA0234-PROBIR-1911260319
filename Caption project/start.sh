#!/bin/sh
# Always serve assets and records from the project, even when launched elsewhere.
set -eu
cd -- "$(dirname -- "$0")"
make
exec ./server "$@"
