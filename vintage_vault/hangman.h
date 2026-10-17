// hangman.h
/*!
  @file hangman.h
  @brief Header file for the hangman game
  @author Nick Garner
 */


#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 100
#define MAX_TRIES 6
#define MAX_DICTIONARY_SIZE 10000

/*!
	 @brief Initializes the hangman game
*/
void hangmanInitialize(void);


/*!
	 @brief checks if letter is in word
	 @param letter The letter to check
	 @param word The word to check
	 @return 1 if the letter is in the word, 0 otherwise
*/
bool isLetterInWord(char letter, const char* word);

/*!
	 @brief Hangman unit tests
*/
void hangmanTests();


#ifdef UNIT_TESTING
// Expose these functions for unit testing
/*!
	 @brief Plays the hangman game
*/
void hangmanPlay(void);
/*!
	 @brief Selects a word from the dictionary based on the desired length
	 @param desired_length The desired length of the word
	 @return A pointer to the selected word

*/
char* selectWord(int desiredLength);
/*!
	 @brief Checks if a word has been guessed
	 @param guessed An array of integers representing the guessed letters
	 @param length The length of the word
	 @return 1 if the word has been guessed, 0 otherwise

*/
int isWordGuessed(const int* guessed, int length);
/*!
	 @brief Converts a string to uppercase
	 @param str The string to convert to uppercase

*/
void toUppercase(char* str);
/*!
	 @brief Sets the mock dictionary for testing
	 @param mock_dict The mock dictionary
	 @param size The size of the mock dictionary

*/
void setMockDictionary(const char mockDict[][MAX_WORD_LENGTH], int size);
/*!
	 @brief Loads the dictionary from a file
	 @param filename The name of the file to load
	 @return 1 if the dictionary was loaded successfully, 0 otherwise

*/
int loadDictionary(const char* filename, char dictionary[][MAX_WORD_LENGTH], int maxSize);
#endif

#endif // HANGMAN_H