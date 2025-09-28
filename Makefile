CXX=g++
CXXFLAGS=-Wall -Wextra -fopenmp -g -O3 --std=c++20 -lm
FILES=src/*.cpp
OUT=.build/a.out

build:
	mkdir -p .build
	$(CXX) $(CXXFLAGS) $(FILES) -o $(OUT)

all: build

run: build
	./$(OUT)

format:
	clang-format -i src/*

.PHONY: all build run format
