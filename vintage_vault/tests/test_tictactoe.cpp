/*!
    @file test_tictactoe.cpp
	@brief TicTacToe Testing
    @author Curtis Mellsop
*/

#include "test_tictactoe.h"
#include <iostream>
#include <sstream>

/*!
    @brief Called method to run test functions
*/
int runttttests(){
    test_initBoard();
    test_checkWin();
    test_checkDraw();
    test_move();
    test_playTicTacToe();
    return 0;
}

/*!
    @brief Tests the function that initialises the board
*/
void test_initBoard(){
    bool pass = true;
    initBoard();
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            if(board[i][j] != ' '){
                pass = false;
            }
        }
    }
    std::cout << "Initiate board function: " << (pass ? "PASSED" : "FAILED") << std::endl;
}

/*!
    @brief Tests the function that checks for a win state
*/
void test_checkWin(){
    // Check winning row
    initBoard();
    board[0][0] = 'X';
    board[0][1] = 'X';
    board[0][2] = 'X';
    std::cout << "Check Win function, row test: " << (checkWin() ? "PASSED" : "FAILED") << std::endl;

    // Check winning column
    initBoard();
    board[0][0] = 'O';
    board[1][0] = 'O';
    board[2][0] = 'O';
    std::cout << "Check Win function, column test: " << (checkWin() ? "PASSED" : "FAILED") << std::endl;

    // Check winning diagonal
    initBoard();
    board[0][0] = 'X';
    board[1][1] = 'X';
    board[2][2] = 'X';
    std::cout << "Check Win function, diagonal test: " << (checkWin() ? "PASSED" : "FAILED") << std::endl;

    // Check non-winning state
    initBoard();
    board[0][0] = 'X';
    board[0][1] = '0';
    board[0][2] = 'X';
    std::cout << "Check Win function, non-winning state: " << (!checkWin() ? "PASSED" : "FAILED") << std::endl;


}

/*!
    @brief Tests the function that checks for a draw state
*/
void test_checkDraw(){
    initBoard();
    char drawState[ROWS][COLS] = {
        {'X', 'O', 'X'},
        {'O', 'X', 'O'},
        {'O', 'X', 'O'}
    };
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            board[i][j] = drawState[i][j];
        }
    }
    std::cout << "Check Draw function: " << (checkDraw() ? "PASSED" : "FAILED") << std::endl;

}

/*!
    @brief Tests the function that allows a player to make a move
*/
void test_move(){
    // Valid move
    initBoard();
    move('X', "A1");
    std::cout << "Check valid move: " << (board[0][0] == 'X' ? "PASSED" : "FAILED") << std::endl;

    // Out of bounds move
    initBoard();
    bool expected_bounds_error = false;
    try{
        move('X', "D1");
    } catch (const std::invalid_argument& e){
        expected_bounds_error = true;
    }
    std::cout << "Check valid move: " << (expected_bounds_error ? "PASSED" : "FAILED") << std::endl;

    // Occupied position move
    initBoard();
    board[0][0] = 'X';
    bool expected_occupied_error = false;
    try{
        move('O', "A1");
    } catch (const std::invalid_argument& e){
        expected_occupied_error = true;
    }
    std::cout << "Check valid move: " << (expected_occupied_error ? "PASSED" : "FAILED") << std::endl;
}

/*!
    @brief Tests the main play function, for correct winning display
*/
void test_playTicTacToe(){
    // Player 1 wins case
    std::istringstream input("A1\nB1\nA2\nB2\nA3");
    std::streambuf* originalCinBuffer = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream output;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    playTicTacToe();

    std::string result = output.str();
    std::cin.rdbuf(originalCinBuffer);
    std::cout.rdbuf(originalCoutBuffer);

    std::cout << "Check P1 win: " << (result.find("Player 1 wins!") != std::string::npos ? "PASSED" : "FAILED") << std::endl;
}