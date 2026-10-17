// hangman.c
/*!
    @file hangman.cpp
	@brief Hangman game implementation
    @author Nick Garner
*/

#include "hangman.h"

// Global variables
#ifdef UNIT_TESTING
char dictionary[MAX_DICTIONARY_SIZE][MAX_WORD_LENGTH];
int dictionarySize = 0;
#else
static char dictionary[MAX_DICTIONARY_SIZE][MAX_WORD_LENGTH];
static int dictionarySize = 0;
#endif

// Remove static keyword for functions to be tested
#ifdef UNIT_TESTING
#define STATIC
#else
#define STATIC static
#endif

/*!
    @brief checks if letter is in word
    @param letter The letter to check
    @param word The word to check
    @return true if the letter is in the word, false otherwise
*/
bool isLetterInWord(char letter, const char* word) {
    while (*word) {
        if (*word == letter) {
            return true;
        }
        word++;
    }
    return false;
}

/*!
    @brief Selects a word from the dictionary based on the desired length
	@param desired_length The desired length of the word
	@return A pointer to the selected word
*/
STATIC char* selectWord(int desiredLength) {
    if (desiredLength < 0) {
        printf("Invalid length. Selecting a random word.\n");
        return dictionary[rand() % dictionarySize];
    }

    if (desiredLength == 0) {
        return dictionary[rand() % dictionarySize];
    }

    int suitableWords[MAX_DICTIONARY_SIZE];
    int suitableCount = 0;

    for (int i = 0; i < dictionarySize; i++) {
        size_t wordLength = strlen(dictionary[i]);
        if (wordLength == (size_t)desiredLength) {
            suitableWords[suitableCount++] = i;
        }
    }

    if (suitableCount == 0) {
        printf("No words found with length %d. Selecting a random word.\n", desiredLength);
        return dictionary[rand() % dictionarySize];
    }

    return dictionary[suitableWords[rand() % suitableCount]];
}

/*!
    @brief Prints the hangman based on the number of tries
	@param tries The number of tries
*/
void printHangman(int tries) {
    const char* hangmanStates[] = {
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="
    };

    printf("%s\n", hangmanStates[tries]);
}

/*!
    @brief Prints the word with guessed letters
	@param word The word to print
	@param guessed An array of guessed letters

*/
STATIC void printWord(const char* word, const int* guessed) {
    for (int i = 0; word[i]; i++) {
        printf("%c ", guessed[i] ? word[i] : '_');
    }
    printf("\n");
}

/*!
    @brief Checks if a word has been guessed
	@param guessed An array of integers representing the guessed letters
	@param length The length of the word
	@return 1 if the word has been guessed, 0 otherwise
*/
STATIC int isWordGuessed(const int* guessed, int length) {
    for (int i = 0; i < length; i++) {
        if (!guessed[i]) return 0;
    }
    return 1;
}

/*!
    @brief Converts a string to uppercase
	@param str The string to convert to uppercase
*/
STATIC void toUppercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

/*!
    @brief Loads the dictionary from a file
    @param filename The name of the file to load
    @return 1 if the dictionary was loaded successfully, 0 otherwise
*/
STATIC int loadDictionary(const char* filename, char dictionary[][MAX_WORD_LENGTH], int maxSize) {
    FILE* file = fopen(filename, "r");
    if (!file) return -1;  // Return -1 on file open error

    int wordsLoaded = 0;
    while (wordsLoaded < maxSize &&
        fgets(dictionary[wordsLoaded], MAX_WORD_LENGTH, file)) {
        dictionary[wordsLoaded][strcspn(dictionary[wordsLoaded], "\n")] = 0;
        toUppercase(dictionary[wordsLoaded]);
        wordsLoaded++;
    }
    fclose(file);
    return wordsLoaded;
}

