#include "../hangman.h"
#include "../newwordle.h"
#include "test_tictactoe.h"
#include "../secretNumber.h"

int main() {
	runwordletests();
	runttttests();
	hangmanTests();
	secNumTests();

	return 0;
}