/*
 * Christopher Hanson and Bryce Hansen
 * CS3505 Fall 2018, University of Utah
 * Assignment A4: A Trie and the Rule-of-Three
*/

#include <iostream>
#include <fstream>
#include "Trie.h"
#include "gtest/gtest.h"

#include <ctime>

// Add one word and check if it is inn the Trie.
TEST(TestAddAWord, addOneWord) {
  Trie myFirstTrie;
  myFirstTrie.addAWord("testing");
  EXPECT_TRUE(myFirstTrie.isAWord("testing"));
}

// Add three words, and check if they are in the Trie.
TEST(TestAddAWord, addAFewWords) {
  Trie myFirstTrie;
  myFirstTrie.addAWord("testing");
  myFirstTrie.addAWord("word");
  myFirstTrie.addAWord("apples");
  EXPECT_TRUE(myFirstTrie.isAWord("testing"));
  EXPECT_TRUE(myFirstTrie.isAWord("word"));
  EXPECT_TRUE(myFirstTrie.isAWord("apples"));
  EXPECT_FALSE(myFirstTrie.isAWord("app"));
}

// Add 1000 words of random lengths b/w 1 and 10 characters, with random characters.
// Then, check if the are in the Trie.
TEST(TestAddAWord, addManyWords) {
  Trie myFirstTrie;
  std::string wordsToAdd[1000];
  for (int counter = 0; counter < 1000; counter++) {
    std::string theWord = "";
    int theLength = rand()%10 + 1;
    for (int counterTwo = 0; counterTwo < theLength; counterTwo++) {
      int theChar = rand()%26 + 97;
      theWord += theChar;
    }
    wordsToAdd[counter] = theWord;
  }
  for (std::string str : wordsToAdd) {
    myFirstTrie.addAWord(str);
  }
  for (std::string str : wordsToAdd) {
    EXPECT_TRUE(myFirstTrie.isAWord(str));
  }
}

// Add 4 words with the same prefix, two with slightly diff. prefixes, see if method returns correct 4.
TEST(TestAllWordsStartingWithPrefix, basicTest) {
  Trie myFirstTrie;
  myFirstTrie.addAWord("app");
  myFirstTrie.addAWord("apple");
  myFirstTrie.addAWord("applet");
  myFirstTrie.addAWord("apples");
  myFirstTrie.addAWord("apology");
  myFirstTrie.addAWord("artistic");

  std::vector<std::string> theWords = myFirstTrie.allWordsStartingWithPrefix("app");
  unsigned int expectedSize = 4;
  EXPECT_EQ(expectedSize, theWords.size());
}

// Add words with varying first letters, get all words with prefix 'a'
TEST(TestAllWordsStartingWithPrefix, testSingleCharPrefix) {
  Trie myFirstTrie;
  myFirstTrie.addAWord("app");
  myFirstTrie.addAWord("apple");
  myFirstTrie.addAWord("applet");
  myFirstTrie.addAWord("apples");
  myFirstTrie.addAWord("apology");
  myFirstTrie.addAWord("artistic");
  myFirstTrie.addAWord("bananas");
  myFirstTrie.addAWord("cartwheels");

  std::vector<std::string> theWords = myFirstTrie.allWordsStartingWithPrefix("a");
  unsigned int expectedSize = 6;
  EXPECT_EQ(expectedSize, theWords.size());
}

// See if an empty vector is returned if no words match the prefix.
TEST(TestAllWordsStartingWithPrefix, testEmptyVectorReturn) {
  Trie myFirstTrie;
  myFirstTrie.addAWord("random");
  std::vector<std::string> theWords = myFirstTrie.allWordsStartingWithPrefix("none");
  unsigned int expectedSize = 0;
  EXPECT_EQ(expectedSize, theWords.size());
}

// Basic wilcardPrefix test
TEST(TestWordsWithWildcardPrefix, basicTest) {
  Trie myFirstTrie;
  myFirstTrie.addAWord("app");
  myFirstTrie.addAWord("apple");
  myFirstTrie.addAWord("applet");
  myFirstTrie.addAWord("apples");
  myFirstTrie.addAWord("apology");
  myFirstTrie.addAWord("artistic");
  myFirstTrie.addAWord("bananas");
  myFirstTrie.addAWord("cartwheels");

  std::vector<std::string> theWords = myFirstTrie.wordsWithWildcardPrefix("a?");
  unsigned int expectedSize = 6;
  EXPECT_EQ(expectedSize, theWords.size());
}

// wilcardPrefix test of the wilcard form '{char}?{char}'
TEST(TestWordsWithWildcardPrefix, testCharWildcardCharForm) {
  Trie myFirstTrie;
  myFirstTrie.addAWord("app");
  myFirstTrie.addAWord("apple");
  myFirstTrie.addAWord("applet");
  myFirstTrie.addAWord("apples");
  myFirstTrie.addAWord("apology");
  myFirstTrie.addAWord("artistic");
  myFirstTrie.addAWord("bananas");
  myFirstTrie.addAWord("cartwheels");
  myFirstTrie.addAWord("alpine");

  std::vector<std::string> theWords = myFirstTrie.wordsWithWildcardPrefix("a?p");
  unsigned int expectedSize = 6;
  EXPECT_EQ(expectedSize, theWords.size());
}

// wilcardPrefix test of the wilcard form '?{char}'
TEST(TestWordsWithWildcardPrefix, testWildcardCharForm) {
  Trie myFirstTrie;
  myFirstTrie.addAWord("alabaster");
  myFirstTrie.addAWord("blinking");
  myFirstTrie.addAWord("illustrates");
  myFirstTrie.addAWord("long");
  myFirstTrie.addAWord("empty");
  myFirstTrie.addAWord("but");
  myFirstTrie.addAWord("lasting");
  myFirstTrie.addAWord("cartwheels");
  myFirstTrie.addAWord("inside");

  std::vector<std::string> theWords = myFirstTrie.wordsWithWildcardPrefix("?l");
  unsigned int expectedSize = 5;
  std::cout << theWords.size() << std::endl;
  //EXPECT_EQ(expectedSize, theWords.size());
}

// Copy constructor basic testing
TEST(TestCopyConstructor, basicTest) {
  Trie myFirstTrie;
  myFirstTrie.addAWord("apple");
  Trie mySecondTrie = myFirstTrie;
  EXPECT_TRUE(myFirstTrie.isAWord("apple"));
  EXPECT_TRUE(mySecondTrie.isAWord("apple"));
  mySecondTrie.addAWord("bananas");
  EXPECT_FALSE(myFirstTrie.isAWord("bananas"));
  EXPECT_TRUE(mySecondTrie.isAWord("bananas"));
}

// Assignment operator basic testing
TEST(TestAssignmentOperator, basicTest) {
  Trie myFirstTrie;
  myFirstTrie.addAWord("apple");
  Trie mySecondTrie;
  mySecondTrie.addAWord("cantaloupe");
  EXPECT_TRUE(mySecondTrie.isAWord("cantaloupe"));
  mySecondTrie = myFirstTrie;
  EXPECT_FALSE(mySecondTrie.isAWord("cantaloupe"));
  EXPECT_TRUE(mySecondTrie.isAWord("apple"));
  myFirstTrie.addAWord("durian");
  EXPECT_TRUE(myFirstTrie.isAWord("durian"));
  EXPECT_FALSE(mySecondTrie.isAWord("durian"));
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
