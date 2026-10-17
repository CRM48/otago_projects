/*!
	@file test_newwordle.cpp
	@brief Wordle Testing
	@author Connor Johnstone
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../newwordle.h"


// Wordle test


// Simple test framework
#define TEST(name) static void test_##name(void)
#define RUN_TEST(name) do { \
    printf("Running %s...\n", #name); \
    test_##name(); \
    printf("%s passed!\n", #name); \
} while (0)

static const char wordle_mock_dictionary[3][MAX_wordle_WORD_LENGTH] = { "apple", "green", "slack" };
static const int wordle_mock_dictionary_size = 3;
extern bool has_letter_been_guessed[26];
extern char guessone[6], guesstwo[6], guessthree[6], guessfour[6], guessfive[6], guesssix[6];
extern char clueone[6], cluetwo[6], cluethree[6], cluefour[6], cluefive[6], cluesix[6];


/*!
    @brief Test for function that checks for only valid characters
*/
TEST(conatainsonlychar) {

    assert(conatainsonlychar("al-ha") == false);
    assert(conatainsonlychar("alpha") == true);

}

/*!
    @brief Test for conversion to lowercase function
*/
TEST(toLowerCase) {

    const char* guess = "HELLO";
    char* lower = toLowerCase(guess);
    assert(strcmp(lower, "hello") == 0);

    const char* alreadylower = "hello";
    char* newlower = toLowerCase(alreadylower);
    assert(strcmp(newlower, "hello") == 0);
}

/*!
    @brief Test for function that compares guess to word
*/
TEST(processGuess) {
    const char* answer = "apple";
    const char* guess = "anvil";
    assert(strcmp(processGuess(answer, guess), "G___Y") == 0);

    const char* sec_guess = "piper";
    assert(strcmp(processGuess(answer, sec_guess), "Y_GY_") == 0);

    const char* third_guess = "apple";
    assert(strcmp(processGuess(answer, third_guess), "GGGGG") == 0);
}

/*!
    @brief Test for valid word length function
*/
TEST(correctlength) {
    assert(correctlength("hello") == true);
    assert(correctlength("hell") == false);
    assert(correctlength("helloo") == false);
}

/*!
    @brief Test for word validity function
*/
TEST(validWord) {
    set_wordle_mock_dictionary(wordle_mock_dictionary, wordle_mock_dictionary_size);
    assert(validWord("aaple") == false);
    assert(validWord("apple") == true);
}

/*!
    @brief Test for word retrieval function
*/
TEST(get_word) {
    set_wordle_mock_dictionary(wordle_mock_dictionary, wordle_mock_dictionary_size);
    assert(strcmp(get_word(0), "apple") == 0);
    assert(strcmp(get_word(4), "green") == 0);
    assert(strcmp(get_word(2), "slack") == 0);

}

/*!
    @brief Test for the function that updates the guessed letters
*/
TEST(updateLettersGuessed) {
    // Reset the has_letter_been_guessed array before each test
    memset(has_letter_been_guessed, 0, sizeof(has_letter_been_guessed));

    // Example guess with some letters
    const char* guess = "maple";
    updateLettersGuessed(guess);


    assert(has_letter_been_guessed['m' - 'a'] == true);
    assert(has_letter_been_guessed['a' - 'a'] == true);
    assert(has_letter_been_guessed['p' - 'a'] == true);
    assert(has_letter_been_guessed['l' - 'a'] == true);
    assert(has_letter_been_guessed['e' - 'a'] == true);


    assert(has_letter_been_guessed['b' - 'a'] == false);
    assert(has_letter_been_guessed['c' - 'a'] == false);
    assert(has_letter_been_guessed['f' - 'a'] == false);

}




/*!
    @brief Test for function that checks letters that haven't been guessed
*/
TEST(lettersNotGuessed) {

    memset(has_letter_been_guessed, 0, sizeof(has_letter_been_guessed));

   
    

    // Example guess with some letters
    const char* guess = "maple";
    updateLettersGuessed(guess);

    // Get the letters not guessed
    char* notGuessed = lettersNotGuessed();

    // Expected result after guessing "maple": 'b', 'c', 'd', 'f', ..., 'z' should be present
    assert(strchr(notGuessed, 'b') != NULL);
    assert(strchr(notGuessed, 'c') != NULL);
    assert(strchr(notGuessed, 'd') != NULL);
    assert(strchr(notGuessed, 'f') != NULL);
    // Check specific letters that were guessed
    assert(strchr(notGuessed, 'm') == NULL);
    assert(strchr(notGuessed, 'a') == NULL);
    assert(strchr(notGuessed, 'p') == NULL);
    assert(strchr(notGuessed, 'l') == NULL);
    assert(strchr(notGuessed, 'e') == NULL);

    free(notGuessed); // Free memory allocated by lettersNotGuessed
}

