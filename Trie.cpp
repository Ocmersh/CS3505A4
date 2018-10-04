/*
 * Christopher Hanson
 * CS3505 Fall 2018, University of Utah
 * Assignment A3: A Trie and the Rule-of-Three
 *
 * Modified for A4: Testing and Travis
 * Refactoring by Christopher Hanson and Bryce Hansen
*/

//#include <iostream>
#include "Trie.h"

// FUNCTION: Constructs new Trie.
Trie::Trie() {
  for (int counter = 0; counter < 26; counter++) {
    branches[counter] = nullptr;
  }
  isEndOfValidWord = false;
}

// FUNCTION: Destructor
Trie::~Trie() {
  for (int counter = 0; counter < 26; counter++) {
    if (branches[counter]) {
      delete branches[counter];
    }
  }
}

// FUNCTION: Trie Copy constructor; Pass in Trie as reference, create deep copy.
Trie::Trie(const Trie& other) {
  // Initialize all branches to nullptr.
  for (int counter = 0; counter < 26; counter++) {
    branches[counter] = nullptr;
  }
  // Then, update if need be.
  isEndOfValidWord = other.isEndOfValidWord;
  for (int counter = 0; counter < 26; counter++) {
    if(other.branches[counter]) {
      branches[counter] = new Trie(*other.branches[counter]);
    }
  }
}

// FUNCTION: Trie assignment; Copies, swaps, deletes allocated memory
Trie& Trie::operator=(Trie trieToCopy) {
  isEndOfValidWord = trieToCopy.isEndOfValidWord;

  Trie* temp;
  for (int counter = 0; counter < 26; counter++) {
    // Swap pointers b/w local var copy and this
    temp = trieToCopy.branches[counter];
    trieToCopy.branches[counter] = branches[counter];
    branches[counter] = temp;
  }
  return *this;
}

// FUNCTION: Adds specified word to this Trie.
void Trie::addAWord(std::string word) {
  //std::cout << " \n";
  //std::cout << "Entered addAWord \n";
  Trie* currentTrie = this;
  char currentChar;

  // Iterate over the word, character by character, simultaneously moving from node
  // to node within the Trie, creating a new Trie when need be.
  for (unsigned int counter = 0; counter < word.length(); counter++) {
    //std::cout << "Entered the for loop in addAWord \n";
    currentChar = word[counter];
    //std::cout << "Attempting to add char " << currentChar << "\n";
    if (!currentTrie->branches[currentChar-97]) { // '-97' to convert from ASCII dec to index
      currentTrie->branches[currentChar-97] = new Trie();
    }
    currentTrie = currentTrie->branches[currentChar-97];
  }
  currentTrie->isEndOfValidWord = true; // End of word reached, set flag.
}

// FUNCTION: Returns bool indicating whether specified word is valid word in Trie.
bool Trie::isAWord(std::string wordToCheck) {
  Trie* currentTrie = this;
  char currentChar;
  // Iterate over wordToCheck and nodes in Trie
  for (unsigned int counter = 0; counter < wordToCheck.length(); counter++) {
    currentChar = wordToCheck[counter];
    if (!currentTrie->branches[currentChar-97]) {
      return false; // Node for curentChar does not exist, so word is not in Trie
    }
    currentTrie = currentTrie->branches[currentChar-97];
    if (counter == wordToCheck.length()-1 && currentTrie->isEndOfValidWord) {
      return true; // End of word reached, and bool indicates valid word.
    }
  }
  return false;
}

// FUNCTION: Returns vector containing all words in Trie starting with specified prefix.
std::vector<std::string> Trie::allWordsStartingWithPrefix(std::string prefix) {
  Trie* currentTrie = this;
  std::vector<std::string> toReturn;
  char currentChar;
  // Iterate over characters of prefix,
  for (unsigned int counter = 0; counter < prefix.length(); counter++) {
    currentChar = prefix[counter];
    if (!currentTrie->branches[currentChar-97]) {
      return toReturn;
    }
    currentTrie = currentTrie->branches[currentChar-97]; // Moving node-to-node
  } // Until the node at end of the prefix is reached.
  getAllWords(toReturn, currentTrie, prefix);
  return toReturn;
}

