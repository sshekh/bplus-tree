CC=g++ -std=gnu++11
CFLAGS=-Wall -c
DEBUG=-g

# Call the build routine
all: tree.out

# Start fresh
fresh: clean-files tree.out

# Build the tree
tree.out: bptree.o
	$(CC) bptree.o -o tree.out

bptree.o: bptree.hpp node.hpp
	$(CC) $(CFLAGS) bptree.hpp node.hpp

setup-files: clean-files
	rm *.o *.out

clean-files: 
	rm -rf nodes/*
