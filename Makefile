CC = gcc
CFLAGS = -Wall -Wextra -Isources -O3 -march=native -flto
LDFLAGS = -flto
LDLIBS = -lm

COMMON_SOURCES = $(wildcard sources/*.c)
COMMON_OBJECTS = $(COMMON_SOURCES:.c=.o)

all: simulation.exe tests.exe

simulation.exe: simulation.o $(COMMON_OBJECTS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

tests.exe: tests.o $(COMMON_OBJECTS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	del /Q $(subst /,\,$(COMMON_OBJECTS)) simulation.o tests.o simulation.exe tests.exe