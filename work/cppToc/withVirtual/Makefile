#CC=gcc
#CXX=g++
CFLAGS = -g3 -ansi -pedantic
CXXFLAGS = $(CFLAGS) -std=c++03
LDLIBS = -lm

test: clean shapes shapes-c
	./shapes > a
	./shapes-c > b
	diff a b

clean:
	rm -f shapes-c shapes a b

.PHONY: test clean