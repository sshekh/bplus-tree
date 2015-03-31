CC=g++ -std=gnu++11
CFLAGS=-Wall -c
DEBUG=-g

# Call the build routine
all: main

# Build the tree
main: bptree.o main.cpp
	$(CC) $(DEBUG) main.cpp -o main

bptree.o: bptree.hpp node.o
	$(CC) $(DEBUG) bptree.hpp -o bptree.o

node.o: node.hpp
	$(CC) $(DEBUG) node.hpp -o node.o

clean: fresh
	rm *.o main

fresh: 
	rm -rf nodes/*
	cp bplustree.config.bkp bplustree.config
