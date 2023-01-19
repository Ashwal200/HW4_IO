CC = gcc -c
CFLAGS = -Wall -g
CLIBSA = ar rcs

all: graph libstacts.a

.PHONY:clean

clean:
	rm -rf *.o *.a graph

graph : main.o libstacts.a
	gcc -Wall main.o ./libstacts.a -o graph

libstacts.a : edges.o nodes.o graph.o graph.h
	$(CLIBSA) libstacts.a edges.o nodes.o graph.o

main.o : main.c graph.h
	$(CC) $(CFLAGS) main.c

edges.o : edges.c graph.h edges.h
	$(CC) $(CFLAGS) edges.c

nodes.o : nodes.c graph.h
	$(CC) $(CFLAGS) nodes.c

graph.o : graph.c graph.h
	$(CC) $(CFLAGS) graph.c
