CXX=g++
CXXFLAGS=-Wall -Wextra -fopenmp -Ofast --std=c++2b -lm
FILES=src/*.cpp
OUT=.build/a.out

build:
	$(CXX) $(CXXFLAGS) $(FILES) -o $(OUT)

all: build

run: build
	./$(OUT)

format:
	clang-format -i src/*

.PHONY: all build run format
