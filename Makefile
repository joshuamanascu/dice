CC = gcc
CFLAGS = -Wall -Wextra -g -I./src/include

SOURCES = dice.c parser.c roll.c
OBJS = dice.o parser.o roll.o
HEADERS = parser.h roll.h


dice: $(OBJS)
	$(CC) $(CFLAGS) -o dice $(OBJS)

$(OBJS): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -c $(SOURCES)


clean:
	rm $(OBJS)

