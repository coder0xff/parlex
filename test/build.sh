#!/bin/bash
set -ex

clang++ -c main.cpp -g -I ../ -std=c++11
clang++ main.o -o test -g -pthread -L ../ -lparlex -std=c++11
