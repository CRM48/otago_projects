/*!
    @file TicTacToe.cpp
	@brief TicTacToe Implementation
    @author Curtis Mellsop
*/

#include "TicTacToe.h"

// declare board variable
char board[ROWS][COLS];

/*!
    @brief Initialises the board variable
*/
void initBoard(){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            // Set each value to a blank character (for output purposes)
            board[i][j] = ' ';
        }
    }
}

/*!
    @brief Displays the TicTacToe board in the terminal
*/
void displayBoard(){
    cout << "\n" << endl;
    // Differentiate columns using numbers
    cout << "\t  1   2   3" << endl;
    for (int i = 0; i < ROWS; i++) {
        // Differentiate rows using letters
        cout << "\t" << char('A' + i) << " ";
        for (int j = 0; j < COLS; j++) {
            cout << board[i][j];
            if (j < COLS - 1) cout << " | ";
        }
        cout << endl;
        if (i < ROWS - 1) cout << "\t  ---------" << endl;
    }
    cout << "\n" << endl;
}

/*!
    @brief Check for win state
    @return True if board is in winning state, false otherwise
*/
bool checkWin(){
    // Check rows
    for(int i = 0; i < ROWS; i++){
        if((board[i][0] == board[i][1] && board[i][1] == board[i][2]) && board[i][0] != ' '){
            return true;
        }
    }

    // Check columns
    for(int i = 0; i < COLS; i++){
        if((board[0][i] == board[1][i] && board[1][i] == board[2][i]) && board[0][i] != ' '){
            return true;
        }
    }

    // Check diagonals
    if(board[1][1] != ' ' && ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[0][2] == board[1][1] && board[1][1] == board[2][0]))){
        return true;
    }
    return false;
}

/*!
    @brief Checks for a draw
    @return True if no possible moves, and not a win state, false otherwise
*/
bool checkDraw(){
    for(int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            if (board[i][j] == ' '){
                // If any blank values in board, then the game can continue
                return false;
            }
        }
    }
    return true;
}

/*!
    @brief Initiates for a players move
    @param player which players turn it is (X or O)
*/
void move(char player, string input){
    // Declare local variables
    bool testing = ((input != "") ? true : false);
    char charRow;
    int col;
    int row;
    while(true){
        // Ask the player to make a move and record their input
        if(input == ""){
            cout << "Player " << ((player == 'X') ? 1 : 2) << ", please enter your move (format example: A2): ";
            cin >> input;
        }
        
        charRow = toupper(input[0]);
        // Convert input into two int values from 0 to 2
        row = charRow - 'A';
        col = input[1] - '1';
        // Check the input is a possible coordinate
        if(row > (ROWS - 1) || row < 0 || col > (COLS - 1) || col < 0){
            cout << "Invalid row or column" << endl;
            if(testing) throw invalid_argument("Invalid row or column");
            input = "";
            continue;
        }
        // Check the coordinate isn't filled
        if(board[row][col] != ' '){
            cout << "Position already has a value" << endl;
            if(testing) throw invalid_argument("Position already has a value");
            input = "";
            continue;
        }
        // Set the boards value to that player
        board[row][col] = player;
        break;
    }    
}

/*!
    @brief Plays one instance of TicTacToe
*/
void playTicTacToe(){
    // Sets player 1 to X
    char currentPlayer = 'X';
    // Creates an empty 2d array 'board'
    initBoard();

    cout << "Welcome to Tic-Tac-Toe" << endl;
    cout << "To play, enter the coordinates of where you want to put your piece:" << endl;

    while (true) {
        // Displays the current board and asks the player to make a move
        displayBoard();
        move(currentPlayer, "");

        // Checks for a win, and if so, output winner and end game
        if (checkWin()) {
            displayBoard();
            cout << "Player " << ((currentPlayer == 'X') ? 1 : 2) << " wins!" << endl;
            break;
        } 
        // If no win check for draw, if so, print it's a draw and end the game
        else if (checkDraw()) {
            displayBoard();
            cout << "It's a draw!" << endl;
            break;
        }

        // Switch players
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

}

/*!
    @brief Runs the game
*/
void runGame(){
    char playAgain = 'n';
    while(true){
        playTicTacToe();
        cout << "\nWould you like to play again?  \nPlease enter 'y' to play again or 'n' to exit to the game menu:" << endl;
        while(true){
            cin >> playAgain;
            if(playAgain != 'y' && playAgain != 'n'){
                cout << "Please enter a valid input (y/n):" << endl;
            }
            else break;
        }

        if(playAgain == 'n') break;
        printf("\033[H\033[J");
        cout << "___________________________________________________________________\n" << endl;
    }
}