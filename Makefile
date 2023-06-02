#Compiler, Compiler Flags
CC = gcc
CFLAGS =-Wall -std=c99 -O3

#Sources
SOURCES = main.c graph.c variants.c

#Objects ('make' automatically compiles .c to .o)
OBJECTS = main.o graph.o variants.o

backbone: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

main.o: main.c graph.h

graph.o: graph.c graph.h

variants.o: variants.c graph.h

clean:
		rm -f *.o main
