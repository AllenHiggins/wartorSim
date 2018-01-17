CC=g++
CFLAGS=-std=c++11 -pthread
C++FILES=main.cpp Creacher.cpp
HFILES=main.h Creacher.h


ALL:$(C++FILES) $(HFILES)
	$(CC) $(CFLAGS) *.cpp -o WartorSim

DEBUG: DEBUGFLAGS=-g -O0
DEBUG: ALL

CLEAN: rm * .o
