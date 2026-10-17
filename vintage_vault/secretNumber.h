/*!
  @file secretNumber.h
  @brief Header file for the Secret Number game
  @author Rochelle Cole
 */
#ifndef SECRETNUMBER_H
#define SECRETNUMBER_H
#include <stdbool.h>


 /*!
    @brief Generates a random secret number between the lower and upper bounds
 */
int getSecretNumber(int lowerBound, int upperBound);

/*!
    @brief Runs all the tests for the secret number game
*/
int secNumTests();

/*!
    @brief Checks if the input for the difficulty level is valid
    @param difficulty The difficulty level taken from the input as a char
    @return true if the input is valid, false if it is not
*/
bool validDifficulty(char difficulty);

/*!
    @brief Gets the difficulty level from the user input
    @return The difficulty level chosen by the user as a char
*/
char getDifficulty(char difficulty, const char* mockInput = NULL, int mockInputSize = 0);

/*!
    @brief Checks if the input for a guess is valid
    @param guess The guess as an integer
    @param lowerBound The lower bound of the range for the secret number
    @param upperBound The upper bound of the range for the secret number
    @param check The number of guesses made
    @return true if the input is valid, false if it is not
*/
bool validGuess(int guess, int lowerBound, int upperBound, int check);


/*!
    @brief Gets the guess from input and checks if it is valid
    @param lowerBound The lower bound of the range for the secret number
    @param upperBound The upper bound of the range for the secret number
    @return The guess as an integer
*/
int getGuess(int lowerBound, int upperBound, const int* mockInput = NULL, int mockInputSize = 0);

/*!
    @brief Plays the game
    @param difficulty The difficulty level taken from input as a char
*/
void play(char difficulty);

/*!
    @brief Checks if the input for play again is valid
    @param playAgain The input for play again as a char
    @return true if the input is valid, false if it is not
*/
bool validPlayAgain(char playAgain);


/*!
    @brief Asks the user if they want to play again
    @return true if the user wants to play again, false if they do not
*/
bool playAgain(char playAgain);

/*!
    @brief Starts the game
*/
void secretNumberStart( );

#endif // SECRETNUMBER_H