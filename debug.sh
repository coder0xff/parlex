#!/bin/bash

set -e -o pipefail -u
DIR=$(pwd)
cd "$( dirname "${BASH_SOURCE[0]}" )"
autoreconf
cd build
../configure CFLAGS="-g3 -O0" CXXFLAGS="-g3 -O0"
make
cd test
ddd test
cd "$DIR"