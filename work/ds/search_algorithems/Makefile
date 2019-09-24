# this is my target
TARGET = search.out
LIBS = 

.PHONY: run clean gdb

# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)
CC = gcc
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Wall -Werror -g
# The debugger flags will be... ("LDFLAGS" is MAKE variable)
LDFLAGS = -g

# Include directory
INC_DIR = ../include
LIB_PATH=
CFLAGS += -I$(INC_DIR)


# All .c files in this directory are my sources
SOURCES = search.c searchTest.c ../vector/vector.c ../sort_algorithems/sortAlg.c
LIB_SRC = 
# All .o files in this directory are my objects
OBJECTS = $(SOURCES:.c=.o)
LIB_OBJ = 

# The default command, compile all the sources
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)     


# Built-in recipe for link("include" is MAKE command), include call "depends"

include depends

# Compile the sources, going over the c.files and create new file with list of the h.files that need to be included to each c.file.
# In the next time, if there where no changes in the h.files thet are needed, the depends file will be exist so the include will go to the file instead of build new one. 
depends:
	$(CC) -MM -I$(INC_DIR) $(SOURCES) $(LIB_SRC) > depends

libs: 

clean:
	-rm $(TARGET) *.o depends

run:  $(TARGET)
	 ./$(TARGET)

gdb:  $(TARGET)
	 gdb -q ./$(TARGET)
	