/*!
	@brief Initializes the hangman game

*/
void hangmanInitialize(void) {
    srand((unsigned int)time(NULL));
    dictionarySize = loadDictionary("dictionary.txt", dictionary, MAX_DICTIONARY_SIZE);
    if (dictionarySize <= 0) {
        fprintf(stderr, "Failed to load dictionary. Hangman game may not function properly.\n");
    }
}

/*!
    @brief Plays the hangman game
*/
STATIC void hangmanPlay(void) {
    int playAgain = 1;

    do {
        int desiredLength;
        printf("Enter desired word length (0 for random): ");
        if (scanf("%d", &desiredLength) != 1) {
            printf("Invalid input. Exiting game.\n");
            return;
        }

        const char* word = selectWord(desiredLength);
        int wordLength = strlen(word);

        int guessed[MAX_WORD_LENGTH] = { 0 };
        int tries = 0;
        char guess;
        char input[100];
        char guessedLetters[26] = { 0 };
        int guessedCount = 0;
        char wrongGuesses[MAX_TRIES] = { 0 };
        int wrongCount = 0;

        printf("Welcome to Hangman!\n");

        while (tries < MAX_TRIES) {
            printf("\nWord: ");
            printWord(word, guessed);
            printf("Tries left: %d\n", MAX_TRIES - tries);
            printHangman(tries);

            if (wrongCount > 0) {
                printf("Wrong guesses: ");
                for (int i = 0; i < wrongCount; i++) {
                    printf("%c ", wrongGuesses[i]);
                }
                printf("\n");
            }

            printf("Guess a letter: ");
            if (scanf(" %99s", input) != 1) {
                printf("Invalid input. Exiting game.\n");
                return;
            }

            if (strlen(input) != 1) {
                printf("Please enter only one letter.\n");
                continue;
            }

            guess = toupper(input[0]);

            if (!isalpha(guess)) {
                printf("Please enter a valid letter.\n");
                continue;
            }

            if (strchr(guessedLetters, guess)) {
                printf("You've already guessed that letter. Try again.\n");
                continue;
            }

            guessedLetters[guessedCount++] = guess;
            int correctGuess = 0;

            for (int i = 0; i < wordLength; i++) {
                if (word[i] == guess) {
                    guessed[i] = 1;
                    correctGuess = 1;
                }
            }

            if (!correctGuess) {
                wrongGuesses[wrongCount++] = guess;
                tries++;
                printf("Wrong guess!\n");
            }

            if (isWordGuessed(guessed, wordLength)) {
                printf("\nCongratulations! You've guessed the word: %s\n", word);
                break;
            }
        }

        if (tries == MAX_TRIES) {
            printf("\nGame over! The word was: %s\n", word);
        }

        printHangman(tries);

        // Prompt for playing again
        char choice;
        int valid_input;
        do {

            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}

            printf("\nWould you like to play again?  \nPlease enter 'y' to play again or 'n' to exit to the game menu: ");
            valid_input = 0;
            char line[256];
            if (fgets(line, sizeof(line), stdin)) {
                // Remove newline character if present
                line[strcspn(line, "\n")] = 0;

                if (strlen(line) == 1) {
                    choice = tolower(line[0]);
                    if (choice == 'y' || choice == 'n') {
                        valid_input = 1;
                    }
                    else {
                        printf("Invalid choice. Please enter only y or n.\n");
                    }
                }
                else {
                    printf("Invalid input. Please enter only a single character y or n.\n");
                }
            }
            else {
                printf("Error reading input. Exiting game.\n");
                return;
            }
        } while (!valid_input);

        playAgain = (choice == 'y');
        printf("\033[H\033[J");
    } while (playAgain);
    printf("Thanks for playing Hangman!\n");
}
// Expose these functions for unit testing
#ifdef UNIT_TESTING
void setMockDictionary(const char mockDict[][MAX_WORD_LENGTH], int size) {
    for (int i = 0; i < size && i < MAX_DICTIONARY_SIZE; i++) {
        strcpy(dictionary[i], mockDict[i]);
    }
    dictionarySize = size;
}
#endif