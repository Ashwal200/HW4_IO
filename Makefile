#Dictionery:
CFLAGS = gcc -c -Wall -g
FLAG = gcc -Wall -o

#nodes.o : nodes.c nodes.h graph.h
#	$(CFLAG) nodes.c
#edges.o : edges.c edges.h graph.h
#	$(CFLAG) edges.c
#graph.o: graph.c graph.h nodes.h edges.h
#	$(CFLAG) graph.c
#main.o: main.c graph.h nodes.h edges.h
#	$(CFLAG) main.c
#graph : edges.o nodes.o graph.o main.o
#	$(FLAG) graph edges.o nodes.o graph.o main.o
#
#all: graph
#
#.PHONY:clean
#
#clean:
#	rm *.o graph

all: main
main: edges.c graph.c nodes.c main.c graph.h
	gcc -Wall -g -o graph edges.c graph.c nodes.c main.c