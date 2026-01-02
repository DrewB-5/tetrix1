#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

using namespace std;

void printBoard(vector<vector<int> > board, vector<vector<int> > piece, int initialJ){
    //Move cursor to the top-left corner
    cout << "\033[H";
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            board[i][j + initialJ] = piece[i][j];
        }
    }

    for(int i = 0; i < 20; i++){
        for(int j = 2; j < 12; j++){
            if (board[i][j] == 0) cout << ".  ";
            else cout << "\033[35m◼\033[0m  ";
        }
        cout << endl;
    }
}

int pWidth(vector<vector<int> > piece) {
    int width = 0;
    for (int j = 0; j < 4; j++) {
        bool columnHasBlock = false;
        for (int i = 0; i < 4; i++) {
            if (piece[i][j] == 1) {
                columnHasBlock = true;
                break;
            }
        }
        if (columnHasBlock) width++;
    }
    return width;
}

int lBoundary(vector<vector<int> > piece) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (piece[i][j] == 1) return j;
        }
    }
    return 0;
}

void setNonCanonicalMode(bool enable) {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    if (enable) {
        term.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    } else {
        term.c_lflag |= (ICANON | ECHO);   // Enable canonical mode and echo
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

bool kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

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

int main(){
    //Hide cursor
    cout << "\033[?25l";
    
    setNonCanonicalMode(true);
    
    vector<vector<int> > board;
    board.resize(20);
    for (size_t i = 0; i < 20; i++){
        board[i].resize(14, 0);
    }

    string input = "";
    vector<vector<int> > piece = {{0, 0, 1, 0},{0, 0, 1, 0},{0, 0, 1, 0},{0, 0, 0, 0}};
    int initialJ = 6;
    
    //Clear the screen at the start
    cout << "\033[2J";
    
    printBoard(board, piece, initialJ);
    
    while (true){
        input = getch();
        if (input != "") {
            int pieceWidth = pWidth(piece);
            int pieceLeftBoundary = lBoundary(piece);

            if (input == "left") {
                if (initialJ > 2 - pieceLeftBoundary) initialJ--;
            } 
            else if (input == "right") {
                if (initialJ < 12 - (pieceWidth + pieceLeftBoundary)) initialJ++;
            }
            else if (input == "q") break;
        }
        printBoard(board, piece, initialJ);
        usleep(16667); //60fps
    }

    //Restore terminal settings and show cursor
    setNonCanonicalMode(false);
    cout << "\033[?25h";

    return 0;
}
