/*!
	@file newWordle.cpp
	@brief Wordle implementation
	@author Connor Johnstone
*/


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


// Remove static keyword for functions to be tested
#ifdef UNIT_TESTING
#define STATIC
#else
#define STATIC static
#endif


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BRIGHT_YELLOW  "\x1b[93m"
#define ANSI_COLOR_RESET   "\x1b[0m"


#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_MAGENTA     "\x1b[35m"


#define MAX_wordle_WORD_LENGTH 100
#define MAX_wordle_DICTIONARY_SIZE 4695


int word_length = 5;
// Global variables
static char wordle_dictionary[MAX_wordle_DICTIONARY_SIZE][MAX_wordle_WORD_LENGTH];
static int wordle_dictionary_size = 0;
extern bool has_letter_been_guessed[26];
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
//bool* test_has_letter_been_guessed = nullptr;
char guessone[6] = { '_', '_', '_', '_','_', '\0' };
char guesstwo[6] = { '_', '_', '_', '_','_', '\0' };
char guessthree[6] = { '_', '_', '_', '_','_', '\0' };
char guessfour[6] = { '_', '_', '_', '_','_', '\0' };
char guessfive[6] = { '_', '_', '_', '_','_', '\0' };
char guesssix[6] = { '_', '_', '_', '_','_', '\0' };
char clueone[6] = { '_', '_', '_', '_','_', '\0' };
char cluetwo[6] = { '_', '_', '_', '_','_', '\0' };
char cluethree[6] = { '_', '_', '_', '_','_', '\0' };
char cluefour[6] = { '_', '_', '_', '_','_', '\0' };
char cluefive[6] = { '_', '_', '_', '_','_', '\0' };
char cluesix[6] = { '_', '_', '_', '_','_', '\0' };
char letters_left_to_guess[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
bool has_letter_been_guessed[26] = { false };

const char* const GREEN_FORMAT = ANSI_COLOR_GREEN "%c";
const char* const BLUE_FORMAT = ANSI_COLOR_BLUE "%c";
const char* const CYAN_FORMAT = ANSI_COLOR_CYAN "%c";
const char* const YELLOW_FORMAT = ANSI_COLOR_BRIGHT_YELLOW "%c";
const char* const RED_FORMAT = ANSI_COLOR_RED "%c";
const char* const MAGENTA_FORMAT = ANSI_COLOR_MAGENTA "%c";
const char* const RESET_FORMAT = ANSI_COLOR_RESET "%c";



/*!
	@brief gets a random 5 letter word from the text file
	@param number is the index to get the word
	@return the word at that index.
*/


STATIC char* get_word(int number) {
	

	return wordle_dictionary[number % wordle_dictionary_size];
}
/*!
	@brief Loads the wordlength5 from a file
	@param filename The name of the file to load
	@return 1 if the text file was loaded successfully, 0 otherwise
*/

STATIC int load_all_5letter_words(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) return 0;

	while (fgets(wordle_dictionary[wordle_dictionary_size], MAX_wordle_WORD_LENGTH, file)) {
		wordle_dictionary[wordle_dictionary_size][strcspn(wordle_dictionary[wordle_dictionary_size], "\n")] = 0;
		if (++wordle_dictionary_size >= MAX_wordle_DICTIONARY_SIZE) break;
	}

	fclose(file);
	return 1;
}



/*!
	@brief Initializes the Wordle game

*/
void wordle_initialize(void) {
	srand((unsigned int)time(NULL));
	if (!load_all_5letter_words("wordlength5.txt")) {
		fprintf(stderr, "Failed to load dictionary. Wordle game may not function properly.\n");
	}
}


