#!/usr/bin/env bash
set -xe

FILES=src/*.cpp
OUT=.build/a.out

mkdir -p .build
g++ -fopenmp --std=c++20 -lm $FILES -o $OUT
./$OUT
