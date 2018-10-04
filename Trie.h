#ifndef TRIE_H
#define TRIE_H
#include<string>
#include<vector>
#include<set>

class Trie {
private:
  Trie* branches[26];
  bool isEndOfValidWord;
  void getAllWords(std::vector<std::string>& collectionVector, Trie* targetTrie, std::string theCurrentWord);
public:
  Trie();
  ~Trie();
  Trie(const Trie& other);
  Trie& operator=(Trie trieToCopy);
  void addAWord(std::string word);
  bool isAWord(std::string wordToCheck);
  std::vector<std::string> allWordsStartingWithPrefix(std::string prefix);
  std::vector<std::string> wordsWithWildcardPrefix(std::string prefix);
};

#endif
