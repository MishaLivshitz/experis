# This makefile will build one of ping pong files

# Sources are ping or pong .c files in directory

ifeq ($(NAME),ping)
	TARGET = ping
	SOURCES = ping.c
else
	TARGET = pong
	SOURCES = pong.c
endif

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
$(TARGET): $(OBJECTS)

# Compile the object
#%.o: %.c
#	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# Ask C pre-processor to help us with include files
include depends
# You may decide to add/remove $(SOURCES) from dependents
depends:
	$(CC) $(CPPFLAGS) $(SOURCES) > $(@)

clean:
	rm -f $(wildcard *.o) depends ping pong

run: $(TARGET)

