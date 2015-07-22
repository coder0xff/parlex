#!/bin/bash
set -ex

clang++ -c main.cpp -I ../ -std=c++11
clang++ main.o -o test -pthread -L ../ -lparlex -std=c++11
