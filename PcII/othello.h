#ifndef OTHELLO_H
#define OTHELLO_H

#include <iostream>

// Constants
const int BOARD_SIZE = 8;
// Constants for the different states of the cells
const char EMPTY = '-';
const char PLAYER_1 = 'O';
const char PLAYER_2 = 'X';

// Player structure
struct Player {
    std::string name;
    char symbol;
    int score;
};

// Game class
class Othello {
public:
    // Constructor
    Othello();

    // Start the game
    void play();

private:
    // Board state
    char board[BOARD_SIZE][BOARD_SIZE];

    // Players
    Player player1;
    Player player2;
    Player* currentPlayer;
    Player* otherPlayer;

    char opponentPiece;
    char playerPiece;

    // Initialize the board
    void initializeBoard();

    // Print the board
    void printBoard();

    // Prompt for player names
    void promptForNames();

    // Switch players
    void switchPlayers();

    // Get a valid move from the current player
    void getMove(int& row, int& col);

    // Make a move on the board
    bool makeMove(int row, int col);

    // Check if a move is valid
    bool isValidMove(int row, int col);
    //bool isValidMove(char board[][8], int row, int col, char player);

    // Check if still valid moves

    bool hasValidMove(char player);

    // Check if the board is full
    bool isBoardFull();

    // Check if the game is over
    bool isGameOver();

    // Calculate the final score
    void calculateScore();

    // Display the winner and final score
    void displayResult();

    char getColor();

    char getOpponentColor();
};

#endif
