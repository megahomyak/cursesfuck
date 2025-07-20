#!/bin/bash
set -euo pipefail
gcc "./$1" -lncurses
shift
./a.out "$@"
rm a.out