/*!
	@brief converts input to lowercase
	@param the user input
	@return the user input in lower case
*/
STATIC char* toLowerCase(const char* guess) {

	const char* lowercaseguess = guess;
	const int length = strlen(lowercaseguess);
	
	char* lower = (char*)malloc(length + 1);
	lower[length] = 0;
	for (int i = 0; i < length; i++) {
		lower[i] = tolower(guess[i]);
	}

	return lower;

}
/*!
	@brief checks if user input contains only letters
	@param the user input
	@return true if it does contain onyl char false if not
*/
STATIC bool conatainsonlychar(const char* guess) {
	bool onlyalpha = false;

	const int length = 5;
	char alphabet[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	for (int i = 0; i < length; i++) {
		char letter = guess[i];
		for (int j = 0; j < 26; j++) {
			if (letter == alphabet[j]) {
				onlyalpha = true;
			}
		}
		if (!onlyalpha) {
			return onlyalpha;
		}
		onlyalpha = false;

	}

	return true;




}
/*!
	@brief Checks if the user input is a valid word from the dictionary
	@param newguess The user's guess
	@return true if the word is found in the dictionary, false otherwise
*/
STATIC bool validWord(const char* newguess) {
	for (int i = 0; i < wordle_dictionary_size; i++) {
		if (strcmp(wordle_dictionary[i], newguess) == 0) {
			return true;
		}
	}
	return false;
}


/*!
	@brief checks if user input is 5 letters long
	@param the user input
	@return true if it is correct length  false if not
*/
STATIC bool correctlength(const char* guess) {
	const int length = strlen(guess);
	if (length == word_length) {
		return true;
	}

	return false;
}

/*!
	@brief compares user guess to the answer
	@param the answer
	@param the users guess
	@return a string of the user guess G if letter is in correct location, Y if not in correct, _ if letter not present in answer
*/
STATIC char* processGuess(const char* theWord, const char* theGuess) {
	// the clue
	char* clue = (char*)malloc(6 * sizeof(char));

	if (clue == NULL) {
		perror("Unable to allocate memory for clue");
		exit(EXIT_FAILURE);
	}


	// Initialize the clue with '_'
	for (int i = 0; i < 5; i++) {
		clue[i] = '_';
	}
	// Add to the end to make a string
	clue[5] = '\0';


	// set of flags indicating if that letter in the answer in used as clue
	bool answerFlags[5] = {false, false,false,false,false };

	// first pass, look for matched
	for (int i = 0; i < 5; i++) {
		if (theGuess[i] == theWord[i]) {
			clue[i] = 'G';
			answerFlags[i] = true;

		}
	}

	// second pass, look for correct letter wrong place
	for (int i = 0; i < 5; i++) {
		if (clue[i] == '_') {
			for (int j = 0; j < 5; j++) {
				if (theGuess[i] == theWord[j] && !answerFlags[j]) {
					// a match at another position and has not been used a clue
					clue[i] = 'Y';
					answerFlags[j] = true;
					break; // makes it so only one clue for one letter



				}
			}
		}

	}
	//printf("%s\n", clue);
	return clue;
		//strcmp(clue, "GGGGG") == 0;

}
/*!
	@brief updates the letters the user has guessed to be prepared to display the letters not guessed
	@param the users guess
*/
STATIC void updateLettersGuessed(const char* theGuess) {
	for (int i = 0; i < strlen(theGuess); i++) {
		char letter = theGuess[i];
		for (int j = 0; j<26; j++){
			if (letter == letters_left_to_guess[j]) {
				has_letter_been_guessed[j] = true;
			}
		}
	}
}
/*!
	@brief  gets all the letters the user has not guessed 
	@return a the letters that havw not been guessed
*/

STATIC char* lettersNotGuessed() {
	char* result = (char*)malloc(27 * sizeof(char)); // 26 letters + null terminator
	int index = 0;

	for (int i = 0; i < 26; i++) {
		if (!has_letter_been_guessed[i]) {
			result[index++] = 'a' + i;
		}
	}
	result[index] = '\0'; // Null-terminate the string

	return result;
}
/*!
	@brief a method for storing previous guesses and clues to be diplayed later
	@param the turn number
	@param the clue from the current turn
	@param the users guess from the current turn
*/

STATIC void updateclue(int turn, char* clue, const char* newguess) {
	switch (turn)
	{
	case 1:
		for (int i = 0; i < 6; i++) {
			guessone[i] = newguess[i];
			clueone[i] = clue[i];
		}
		break;
	case 2:
		for (int i = 0; i < 6; i++) {
			guesstwo[i] = newguess[i];
			cluetwo[i] = clue[i];
		}
		break;
	case 3:
		for (int i = 0; i < 6; i++) {
			guessthree[i] = newguess[i];
			cluethree[i] = clue[i];
		}
		break;
	case 4:
		for (int i = 0; i < 6; i++) {
			guessfour[i] = newguess[i];
			cluefour[i] = clue[i];
		}
		break;
	case 5:
		for (int i = 0; i < 6; i++) {
			guessfive[i] = newguess[i];
			cluefive[i] = clue[i];
		}
		break;
	case 6:
		for (int i = 0; i < 6; i++) {
			guesssix[i] = newguess[i];
			cluesix[i] = clue[i];
		}
		break;

	}

}
/*!
	@brief prints the game 
	@param an clue to be used to choose colour of letter
	@param the users guess
	@param colourblind changes the colour of the prints if user is colourblind
*/

void print_colored_output(char clue[], char guess[], bool colourblind) {
	if (!colourblind) {
		for (int i = 0; i < 6; i++) {
			if (clue[i] == 'G') {

				std::cout << ANSI_COLOR_GREEN << guess[i] << ANSI_COLOR_RESET;
			}
			else if (clue[i] == 'Y') {
				std::cout << ANSI_COLOR_BRIGHT_YELLOW << guess[i] << ANSI_COLOR_RESET;
			}
			else if (guess[i] == '_') {
				std::cout << guess[i];
			}
			else {
				std::cout << ANSI_COLOR_RED << guess[i] << ANSI_COLOR_RESET;
			}
		}
		std::cout << std::endl;
	}else {
		for (int i = 0; i < 6; i++) {
			if (clue[i] == 'G') {

				std::cout << ANSI_COLOR_CYAN << guess[i] << ANSI_COLOR_RESET;
			}
			else if (clue[i] == 'Y') {
				std::cout << ANSI_COLOR_BRIGHT_YELLOW << guess[i] << ANSI_COLOR_RESET;
			}
			else if (guess[i] == '_') {
				std::cout << guess[i];
			}
			else {
				std::cout << ANSI_COLOR_MAGENTA << guess[i] << ANSI_COLOR_RESET;
			}
		}
		std::cout << std::endl;
	}
}


/*!
	@brief resets the games
*/


STATIC void gamereset() {
	for (int i = 0; i < 6; i++) {
		guessone[i] = '_'; clueone[i] = '_';
		guesstwo[i] = '_'; cluetwo[i] = '_';
		guessthree[i] = '_'; cluethree[i] = '_';
		guessfour[i] = '_'; cluefour[i] = '_';
		guessfive[i] = '_'; cluefive[i] = '_';
		guesssix[i] = '_'; cluesix[i] = '_';
	}

	// Null-terminate the strings
	guessone[5] = '\0'; clueone[5] = '\0';
	guesstwo[5] = '\0'; cluetwo[5] = '\0';
	guessthree[5] = '\0'; cluethree[5] = '\0';
	guessfour[5] = '\0'; cluefour[5] = '\0';
	guessfive[5] = '\0'; cluefive[5] = '\0';
	guesssix[5] = '\0'; cluesix[5] = '\0';


	memset(has_letter_been_guessed, false, sizeof(has_letter_been_guessed));


	for (int i = 0; i < 26; i++) {
		letters_left_to_guess[i] = 'a' + i;
	}



}

/*!
	@brief ask the user if they are colour blind or not
	@return true if user is  colour blind and false if they are not.
*/


STATIC bool getcolourblindess() {
	char choice;
	while (true) {

		scanf("%c", &choice);

		if (choice == 'y') {
			printf("Note: Cyan = correct letter correct location, Yellow = correct letter, wrong location, Magenta = Wrong letter\n\n");
			return true;
		}
		else if (choice == 'n') {
			return false;
		}
		else {
			printf("\nAre you colour blind? y/n\n");
		}

	}
}






/*!
	@brief plays wordle game
*/

void playWordle(void) {
	printf("\n\nWORDLE\n\n");
	
	gamereset();

	int number = rand();
	const char* newanswer = get_word(number);

	// clears input buffer


	// do the game loop
	int num_of_guesses = 0;
	bool correct_guess = false;
	char guess[6];
	bool iscolourblind = false;
	
	iscolourblind = getcolourblindess();




	print_colored_output(clueone, guessone, iscolourblind);
	print_colored_output(cluetwo, guesstwo, iscolourblind);
	print_colored_output(cluethree, guessthree, iscolourblind);
	print_colored_output(cluefour, guessfour, iscolourblind);
	print_colored_output(cluefive, guessfive, iscolourblind);
	print_colored_output(cluesix, guesssix, iscolourblind);



	while (num_of_guesses < 6 && !correct_guess) {
		//get guess from user

		char* lettersleft = lettersNotGuessed();
		printf("\nLetter not guessed yet: %s", lettersleft);
		printf("\n\nInput a 5-letter word and press enter \n");


		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		fgets(guess, sizeof(guess), stdin); // Use fgets for safer input
		guess[strcspn(guess, "\n")] = 0; // Remove newline

		
	

		char* newguess = toLowerCase(guess);


		
		if (!conatainsonlychar(newguess)) {
			printf("Guess contains a non letter, Try Again.");
			continue;
		}
		if (!correctlength(newguess)) {
			printf("Word inputted was not the correct length. Try Again");
			continue;
		}




		if (!validWord(newguess)) {
			printf("Your guess was not a valid word. Try Again");
			continue;
		}

		updateLettersGuessed(newguess);





		num_of_guesses += 1;


		//proocess guess 
		char* clue = processGuess(newanswer, newguess);


		updateclue(num_of_guesses, clue, newguess);

		print_colored_output(clueone, guessone, iscolourblind);
		print_colored_output(cluetwo, guesstwo, iscolourblind);
		print_colored_output(cluethree, guessthree, iscolourblind);
		print_colored_output(cluefour, guessfour, iscolourblind);
		print_colored_output(cluefive, guessfive, iscolourblind);
		print_colored_output(cluesix, guesssix, iscolourblind);



		correct_guess = strcmp(clue, "GGGGG") == 0;
		printf("\n");

	}

	//display end of game message
	if (correct_guess) {
		printf("\nCongratulations! You guessed the correct word in %d tries!\n", num_of_guesses);
	}
	else {
		printf("\nNo more guesses... The correct word was %s\n", newanswer);
	}

	char choice;
	while (true) {
		scanf("%c", &choice);
		if (choice == 'y') {
			printf("\033[H\033[J");
			playWordle();
		}
		else if (choice == 'n') {
			return;
		}
		else {
			printf("\nWould you like to play again?  \nPlease enter 'y' to play again or 'n' to exit to the game menu:\n");
		}

	}
}



	

// Expose these functions for unit testing
#ifdef UNIT_TESTING

void set_wordle_mock_dictionary(const char mock_dict[][MAX_wordle_WORD_LENGTH], int size) {
	for (int i = 0; i < size && i < MAX_wordle_DICTIONARY_SIZE; i++) {
		strncpy(wordle_dictionary[i], mock_dict[i], MAX_wordle_WORD_LENGTH - 1);
		wordle_dictionary[i][MAX_wordle_WORD_LENGTH - 1] = '\0';
	}
	wordle_dictionary_size = size;
}
#endif



