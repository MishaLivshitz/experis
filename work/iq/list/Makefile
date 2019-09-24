TARGET = test

CC=g++
CFLAGS +=-g3 -pedantic -ansi -Wall -Werror -DDEBUG -fPIC
CXXFLAGS += $(CFLAGS) -std=c++03

list: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)