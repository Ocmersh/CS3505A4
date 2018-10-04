# Christopher Hanson
# CS3505 Fall 2018, University of Utah
# Assignment A3: A Trie and the Rule-of-Three

CC = g++
CFLAGS = -Wall -fsanitize=address -fsanitize=undefined
GOOGLETEST = ../googletest/googletest

Trie.o : Trie.h Trie.cpp
	$(CC) $(CFLAGS) -c Trie.h Trie.cpp

TrieTests : TrieTests.cpp Trie.o
	$(CC) $(CFLAGS) -o TrieTests TrieTests.cpp Trie.o -I $(GOOGLETEST)/include -L $(GOOGLETEST)/lib

clean:
	rm -f *.o *.a *.h.gch test

test:
	./TrieTests
