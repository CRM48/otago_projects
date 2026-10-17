/*!
  @file secretNumTests.cpp
  @brief Secret Number Testing
  @author Rochelle Cole
 */
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "../secretNumber.h" // Include the header file

// Function to run all tests
void runTests();

// Test functions
void test_getSecretNumber();
void test_validDifficulty();
void test_getDifficulty();
void test_validGuess();
void test_validPlayAgain();
void test_playAgain();
void test_getGuess_withMockInput();
void test_getDifficulty_withMockInput();

// Function to Print test results
void printTestResult(const char* testName, bool result);

/*!
  @brief Main test function that's called by the main test file
 */
int secNumTests() {
    runTests();
    return 0;
}

/*!
  @brief Called function that runs all test functions
 */
void runTests() {
    test_getSecretNumber();
    test_validDifficulty();
    test_getDifficulty();
    test_validGuess();
    test_validPlayAgain();
    test_playAgain();
    test_getGuess_withMockInput();
    test_getDifficulty_withMockInput();
}

/*!
  @brief Tests the valdity of a retrieval of a random secret number
 */
void test_getSecretNumber() {
    int lowerBound = 1;
    int upperBound = 10;
    int secretNumber = getSecretNumber(lowerBound, upperBound);
    bool result = (secretNumber >= lowerBound && secretNumber <= upperBound);
    printTestResult("test_getSecretNumber", result);
}

/*!
  @brief Main test function that's called by the main test file
 */
void test_validDifficulty() {
    bool result = validDifficulty('e') && validDifficulty('m') && validDifficulty('h') && !validDifficulty('x');
    printTestResult("test_validDifficulty", result);
}

/*!
  @brief Tests the validity of the return of a difficulty input
 */
void test_getDifficulty(){
    bool result = getDifficulty('E') == 'e' && getDifficulty('m') == 'm';
    printTestResult("test_getDifficulty", result);
}

/*!
  @brief Tests the guess validity function
 */
void test_validGuess() {
    bool result = validGuess(5, 1, 10, 1) && !validGuess(15, 1, 10, 1);
    printTestResult("test_validGuess", result);
}

/*!
  @brief Tests the function that checks a valid answer for the play again function
 */
void test_validPlayAgain() {
    bool result = validPlayAgain('y') && validPlayAgain('n') && !validPlayAgain('x') && validPlayAgain('Y') && validPlayAgain('N');
    printTestResult("test_validPlayAgain", result);
}

/*!
  @brief Tests the function that asks the user to play again
 */
void test_playAgain(){
    bool result = playAgain('y') == true && playAgain('n') == false;
    printTestResult("test_playAgain", result);
}

/*!
  @brief Tests the function that gets the users guess
 */
void test_getGuess_withMockInput() {
    const int mockGuesses[] = { 5, 7}; 
    int mockGuessCount = sizeof(mockGuesses) / sizeof(mockGuesses[0]);

    int guess = getGuess(1, 10, mockGuesses, mockGuessCount);

    bool result = (guess == 5);
    printTestResult("test_getGuess_withMockInput", result);
}

/*!
  @brief Tests the function that gets user input for difficulty
 */
void test_getDifficulty_withMockInput() {
    const char mockInputs[] = {'x', 'm'}; 
    int mockInputCount = sizeof(mockInputs) / sizeof(mockInputs[0]);

    char difficulty = getDifficulty(' ', mockInputs, mockInputCount);

    bool result = (difficulty == 'm');
    printTestResult("test_getDifficulty_withMockInput", result);
}

/*!
  @brief Prints out the results from testing
 */
void printTestResult(const char* testName, bool result) {
    if (result) {
        printf("%s: PASSED\n", testName);
    } else {
        printf("%s: FAILED\n", testName);
    }
}