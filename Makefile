CC = gcc
CFLAGS = -Wall -Wextra -g -I./src/include

SOURCES = dice.c parser.c
OBJS = dice.o parser.o
HEADERS = parser.h


#EXECUTABLE SHOULD BE FIRST DUH
dice: $(OBJS)
	$(CC) $(CFLAGS) -o dice $(OBJS)

$(OBJS): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -c $(SOURCES)


