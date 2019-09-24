#CC=gcc
#CXX=g++
CFLAGS = -g3 -ansi -pedantic
CXXFLAGS = $(CFLAGS) -std=c++03
LDLIBS = -lm

test: clean points-cpp points-c
	./points-cpp > a
	./points-c > b
	diff a b

clean:
	rm -f points-c points-cpp a b

.PHONY: test clean