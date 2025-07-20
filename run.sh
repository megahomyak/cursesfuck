#!/bin/bash
set -euo pipefail
gcc "./$1" -lncurses
shift
( set +e ; ./a.out "$@" ; rm a.out )
