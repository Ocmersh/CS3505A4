/*
 * Christopher Hanson
 * CS3505 Fall 2018, University of Utah
 * Assignment A3: A Trie and the Rule-of-Three
*/

#include <iostream>
#include <fstream>
#include "Trie.h"

void debug_addWordToTheTrie(Trie& theTrie, std::string word) {
  std::cout << "adding word " << word << " to myFirstTrie \n";
  theTrie.addAWord(word);
  std::cout << "Word " << word << " successfully added \n";
}
void debug_allWordsStartingWithThePrefix(Trie& theTrie, std::string prefix) {
  std::vector<std::string> testVector = theTrie.allWordsStartingWithPrefix(prefix);
  std::cout << "Printing vector for trie with prefix " << prefix << " \n";
  for (std::string s : testVector) {
    std::cout << s << "\n";
  }
  std::cout << "Completed printing vector for trie with prefix " << prefix << " \n";
}
void debug_isAWord(Trie& theTrie, std::string wordToCheck) {
  std::vector<std::string> testVector;

  //std::cout << "Checking if " << wordToCheck << " is a word \n";
  bool itIsAWord = theTrie.isAWord(wordToCheck);
  //std::cout << wordToCheck << " is a word: " << itIsAWord << " \n";
  if (itIsAWord) {
    std::cout << wordToCheck << " is found" << std::endl;
  }
  else {
    std::cout << wordToCheck << " is not found, did you mean:" << std::endl;
    testVector = theTrie.allWordsStartingWithPrefix(wordToCheck);
    if (testVector.size() < 1) {
      std::cout << "   no alternatives found" << std::endl;
    }
    else {
      for (std::string s : testVector) {
        std::cout << "   " << s << std::endl;
      }
    }
  }
}
void debug_wordsWithWildcardPrefix(Trie& theTrie, std::string prefix) {
  std::vector<std::string> testVector = theTrie.wordsWithWildcardPrefix(prefix);
  std::cout << "Printing vector for trie with wildcard prefix " << prefix << " \n";
  std::cout << "Number of words found: " << testVector.size() << std::endl;
  for (std::string s : testVector) {
    std::cout << s << "\n";
  }
  std::cout << "Completed printing vector for trie with wildcard prefix " << prefix << " \n";
}

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cout << "At least one filename of dictionary or query file not provided. \n";
    std::cout << "Exiting... \n";
    return 0;
  }
  std::cout << "Dictionary file: " << argv[1] << "\n";
  std::cout << "Query file: " << argv[2] << "\n";

  std::string wordToAdd;
  std::string wordToLookFor;
  std::vector<std::string> testVector;
  Trie myFirstTrie;

  // Add words in dicitonary file to Trie
  std::ifstream dictFile(argv[1]);
  if (dictFile.is_open()) {
    while (getline(dictFile, wordToAdd)) {
      debug_addWordToTheTrie(myFirstTrie, wordToAdd);
    }
  }
  else {
    std::cout << "Could not open file. \n";
    std::cout << "Exiting... \n";
    return 0;
  }

  // Run queries from query file
  std::ifstream querFile(argv[2]);
  if (querFile.is_open()) {
    while (getline(querFile, wordToLookFor)) {
      debug_isAWord(myFirstTrie, wordToLookFor);
    }
  }

  // Test copy constructor
  Trie mySecondTrie = myFirstTrie;
  debug_isAWord(myFirstTrie, "apple");
  debug_isAWord(mySecondTrie, "apple");

  // Test assignment operator
  Trie myThirdTrie;
  debug_addWordToTheTrie(myThirdTrie, "pencil");
  mySecondTrie = myThirdTrie;
  debug_isAWord(myThirdTrie, "pencil");
  debug_isAWord(mySecondTrie, "pencil");

  // Test wordsWithWildcardPrefix method
  Trie myFourthTrie;
  debug_addWordToTheTrie(myFourthTrie, "penny");
  debug_addWordToTheTrie(myFourthTrie, "pencil");
  debug_addWordToTheTrie(myFourthTrie, "pinwheel");
  debug_addWordToTheTrie(myFourthTrie, "penne");
  debug_addWordToTheTrie(myFourthTrie, "bins");
  debug_addWordToTheTrie(myFourthTrie, "pancreas");
  debug_addWordToTheTrie(myFourthTrie, "arkansas");
  debug_addWordToTheTrie(myFourthTrie, "pork");

  debug_wordsWithWildcardPrefix(myFourthTrie, "p?n");
  debug_allWordsStartingWithThePrefix(myFourthTrie, "pen");

  debug_wordsWithWildcardPrefix(myFourthTrie, "?en");

  return 0;
}
