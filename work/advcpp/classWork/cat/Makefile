TARGET = challenge

# we are using g++, hence the need to define CC
CC=g++
# C compiler flags
CFLAGS +=-g -pedantic -ansi -Wall -Werror -DDEBUG -fPIC 
CXXFLAGS += $(CFLAGS) -std=c++03
# Linker (ld) flags
LDFLAGS+=-g -pthread 
# Include path
INC_DIR +=  ./include ../include ../../include
INC_FLAG = $(addprefix -I,$(INC_DIR))

CPPFLAGS += $(INC_FLAG)

# all .c files in current directory
SOURCES += $(wildcard *.cpp)
OBJECTS ?= $(SOURCES:.cpp=.o)
#
.PHONY: all clean test libcat.so
#

all:	$(TARGET) libcat.so test

libcat.so:	$(OBJECTS)
	$(CC) -shared $< -o $@

# the target is the test file
#	Built-in linker rule $(CC) $(LDFLAGS) -o $(@) $(*) $(LDLIBS)
$(TARGET): $(OBJECTS)


# dependencies
# for every line in depends file the following built-in rule is used
# $(CC) $(CPPFLAGS) $(CFLAGS) / $(CXXFLAGS) -c -o $@ $<
include depends
depends:
	$(CC) -MM $(CPPFLAGS) $(SOURCES) > depends

clean:
	rm -f $(OBJECTS) $(TARGET) *.so depends *.gch

test: $(TARGET)
	./$(TARGET) -v


