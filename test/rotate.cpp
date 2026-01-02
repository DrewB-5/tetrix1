#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>

using namespace std;

void printPiece(unordered_map<string, unordered_map<int, vector<vector<int>>>>& pieces, int rotation, string piece) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(pieces[piece][rotation][i][j] == 1) cout << "\033[35m◼\033[0m  ";
            else if(pieces[piece][rotation][i][j] == 2) cout << "\033[38;5;9m◼\033[0m  ";
            else if(pieces[piece][rotation][i][j] == 3) cout << "\033[32m◼\033[0m  ";
            else if(pieces[piece][rotation][i][j] == 4) cout << "\033[38;5;214m◼\033[0m  ";
            else if(pieces[piece][rotation][i][j] == 5) cout << "\033[38;5;105m◼\033[0m  ";
            else if(pieces[piece][rotation][i][j] == 6) cout << "\033[36m◼\033[0m  ";
            else if(pieces[piece][rotation][i][j] == 7) cout << "\033[33m◼\033[0m  ";
            else cout << ".  ";
        }
        cout << endl;
    }
}

void delay(int seconds) {
    time_t start_time = time(NULL);  // Get current time
    while (time(NULL) < start_time + seconds);  // Loop until desired time has passed
}

string getch() {
    struct termios oldt, newt;
    char ch[3]; // Buffer for 3 characters (for escape sequences)
    string result;

    // Get the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical mode and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read one character
    ch[0] = getchar();

    result = std::string(1, ch[0]); // If it's a regular character, create a string

    // Restore the old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    return result;
}

int main() {
    unordered_map<string, unordered_map<int, vector<vector<int>>>> pieces;
    srand(static_cast<unsigned int>(time(0)));
    string piece;

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
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
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
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {2, 2, 2, 2},
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
        {7, 7, 0, 0},
        {7, 7, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["oPiece"][1] = {
        {7, 7, 0, 0},
        {7, 7, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["oPiece"][2] = {
        {7, 7, 0, 0},
        {7, 7, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
    pieces["oPiece"][3] = {
        {7, 7, 0, 0},
        {7, 7, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    string roKey;
    int rotation = 0;
    for (int i = 0; i < 7; i ++){
        //int randomPiece = rand() % 7;
        int randomPiece = i;
        if (randomPiece == 0) piece = "sPiece";
        else if(randomPiece == 1) piece = "iPiece";
        else if(randomPiece == 2) piece = "zPiece";
        else if(randomPiece == 3) piece = "lPiece";
        else if(randomPiece == 4) piece = "pPiece";
        else if(randomPiece == 5) piece = "tPiece";
        else piece = "oPiece";

        printPiece(pieces, rotation, piece);
        while (true) {
            roKey = getch();
            if (roKey == "a") {
                rotation = (rotation + 3) % 4;
                printPiece(pieces, rotation, piece);
            } else if (roKey == "d") {
                rotation = (rotation + 1) % 4;
                printPiece(pieces, rotation, piece);
            } else if (roKey == "q") {
                break;
            } else continue;
        }
    }
    return 0;
}
