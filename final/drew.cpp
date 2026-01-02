#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <unordered_map>
#include <queue>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include "drew.h"

using namespace std;

int getRandomNumber() {
    //Random number generator got from stack overflow because srand and rand() was not good enough
    random_device rd; // Optional for better seeding

    mt19937 gen(rd()); //Mersenne Twister engine

    uniform_int_distribution<> dist(1, 100); // range 1-100

    int random_number = dist(gen); //gets random number
    return random_number;
}

//This function sets the map the stores all the pieces in the game
void setMap(unordered_map<string, unordered_map<int, vector<vector<int>>>> &pieces){
    for (int i = 0; i < 4; i ++) {
        pieces["sPiece"][i] = vector<vector<int>>(4, vector<int>(4, 0));
        pieces["iPiece"][i] = vector<vector<int>>(4, vector<int>(4, 0));
        pieces["zPiece"][i] = vector<vector<int>>(4, vector<int>(4, 0));
        pieces["lPiece"][i] = vector<vector<int>>(4, vector<int>(4, 0));
        pieces["pPiece"][i] = vector<vector<int>>(4, vector<int>(4, 0));
        pieces["tPiece"][i] = vector<vector<int>>(4, vector<int>(4, 0));
        pieces["oPiece"][i] = vector<vector<int>>(4, vector<int>(4, 0));
    }

    pieces["sPiece"][0] = {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["sPiece"][1] = {
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };
    pieces["sPiece"][2] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["sPiece"][3] = {
        {1, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    };

    pieces["iPiece"][0] = {
        {2, 2, 2, 2},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["iPiece"][1] = {
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0},
        {0, 0, 2, 0}
    };
    pieces["iPiece"][2] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {2, 2, 2, 2},
        {0, 0, 0, 0}
    };
    pieces["iPiece"][3] = {
        {0, 2, 0, 0},
        {0, 2, 0, 0},
        {0, 2, 0, 0},
        {0, 2, 0, 0}
    };

    pieces["zPiece"][0] = {
        {3, 3, 0, 0},
        {0, 3, 3, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["zPiece"][1] = {
        {0, 0, 3, 0},
        {0, 3, 3, 0},
        {0, 3, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["zPiece"][2] = {
        {0, 0, 0, 0},
        {3, 3, 0, 0},
        {0, 3, 3, 0},
        {0, 0, 0, 0}
    };
    pieces["zPiece"][3] = {
        {0, 3, 0, 0},
        {3, 3, 0, 0},
        {3, 0, 0, 0},
        {0, 0, 0, 0}
    };

    pieces["lPiece"][0] = {
        {4, 4, 4, 0},
        {4, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["lPiece"][1] = {
        {4, 4, 0, 0},
        {0, 4, 0, 0},
        {0, 4, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["lPiece"][2] = {
        {0, 0, 0, 0},
        {0, 0, 4, 0},
        {4, 4, 4, 0},
        {0, 0, 0, 0}
    };
    pieces["lPiece"][3] = {
        {0, 4, 0, 0},
        {0, 4, 0, 0},
        {0, 4, 4, 0},
        {0, 0, 0, 0}
    };

    pieces["pPiece"][0] = {
        {5, 5, 5, 0},
        {0, 0, 5, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["pPiece"][1] = {
        {0, 5, 0, 0},
        {0, 5, 0, 0},
        {5, 5, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["pPiece"][2] = {
        {0, 0, 0, 0},
        {5, 0, 0, 0},
        {5, 5, 5, 0},
        {0, 0, 0, 0}
    };
    pieces["pPiece"][3] = {
        {0, 5, 5, 0},
        {0, 5, 0, 0},
        {0, 5, 0, 0},
        {0, 0, 0, 0}
    };

    pieces["tPiece"][0] = {
        {6, 6, 6, 0},
        {0, 6, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["tPiece"][1] = {
        {0, 6, 0, 0},
        {6, 6, 0, 0},
        {0, 6, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["tPiece"][2] = {
        {0, 0, 0, 0},
        {0, 6, 0, 0},
        {6, 6, 6, 0},
        {0, 0, 0, 0}
    };
    pieces["tPiece"][3] = {
        {0, 6, 0, 0},
        {0, 6, 6, 0},
        {0, 6, 0, 0},
        {0, 0, 0, 0}
    };

    pieces["oPiece"][0] = {
        {0, 7, 7, 0},
        {0, 7, 7, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["oPiece"][1] = {
        {0, 7, 7, 0},
        {0, 7, 7, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["oPiece"][2] = {
        {0, 7, 7, 0},
        {0, 7, 7, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["oPiece"][3] = {
        {0, 7, 7, 0},
        {0, 7, 7, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
}

//This function changes the terminal settings to not show the user input back to them and not require "ENTER" to be hit in order for the input to be read
//It was made with help from GeeksForGeeks, StackOverflow, and ChatGPT for debugging
void setNonCanonicalMode(bool enable) {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    if (enable) {
        term.c_lflag &= ~(ICANON | ECHO);  //Disable canonical mode and echo
    } else {
        term.c_lflag |= (ICANON | ECHO);   // Enable canonical mode and echo
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

//This function Doesnt stop the program from running while waiting for keyboard input. This is needed so that the program runs until an arrow key is hit
//It was made with help from GeeksForGeeks, StackOverflow, and ChatGPT for debugging
bool kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

//This function read in keybaord inputs like the arrow keys
//It was made with help from GeeksForGeeks, StackOverflow, and ChatGPT for debugging
string getch() {
    char ch[1];
    string result = "";

    if (kbhit()) {
        read(STDIN_FILENO, &ch, 1);
        if (ch[0] == '\033') {  // If it's an escape sequence (starts with \033)
            read(STDIN_FILENO, &ch, 1);  // Skip the '['
            read(STDIN_FILENO, &ch, 1);  // Read the actual arrow key
            switch (ch[0]) {
                case 'D': return "left";  // Left arrow
                case 'C': return "right"; // Right arrow
            }
        } else {
            result = string(1, ch[0]);  // Handle regular keys
        }
    }

    return result;
}

//This function handles the quickDrop placement. When "s" is hit it places the piece in its lowest possible spot.
int dropPiece(int& initialJ, int& rotation, vector<vector<int>>& board, unordered_map<string, unordered_map<int, vector<vector<int>>>>& pieces, string& piece, queue<string>& pQueue) {
    int dropDistance = 0;
    bool canDrop = true;

    const vector<string> pieceTypes = {"sPiece", "iPiece", "zPiece", "lPiece", "pPiece", "tPiece", "oPiece"};

    //Check how far the piece can drop
    while (canDrop) {
        dropDistance++;
        canDrop = true;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (pieces.at(piece).at(rotation)[i][j] != 0) {  // Use .at() because [] caused seg faults 
                    // Check bounds and existing pieces
                    if (i + dropDistance >= 20 || board[i + dropDistance][initialJ + j] != 0) {
                        canDrop = false;
                        break;
                    }
                }
            }
            if (!canDrop) break;
        }
    }

    // Place the piece at the lowest valid position
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (pieces.at(piece).at(rotation)[i][j] != 0) {
                board[i + dropDistance - 1][initialJ + j] = pieces.at(piece).at(rotation)[i][j];
            }
        }
    }

    
    return dropDistance;
}

//This function rotates the piece by iterating through the vector in the map
void rotatePiece(int& rotation, int direction, int initialJ, const unordered_map<string, unordered_map<int, vector<vector<int>>>>& pieces, const string& piece, const vector<vector<int>>& board) {
    int nextRotation = (rotation + direction) % 4;

    // Rotation check
    bool rotationFits = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            //checks to see if it will rotate into a nearby piece
            if (pieces.at(piece).at(nextRotation)[i][j] != 0) {
                if (initialJ + j < 2 || initialJ + j > 11 || board[i][initialJ + j] != 0) {
                    rotationFits = false;
                    break;
                }
            }
        }
        if (!rotationFits) break;
    }

    // Rotate if safe
    if (rotationFits) {
        rotation = nextRotation;
    }
}

//This functions checks for collisions with the board and other pieces
bool canMovePiece(int initialJ, int initialI, int rotation, const string& piece, const vector<vector<int>>& board, const unordered_map<string, unordered_map<int, vector<vector<int>>>>& pieces) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (pieces.at(piece).at(rotation)[i][j] != 0) {
                int boardRow = initialI + i;
                int boardCol = initialJ + j;

                if (boardCol < 2 || boardCol > 11 || boardRow >= board.size() || board[boardRow][boardCol] != 0){
                    return false;
                }
                
                /*if (initialJ + j < 2 || initialJ + j > 11 || board[initialI][initialJ + j] != 0){
                    return false; // Collision or out of bounds
                }*/
            }
        }
    }
    return true; // Movement is allowed
}

//This function checks if the current piece can move down any further (whether or not it is in contact with another piece or the bottom of the board)
bool canMoveDown(int initialJ, int rotation, const string& piece, vector<vector<int>>& board, const unordered_map<string, unordered_map<int, vector<vector<int>>>>& pieces) {
    vector<vector<int>> currentPiece = pieces.at(piece).at(rotation);

    for (int i = 0; i < currentPiece.size(); ++i) {
        for (int j = 0; j < currentPiece[i].size(); ++j) {
            if (currentPiece[i][j] != 0) {
                int newRow = i + initialI.load() + 1; //load is used to read the global atomic value initialI
                int newCol = j + initialJ;

                if (newRow >= board.size() || newRow >= 20 || board[newRow][newCol] != 0) {
                    return false; // cant move down
                }
            }
        }
    }
    return true;
}

//This function actually places the piece on the board
void placePiece(vector<vector<int>>& board, const vector<vector<int>>& currentPiece, int initialI, int initialJ) {
    for (int i = 0; i < currentPiece.size(); ++i) {
        for (int j = 0; j < currentPiece[i].size(); ++j) {
            if (currentPiece[i][j] != 0) {
                int row = i + initialI;
                int col = j + initialJ;
                
                if (row >= 0 && row < board.size() && col >= 0 && col < board[0].size()) {
                    board[row][col] = currentPiece[i][j];
                }
            }
        }
    }
}