// FUNCTION: Helper function to get all words contained within a Trie. Placed in vector passed in by ref.
void Trie::getAllWords(std::vector<std::string>& collectionVector, Trie* theCurrentTrie, std::string theCurrentWord) {
  Trie* currentTrie = theCurrentTrie;
  if (currentTrie->isEndOfValidWord) {
    collectionVector.push_back(theCurrentWord);
  }
  for (int counter = 0; counter < 26; counter++) {
    if (currentTrie->branches[counter]) {
      std::string theNextWord = theCurrentWord += (counter+97);
      getAllWords(collectionVector, currentTrie->branches[counter], theNextWord);
      theCurrentWord = theCurrentWord.substr(0, theCurrentWord.length()-1);
    }
  }
}

// FUNCTON: Returns vector containing all word in Trie that start with specified wildcard prefix ('?' = any or no letter).
std::vector<std::string> Trie::wordsWithWildcardPrefix(std::string prefix) {
  std::vector<std::string> toReturn;
  std::vector<std::string> allPossiblePrefixes;
  char currentChar;
  // Assemble a vector containing a string for every prefix permitted by wildcard prefix
  for (unsigned int counter = 0; counter < prefix.length(); counter++)
  {
    currentChar = prefix[counter];
    // If '?' is encountered, add a new string for each letter of the alphabet for
    // each string already in the vector. Note that those already there are left,
    // to account for the case that '?' may mean no letter at all.
    if (currentChar == '?' && allPossiblePrefixes.size() > 0)
    {
      //std::cout << "encountered question mark ??? \n";
      for (std::string str : allPossiblePrefixes) {
        std::string temp;
        for (unsigned int counterTwo = 0; counterTwo < 26; counterTwo++) {
          temp = str;
          allPossiblePrefixes.push_back(temp += (counterTwo + 97));
        }
      }
    }
    else // Otherwise, concatenate the currentChar to all strings in the vector.
    {
      // Unless this is the first char in the prefix, then do init. preparation of vector.
      if (allPossiblePrefixes.size() < 1) {
        if (currentChar != '?') { // Add the single char if it is not '?'
          allPossiblePrefixes.push_back(std::string(1, currentChar));
        }
        else { // Add all 26 letters of alphabet if first char is '?'
          //std::cout << "Question mark encountered as first char " << std::endl;
          for (unsigned int counterTwo = 0; counterTwo < 26; counterTwo++) {
            allPossiblePrefixes.push_back(std::string(1, counterTwo + 97));
          }
          allPossiblePrefixes.push_back(""); // This line added in A4
        }
      }
      else { // Not first char in prefix, and not question mark, so simply concat to all existing prefixes
        for (std::string& str : allPossiblePrefixes) {
          str += currentChar;
        }
      }
    }
  }
  std::vector<std::string> temp;
  std::set<std::string> setOfAllMatchingWords; // Will be converted to vector for return

  // DEBuG
  //std::cout << "Length of allPossiblePrefixes: " << allPossiblePrefixes.size() << std::endl;
  //for (std::string theCurrentPrefix : allPossiblePrefixes) {
  //  std::cout << "theCurrentPrefix: " << theCurrentPrefix << std::endl;
  //}

  // Get all words that match every prefix possible based on wildCard prefix given
  for (std::string pref : allPossiblePrefixes) {
    temp = allWordsStartingWithPrefix(pref);
    for (std::string str : temp) {
      setOfAllMatchingWords.emplace(str); // Put words in set to avoid duplication
    }
  }
  // Copy contents of set to vector for toReturn
  for (std::string word : setOfAllMatchingWords) {
    toReturn.push_back(word);
  }
  return toReturn;
}
