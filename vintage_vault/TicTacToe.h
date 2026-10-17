/*!
    @file TicTacToe.h
    @brief Header file for TicTacToe class
    @author Curtis Mellsop
 */
#include <iostream>
using namespace std;


const int ROWS = 3;
const int COLS = 3;
extern char board[ROWS][COLS];

/*!
    @brief Initialises the board variable
*/
void initBoard();

/*!
    @brief Displays the TicTacToe board in the terminal
*/
void displayBoard();

/*!
    @brief Check for win state
    @return True if board is in winning state, false otherwise
*/
bool checkWin();

/*!
    @brief Checks for a draw
    @return True if no possible moves, and not a win state, false otherwise
*/
bool checkDraw();

/*!
    @brief Initiates for a players move
    @param player which players turn it is (X or O)
*/
void move(char player, string input);

/*!
    @brief Plays one instance of TicTacToe
*/
void playTicTacToe();

/*!
    @brief Runs the game
*/
void runGame();