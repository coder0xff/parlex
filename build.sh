#!/bin/bash
set -ex

CXXFLAGS="-std=c++11 -g"

clang++ -c builtins.cpp $CXXFLAGS
clang++ -c job.cpp $CXXFLAGS
clang++ -c parser.cpp $CXXFLAGS
clang++ -c subjob.cpp $CXXFLAGS

ar crsv libparlex.a builtins.o job.o parser.o subjob.o