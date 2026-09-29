CC = gcc
CFLAGS = -Wall -Wextra -Isources
SOURCES = $(wildcard *.c sources/*.c)
OBJECTS = $(SOURCES:.c=.o)

all: rabbit.exe

rabbit.exe: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -lm -o $@

clean:
	del /Q $(subst /,\,$(OBJECTS)) rabbit.exe