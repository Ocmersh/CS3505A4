# Christopher Hanson and Bryce Hansen
# CS3505 Fall 2018, University of Utah
# Assignment A4: Travis and Testing

CC = g++
CFLAGS = -Wall -fsanitize=address -fsanitize=undefined
GOOGLETEST ?= ../googletest/googletest

Trie.o : Trie.h Trie.cpp
	$(CC) $(CFLAGS) -c Trie.h Trie.cpp

TrieTests : TrieTests.cpp Trie.o
	$(CC) $(CFLAGS) -I $(GOOGLETEST)/include TrieTests.cpp Trie.o -o TrieTests -L $(GOOGLETEST)/lib -lgtest -lpthread

clean:
	rm -f *.o *.a *.h.gch test

test:
	./TrieTests