/*!
    @brief Test for the update word each round function
*/
TEST(updateclue) {
    memset(clueone, 0, sizeof(clueone));
    memset(guessone, 0, sizeof(guessone));
    memset(cluetwo, 0, sizeof(cluetwo));
    memset(guesstwo, 0, sizeof(guesstwo));
    memset(cluethree, 0, sizeof(cluethree));
    memset(guessthree, 0, sizeof(guessthree));
    memset(cluefour, 0, sizeof(cluefour));
    memset(guessfour, 0, sizeof(guessfour));

    memset(cluefive, 0, sizeof(cluefive));
    memset(guessfive, 0, sizeof(guessfive));
    memset(cluesix, 0, sizeof(cluesix));
    memset(guesssix, 0, sizeof(guesssix));


    int turn = 1;
    const char* answer = "grave";
    const char* guess = "maple";
    char* clue = processGuess(answer, guess);


    updateclue(turn, clue, guess);


    turn = 2;
    guess = "stale";
    clue = processGuess(answer, guess);

    updateclue(turn, clue, guess);

    turn = 3;
    guess = "crane";
    clue = processGuess(answer, guess);

    updateclue(turn, clue, guess);



    turn = 4;
    guess = "nudge";
    clue = processGuess(answer, guess);
    updateclue(turn, clue, guess);


    
    turn = 5;
    guess = "brave";
    clue = processGuess(answer, guess);
    updateclue(turn, clue, guess);

    turn = 6;
    guess = "grave";
    clue = processGuess(answer, guess);
    updateclue(turn, clue, guess);
    assert(strcmp(clueone, "_Y__G") == 0);
    assert(strcmp(guessone, "maple") == 0);
    assert(strcmp(cluetwo, "__G_G") == 0);
    assert(strcmp(guesstwo, "stale") == 0);
    assert(strcmp(cluethree, "_GG_G") == 0);
    assert(strcmp(guessthree, "crane") == 0);
    assert(strcmp(cluefour, "___YG") == 0);
    assert(strcmp(guessfour, "nudge") == 0);
    assert(strcmp(cluefive, "_GGGG") == 0);
    assert(strcmp(guessfive, "brave") == 0);
    assert(strcmp(cluesix, "GGGGG") == 0);
    assert(strcmp(guesssix, "grave") == 0);
}


TEST(gamereset) {
    memset(clueone, 0, sizeof(clueone));
    memset(guessone, 0, sizeof(guessone));
    memset(cluetwo, 0, sizeof(cluetwo));
    memset(guesstwo, 0, sizeof(guesstwo));
    memset(cluethree, 0, sizeof(cluethree));
    memset(guessthree, 0, sizeof(guessthree));
    memset(cluefour, 0, sizeof(cluefour));
    memset(guessfour, 0, sizeof(guessfour));

    memset(cluefive, 0, sizeof(cluefive));
    memset(guessfive, 0, sizeof(guessfive));
    memset(cluesix, 0, sizeof(cluesix));
    memset(guesssix, 0, sizeof(guesssix));
    gamereset();
    assert(strcmp(clueone, "_____") == 0);
    assert(strcmp(guessone, "_____") == 0);
    assert(strcmp(cluetwo, "_____") == 0);
    assert(strcmp(guesstwo, "_____") == 0);
    assert(strcmp(cluethree, "_____") == 0);
    assert(strcmp(guessthree, "_____") == 0);
    assert(strcmp(cluefour, "_____") == 0);
    assert(strcmp(guessfour, "_____") == 0);
    assert(strcmp(cluefive, "_____") == 0);
    assert(strcmp(guessfive, "_____") == 0);
    assert(strcmp(cluesix, "_____") == 0);
    assert(strcmp(guesssix, "_____") == 0);


}

/*!
    @brief Main test function to run all tests
*/
int runwordletests() {
    printf("Running Wordle unit tests...\n");

    RUN_TEST(conatainsonlychar);
    RUN_TEST(toLowerCase);
    RUN_TEST(processGuess);
    RUN_TEST(correctlength);
    RUN_TEST(validWord);
    RUN_TEST(get_word);
    RUN_TEST(updateLettersGuessed);
    RUN_TEST(lettersNotGuessed);
    RUN_TEST(updateclue);
    RUN_TEST(gamereset);

    printf("All tests passed!\n");
    return 0;
}


