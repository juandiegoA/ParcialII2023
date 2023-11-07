#include <iostream>
#include "othello.h"

// Constructor
Othello::Othello() {
    initializeBoard();
}

// Inicializar el juego
void Othello::play() {
    promptForNames();

    while (!isGameOver()) {
        printBoard();
        std::cout << currentPlayer->name << " Turno (" << currentPlayer->symbol << "):" << std::endl;

        int row, col;
        getMove(row, col);

        if (makeMove(row, col)) {
            switchPlayers();
        } else {
            std::cout << "Movimiento invalido. Prueba de nuevo." << std::endl;
        }
    }

    calculateScore();
    displayResult();
}

// Inicializar el tablero
void Othello::initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '-';
        }
    }

    // Piezas iniciales
    board[3][3] = 'O';
    board[3][4] = 'X';
    board[4][3] = 'X';
    board[4][4] = 'O';
}

// Print del tablero
void Othello::printBoard() {
    std::cout << "  ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i << " ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Ingresar nombre de jugadores
void Othello::promptForNames() {
    std::cout << "Ingrese jugador 1: ";
    std::cin >> player1.name;
    player1.symbol = 'X';

    std::cout << "Ingrese jugador 2: ";
    std::cin >> player2.name;
    player2.symbol = 'O';

    currentPlayer = &player1;
    otherPlayer = &player2;
}

// Cambiar jugadores
void Othello::switchPlayers() {
    Player* temp = currentPlayer;
    currentPlayer = otherPlayer;
    otherPlayer = temp;
}

// Ingresar movimiento
void Othello::getMove(int& row, int& col) {
    std::cout << "Ingrese fila y columna (Separado por un espacio): ";
    std::cin >> row >> col;
}

// Print el movimiento tomado
bool Othello::makeMove(int row, int col) {
    if (!isValidMove(row, col)) {
        return false;
    }

    // actualizar el tablero
    board[row][col] = currentPlayer->symbol;

    // Revisar y voltear las piezas del rival, si se puede (up, down, left, right)
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }

            // Desplazarse en la dirección actual y dar la vuelta a las piezas
            int r = row + i;
            int c = col + j;
            while (r >= 0 && r < 8 && c >= 0 && c < 8 && board[r][c] == otherPlayer->symbol) {
                r += i;
                c += j;
            }

            // Si se llega al final de la dirección y es la pieza del oponente, voltea las piezas
            if (r >= 0 && r < 8 && c >= 0 && c < 8 && board[r][c] == currentPlayer->symbol) {
                while (r != row || c != col) {
                    r -= i;
                    c -= j;
                    board[r][c] = currentPlayer->symbol;
                }
            }
        }
    }

    return true;
}

// Revisar si un movimiento es valido
bool Othello::isValidMove(int row, int col) {
    // Revisar que este dentro del tablero
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
        return false;
    }

    // Revisar si la celda esta vacia
    if (board[row][col] != EMPTY) {
        return false;
    }

    // Revisar si es valido en las direciones
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            // Saltarse la celda actual
            if (dr == 0 && dc == 0) {
                continue;
            }

            // Revizar si hay una pieza del oponente en las celdas adyacentes
            int r = row + dr;
            int c = col + dc;
            if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == PLAYER_2) {
                // Mueve en la dirección hasta alcanzar una casilla con la ficha del jugador actual
                while (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == PLAYER_2) {
                    r += dr;
                    c += dc;
                }

                // Si el while finaliza con un valid move, return true
                if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && board[r][c] == PLAYER_1) {
                    return true;
                }
            }
        }
    }

    // Si no encuentra una direccion, retorne falso
    return false;
}

bool Othello::isGameOver() {
    // Revisar si el tablero esta lleno
    bool isFull = true;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == '-') {
                isFull = false;
                break;
            }
        }
        if (!isFull) {
            break;
        }
    }
    if (isFull) {
        return true;
    }

    // Check if there are any empty spaces
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
}

// Calcular el puntaje final
void Othello::calculateScore() {
    //--------------------------
    player1.score = 0;
    player2.score = 0;
}

// Mostar el ganador y el puntaje final
void Othello::displayResult() {
    std::cout << "Game Over!" << std::endl;
    std::cout << "Puntaje final:" << std::endl;
    std::cout << player1.name << ": " << player1.score << std::endl;
    std::cout << player2.name << ": " << player2.score << std::endl;

    if (player1.score > player2.score) {
        std::cout << player1.name << " Gano!" << std::endl;
    } else if (player2.score > player1.score) {
        std::cout << player2.name << " Gano!" << std::endl;
    } else {
        std::cout << "Es un empate!" << std::endl;
    }
}
