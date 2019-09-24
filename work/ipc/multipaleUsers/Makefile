# This makefile will build one of ping pong files
TARGET = ping pong
# Sources are ping or pong .c files in directory
SOURCES = $(wildcard *.c)

# Objects are all sources with substitution of filename extension .c to .o
OBJECTS ?= $(SOURCES:.c=.o)
# default compiler is CC, but we use $(CC)
CC = gcc
# Compiler and linker flags
# C pre-processor flags
#	Add -I to the list of include directories and add this to CPPFLAGS
CPPFLAGS += $(addprefix)
#   Compilation flags
CFLAGS	 ?= -g3 -ansi -pedantic -Wall -DDEBUG -Werror
#   Linker flags
LDFLAGS	 ?= -g3 

.PHONY:	all clean run


all: $(TARGET) run

# Link the target
#%: %.o
#	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
#$(TARGET): $(OBJECTS)
# list of dependancies for ping and pong
ping: ping.o pingpong.o

pong: pong.o pingpong.o

# Compile the object
#%.o: %.c
#	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# Ask C pre-processor to help us with include files
include depends
# You may decide to add/remove $(SOURCES) from dependents
depends:
	$(CC) -MM $(CPPFLAGS) $(SOURCES) > $(@)

clean:
	rm -f $(TARGET) *.o depends 

# Not for multiple targets
run: $(TARGET)

