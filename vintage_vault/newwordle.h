#ifndef wordle_H
#define wordle_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <cstdlib> 
#include <ctime> 

#define MAX_wordle_WORD_LENGTH 100

#define MAX_wordle_DICTIONARY_SIZE 4695

extern bool* test_has_letter_been_guessed;
extern char guessone[6];
extern char guesstwo[6];
extern char guessthree[6];
extern char guessfour[6];
extern char guessfive[6];
extern char guesssix[6];
extern char clueone[6];
extern char cluetwo[6];
extern char cluethree[6];
extern char cluefour[6];
extern char cluefive[6];
extern char cluesix[6];







/*!
	@file
	@brief documentation
*/

/*!
	@brief Initializes the Wordle game

*/
void wordle_initialize(void);

/*!
	@brief gets a random 5 letter word from the text file
	@param number is the index to get the word
	@return the word at that index.
*/
char* get_word(int desiredength);

/*!
	@brief Loads the wordlength5 from a file
	@param filename The name of the file to load
	@return 1 if the text file was loaded successfully, 0 otherwise
*/
int load_all_5letter_words(const char* filename);


/*!
	@brief plays wordle game
*/
void playWordle(void);
/*!
	@brief checks if user input is a word
	@param the user input
	@return true if it is a word falsw if not
*/
bool validWord(const char* guess);
/*!
	@brief compares user guess to the answer
	@param the answer
	@param the users guess
	@return a string of the user guess G if letter is in correct location, Y if not in correct, _ if letter not present in answer
*/

char* processGuess(const char* theWord, const char* theGuess);
/*!
	@brief converts input to lowercase
	@param the user input
	@return the user input in lower case
*/
char* toLowerCase(const char* guess);
/*!
	@brief checks if user input contains only letters
	@param the user input
	@return true if it does contain onyl char false if not
*/
bool conatainsonlychar(const char* guess);
/*!
	@brief checks if user input is 5 letters long
	@param the user input
	@return true if it is correct length  false if not
*/
bool correctlength(const char* guess);
/*!
	@brief updates the letters the user has guessed to be prepared to display the letters not guessed
	@param the users guess
*/

void updateLettersGuessed(const char* theGuess);
/*!
	@brief  gets all the letters the user has not guessed
	@return a the letters that havw not been guessed
*/

char* lettersNotGuessed();
/*!
	@brief a method for storing previous guesses and clues to be diplayed later
	@param the turn number
	@param the clue from the current turn
	@param the users guess from the current turn
*/

void updateclue(int turn, char* clue, const char* newguess);
/*!
	@brief prints the game
	@param an clue to be used to choose colour of letter
	@param the users guess
*/

void print_colored_output(char clue[], char guess[], bool colourblind);


/*!
	@brief ask the user if they are colour blind or not
	@return true if user is  colour blind and false if they are not.
*/

bool getcolourblindess();

/*!
	@brief resets the games
*/

void gamereset();


int runwordletests();
#ifdef UNIT_TESTING
// Expose these functions for unit testing
char* processGuess(const char* theWord, const char* theGuess);
char* toLowerCase(const char* guess);
bool conatainsonlychar(const char* guess);
bool conatainsonlychar(const char* guess);
bool validWord(const char* guess);
char* get_word(int number);
void set_wordle_mock_dictionary(const char mock_dict[][MAX_wordle_WORD_LENGTH], int size);
void updateLettersGuessed(const char* theGuess);
char* lettersNotGuessed();
void updateclue(int turn, char* clue, const char* newguess);
void gamereset();


//void resetTestArrays();
#endif

#endif // wordle_H