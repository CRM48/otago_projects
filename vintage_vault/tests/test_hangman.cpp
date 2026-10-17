/*!
    @file test_hangman.cpp
	@brief Hangman Testing
    @author Nick Garner
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../hangman.h"
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <functional>
#include <cstdio>

// Simple test framework
#define TEST(name) static void test_##name(void)
#define RUN_TEST(name) do { \
    printf("Running %s...\n", #name); \
    test_##name(); \
    printf("%s passed!\n", #name); \
} while (0)

// Mock dictionary for testing
static const char mockDictionary[3][MAX_WORD_LENGTH] = { "APPLE", "BANANA", "CHERRY" };
static const int mockDictionarySize = 3;

/*!
    @brief Test for word selection function
*/
TEST(selectWord) {
    setMockDictionary(mockDictionary, mockDictionarySize);

    char* word = selectWord(0);
    assert(word != NULL);
    assert(strcmp(word, "APPLE") == 0 || strcmp(word, "BANANA") == 0 || strcmp(word, "CHERRY") == 0);

    word = selectWord(5);
    assert(strcmp(word, "APPLE") == 0);

    word = selectWord(6);
    assert(strcmp(word, "BANANA") == 0 || strcmp(word, "CHERRY") == 0);

    word = selectWord(10);
    assert(word != NULL);
}

/*!
    @brief Test to check correct guess
*/
TEST(isWordGuessed) {
    int guessed1[] = { 1, 1, 1, 1, 1 };
    assert(isWordGuessed(guessed1, 5) == 1);

    int guessed2[] = { 1, 1, 0, 1, 1 };
    assert(isWordGuessed(guessed2, 5) == 0);

    int guessed3[] = { 0, 0, 0, 0, 0 };
    assert(isWordGuessed(guessed3, 5) == 0);
}

/*!
    @brief Test for convertion to uppercase method
*/
TEST(toUppercase) {
    char word[] = "Hello, World!";
    toUppercase(word);
    assert(strcmp(word, "HELLO, WORLD!") == 0);

    char alreadyUpper[] = "UPPERCASE";
    toUppercase(alreadyUpper);
    assert(strcmp(alreadyUpper, "UPPERCASE") == 0);

    char empty[] = "";
    toUppercase(empty);
    assert(strcmp(empty, "") == 0);
}

/*!
    @brief Test for letter checking method
*/
TEST(isLetterInWord) {
    assert(isLetterInWord('A', "APPLE") == true);
    assert(isLetterInWord('Z', "APPLE") == false);
    assert(isLetterInWord('E', "HELLO") == true);
    assert(isLetterInWord('X', "") == false);
}

/*!
    @brief Test for dictionary loading method
*/
TEST(loadDictionary) {
    const char* tempFilename = "temp_dictionary.txt";
    FILE* tempFile;
    int result;
    char testDictionary[MAX_DICTIONARY_SIZE][MAX_WORD_LENGTH];

    // Test 1: Loading a non-existent file
    result = loadDictionary("non_existent_file.txt", testDictionary, MAX_DICTIONARY_SIZE);
    assert(result <= 0);

    // Test 2: Loading a valid file with various word lengths
    tempFile = fopen(tempFilename, "w");
    assert(tempFile != NULL);
    fprintf(tempFile, "apple\nBANANA\nCherry\ndate\nEGGPLANT\n");
    fclose(tempFile);

    result = loadDictionary(tempFilename, testDictionary, MAX_DICTIONARY_SIZE);
    assert(result == 5);
    assert(strcmp(testDictionary[0], "APPLE") == 0);
    assert(strcmp(testDictionary[1], "BANANA") == 0);
    assert(strcmp(testDictionary[2], "CHERRY") == 0);
    assert(strcmp(testDictionary[3], "DATE") == 0);
    assert(strcmp(testDictionary[4], "EGGPLANT") == 0);

    // Test 3: Loading a file with a word at MAX_WORD_LENGTH
    tempFile = fopen(tempFilename, "w");
    assert(tempFile != NULL);
    for (int i = 0; i < MAX_WORD_LENGTH - 1; i++) {
        fprintf(tempFile, "a");
    }
    fprintf(tempFile, "\n");
    fclose(tempFile);

    result = loadDictionary(tempFilename, testDictionary, MAX_DICTIONARY_SIZE);
    assert(result >= 1);
    assert(strlen(testDictionary[0]) == MAX_WORD_LENGTH - 1);

    // Test 4: Loading a file with more words than MAX_DICTIONARY_SIZE
    tempFile = fopen(tempFilename, "w");
    assert(tempFile != NULL);
    for (int i = 0; i < MAX_DICTIONARY_SIZE + 10; i++) {
        fprintf(tempFile, "word%d\n", i);
    }
    fclose(tempFile);

    result = loadDictionary(tempFilename, testDictionary, MAX_DICTIONARY_SIZE);
    assert(result == MAX_DICTIONARY_SIZE);

    // Test 5: Loading an empty file
    tempFile = fopen(tempFilename, "w");
    assert(tempFile != NULL);
    fclose(tempFile);

    result = loadDictionary(tempFilename, testDictionary, MAX_DICTIONARY_SIZE);
    assert(result == 0);

    // Clean up
    remove(tempFilename);
}

void hangmanTests() {
    printf("Running Hangman unit tests...\n");

    RUN_TEST(loadDictionary);
    RUN_TEST(selectWord);
    RUN_TEST(isWordGuessed);
    RUN_TEST(toUppercase);
    RUN_TEST(isLetterInWord);


    printf("All tests passed!\n");
}
// compile and run with:
// gcc hangman.cpp test_hangman.cpp -o test_hangman.cpp -DUNIT_TESTING
// ./test_hangman