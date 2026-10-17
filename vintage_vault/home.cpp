// home.c
/*!
    @file home.cpp
	@brief Main file for the Game Hub
*/
#include <stdio.h>
#include "secretNumber.h"
#include "hangman.h"
#include "newwordle.h"
#include "TicTacToe.h"
#include "startmusic.h"
#include <filesystem>
#include <iostream>
#include <chrono> // Add this line
#include <thread> // Add this line


namespace fs = std::filesystem;
// Include headers for other games as you add them

/*!
    @brief Function to initialize all games
*/
void initialize_games(void) {

    const char* audioFile = "music.wav";
    fs::path audioPath = fs::current_path() / audioFile;

    if (fs::exists(audioPath)) {
        startBackgroundMusic(audioFile);
    }
    else {
        std::cerr << "Audio file not found: " << audioPath << std::endl;
    }

    hangmanInitialize();
    wordle_initialize();

    // Initialize other games as you add them
}

/*!
	@brief Function to display the homescreen and allow the user to choose a game to play
*/
int homescreen(void) {
    int choice;


    initialize_games();

    printf(" __      ____      __  \n");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    printf(" \\ \\    / /\\ \\    / //\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    printf("  \\ \\  / // \\ \\  / //  \n");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    printf("   \\ \\/ //   \\ \\/ //  \n");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    printf("    \\  //     \\  //  \n");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    printf("     \\//intage \\//ault    \n\n\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    printf("Brought to you by C++L Points\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));



    while (1) {
        


     
    
        printf("\nWelcome to the Game Hub!\n\n");
        printf("1. HANGMAN\n\n");
        printf("    +---+\n    |   |\n    O   |\n   /|\\  |\n   / \\  |\n        |\n  =========\n\n");

        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        printf("2. WORDLE\n\n");
        printf("   S _ _ _ _\n");
        printf("   S _ E A _\n");
        printf("   S T E A _\n");
        printf("   S T E A M\n\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        printf("3. SECRET NUMBER\n\n");
        printf("   _____\n");
        printf("  / ___ \\\n");
        printf("  |    ||\n");
        printf("  | ___||\n");
        printf("  |    ||\n");
        printf("  | ___||\n");
        printf("  \\_____/\n\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        printf("4. TICTACTOE\n\n");
        printf("   X | O | O\n");
        printf("   ---------\n");
        printf("   O | X | O\n");
        printf("   ---------\n");
        printf("   X | O | X\n\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        printf("0. Exit\n\n");
        printf("Please select an option by inputting the number and pressing enter: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            hangmanPlay();
            break;
        case 2:
            playWordle();
            break;
        case 3:
            secretNumberStart();
            break;
        case 4:
            runGame();
            break;
        case 0:
            printf("Thank you for playing. Goodbye!\n");
            stopBackgroundMusic();
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
        printf("\033[H\033[J");
    }

    return 0;
}

// to test:
// gcc home.cpp hangman.cpp secretNumber.cpp -o gamehub