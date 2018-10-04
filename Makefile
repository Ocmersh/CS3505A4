# Christopher Hanson
# CS3505 Fall 2018, University of Utah
# Assignment A3: A Trie and the Rule-of-Three

CC = g++
CFLAGS = -Wall -fsanitize=address -fsanitize=undefined

Trie.o : Trie.h Trie.cpp
	$(CC) $(CFLAGS) -c Trie.h Trie.cpp

TrieTest : TrieTest.cpp Trie.o
	$(CC) $(CFLAGS) -o TrieTest TrieTest.cpp Trie.o

clean:
	rm -f *.o *.a *.h.gch test

test:
	./TrieTest "dictionary.txt" "query.txt"
