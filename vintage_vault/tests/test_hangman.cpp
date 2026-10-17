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
#include <windows.h>

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

/*!
    @brief Test for main play function
*/
TEST(hangmanPlay) {
    // Mock dictionary setup
    const char mockDict[][MAX_WORD_LENGTH] = {
        "APPLE",
        "BANANA",
        "CHERRY",
        "ORANGE"
    };
    int mockDictSize = sizeof(mockDict) / sizeof(mockDict[0]);
    setMockDictionary(mockDict, mockDictSize);

    // Prepare input file
    FILE* tempInput = fopen("temp_input.txt", "w");
    if (tempInput == NULL) {
        perror("Error opening temp_input.txt");
        return;
    }
    // Updated input to match new requirements
    fprintf(tempInput, "5\nA\nP\nL\nE\nn\n");
    fclose(tempInput);

    // Redirect stdin and stdout
    FILE* newStdin = freopen("temp_input.txt", "r", stdin);
    FILE* newStdout = freopen("temp_output.txt", "w", stdout);
    if (newStdin == NULL || newStdout == NULL) {
        perror("Error redirecting stdin/stdout");
        if (newStdin) fclose(newStdin);
        if (newStdout) fclose(newStdout);
        return;
    }

    // Run the game
    hangmanPlay();

    // Close redirected streams
    fclose(newStdin);
    fclose(newStdout);

    // Reopen stdin and stdout to their default streams
    FILE* consoleIn = freopen("CON", "r", stdin);
    FILE* consoleOut = freopen("CON", "w", stdout);
    if (consoleIn == NULL || consoleOut == NULL) {
        perror("Error restoring stdin/stdout");
        return;
    }

    // Verify output
    FILE* outputFile = fopen("temp_output.txt", "r");
    if (outputFile == NULL) {
        perror("Error opening temp_output.txt");
        return;
    }

    char output[1000];  // Increased buffer size
    size_t bytesRead = fread(output, 1, sizeof(output) - 1, outputFile);
    output[bytesRead] = '\0';
    fclose(outputFile);

    // Check if the output contains expected strings
    assert(strstr(output, "Welcome to Hangman!") != NULL);
    assert(strstr(output, "Word: _ _ _ _ _") != NULL);
    assert(strstr(output, "Congratulations!") != NULL);
    assert(strstr(output, "Thanks for playing Hangman!") != NULL);

    // Clean up
    remove("temp_input.txt");
    remove("temp_output.txt");
}

void hangmanTests() {
    printf("Running Hangman unit tests...\n");

    RUN_TEST(loadDictionary);
    RUN_TEST(selectWord);
    RUN_TEST(isWordGuessed);
    RUN_TEST(toUppercase);
    RUN_TEST(isLetterInWord);
    RUN_TEST(hangmanPlay);


    printf("All tests passed!\n");
}
// compile and run with:
// gcc hangman.cpp test_hangman.cpp -o test_hangman.cpp -DUNIT_TESTING
// ./test_hangman