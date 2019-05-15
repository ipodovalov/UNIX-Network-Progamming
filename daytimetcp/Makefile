CC = gcc
CFLAGS = -g -O2 -D_REENTRANT -Wall

LIBS = -lpthread

.PHONY : all clean

TARGET ?= ask_timesrv
SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)

OBJECTS := $(patsubst %.c,%.o,$(SOURCES))

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	${CC} -o $@ $^

%.o : %.c
	${CC} -c $<

dependencies : $(SOURCES) $(HEADERS)
	${CC} -MM $(SOURCES) > $@

-include dependencies

clean :
	rm -f *.a *.o $(TARGET) *~ dependencies
