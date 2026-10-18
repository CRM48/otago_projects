# Vintage Vault

[![VintageVault CI](https://github.com/CRM48/otago_projects/actions/workflows/vintage-vault.yml/badge.svg)](https://github.com/CRM48/otago_projects/actions/workflows/vintage-vault.yml)

[![VintageVault Coverage](https://codecov.io/github/CRM48/otago_projects/graph/badge.svg?flag=vintage-vault)](https://codecov.io/github/CRM48/otago_projects)

[![Docs](https://img.shields.io/badge/Docs-Doxygen-brightgreen)](https://crm48.github.io/otago_projects/vintage_vault/)

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/fae259780451490ba321bb03a6961c25)](https://app.codacy.com/gh/CRM48/otago_projects/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)

VintageVault is a C++ command-line game hub containing four classic games: Tic-Tac-Toe, Hangman, Wordle, and Secret Number. Players can select and play games through a central menu, with background music playing throughout the application.

The project was developed as a team assignment for COSC345 at the University of Otago. It demonstrates modular C++ programming, game logic, automated testing, and software development tools including CMake, GitHub Actions, Codecov, Doxygen, and Codacy.

## Requirements

- Windows
- C++ compiler (MSVC / Visual Studio 2022)
- CMake

## Build and Run

1. Open a terminal in the `vintage_vault` directory.
2. Configure and build the application:

   ```bash
   cmake -S . -B build
   cmake --build build --config Debug
   ```

3. Navigate to the executable directory and launch VintageVault:

   ```bash
   cd build/bin/Debug
   ./VintageVault.exe
   ```

The main menu allows players to select one of the four games or exit the application.

## Games

### Tic-Tac-Toe
A two-player game played on a 3×3 grid. Players take turns placing their marks, aiming to get three in a row horizontally, vertically, or diagonally.

### Hangman
A word-guessing game where players select a word length and guess individual letters to reveal a hidden word. Incorrect guesses reduce the number of remaining attempts.

### Wordle
A five-letter word-guessing game where players have six attempts to identify the hidden word. Each guess provides coloured feedback:

- **Green:** Correct letter in the correct position.
- **Yellow:** Correct letter in the wrong position.
- **Red:** Letter not in the word.

### Secret Number
A number-guessing game where players attempt to identify a randomly generated number. Feedback after each guess helps narrow down the correct answer.

## Testing

VintageVault includes automated unit tests for the four games, covering game logic, word selection, input handling and other core functionality.

To run the tests after building:

```bash
ctest --test-dir build -C Debug --output-on-failure
```

GitHub Actions automatically builds and tests the application on Windows, with an additional Ubuntu job generating code coverage reports using `gcovr`.

Code coverage is published through Codecov, code quality is assessed using Codacy, and source-code documentation is generated using Doxygen and hosted on GitHub Pages.

## Project Structure

- `main.cpp` and `home.cpp` – Application entry point and main menu.
- `TicTacToe.cpp`, `hangman.cpp`, `newwordle.cpp`, `secretNumber.cpp` – Game implementations.
- `startmusic.cpp` – Background music playback.
- `tests/` – Automated tests for the games.
- `dictionary.txt` and `wordlength5.txt` – Word lists used by Hangman and Wordle.
- `music.wav` – Background music.
- `CMakeLists.txt` – Build configuration.
- `Doxyfile` – Doxygen documentation configuration.
