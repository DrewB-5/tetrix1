#include "drew.h"
#include "grant.h"
#include "justin.h"
#include <atomic>
#include <chrono>
#include <ctime>
#include <iostream>
#include <queue>
#include <string>
#include <sys/select.h>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <vector>

using namespace std;

atomic<int> initialI(0);
atomic<bool> stopThread(false);

int findPiece(vector<string> pieceTypes, string piece) {
  for (size_t i = 0; i < pieceTypes.size(); i++) {
    if (pieceTypes[i] == piece)
      return i;
    else
      continue;
  }
  return 0;
}

void timerFunction() {
  chrono::time_point<chrono::steady_clock> lastTime =
      chrono::steady_clock::now();
  while (!stopThread) {
    this_thread::sleep_for(
        chrono::milliseconds(100)); // Sleep for 100ms to avoid busy-waiting
    chrono::time_point<chrono::steady_clock> now = chrono::steady_clock::now();
    chrono::seconds duration =
        chrono::duration_cast<chrono::seconds>(now - lastTime);

    if (duration.count() >= .1) {
      initialI++;     // Increment initialI after every second
      lastTime = now; // Reset the time
    }
  }
}

int main() {
  // starts the timer
  thread timerThread(timerFunction);
  int gameCounter = 0;
  while (true) {

    // runs the title screen and then sets variables/gets data needed to begin
    // game.
    pregameScreen();
    gameCounter++;
    int linesCleared = 0;

    vector<int> leaderboard;
    grabScoreData(leaderboard);
    sortScoreData(leaderboard);

    vector<vector<int>> board(22, vector<int>(14, 0));

    // Hide cursor
    cout << "\033[?25l";
    setNonCanonicalMode(true);

    unordered_map<string, unordered_map<int, vector<vector<int>>>> pieces;
    setMap(pieces);

    const vector<string> pieceTypes = {"sPiece", "iPiece", "zPiece", "lPiece",
                                       "pPiece", "tPiece", "oPiece"};
    vector<int> pieceScores(7, 0);

    // Piece queue
    queue<string> pQueue;

    for (int i = 0; i < 2; ++i) {
      int random = getRandomNumber() % 7;
      pQueue.push(pieceTypes[random]);
    }

    string piece = pQueue.front();
    int dropDistance = 0;
    int temp;
    bool game = true;

    int score = 0;
    resetBoard(board, score);
    initialI = 0;

    while (game) {
      int initialJ = 6;
      int rotation = 0;

      temp = linesCleared;

      cout << "\033[2J"; // Clear the screen

      for (int i = 0; i < 4; i++) {
        checkRows(board, linesCleared);
      }

      score += calcScore(linesCleared - temp);

      vector<vector<int>> nextPiece = pieces[pQueue.back()][0];

      printBoard(board, pieces, piece, initialJ, initialI.load(), rotation,
                 nextPiece, linesCleared, score, leaderboard, gameCounter,
                 pieceScores);

      chrono::time_point<chrono::steady_clock> inputStartTime =
          chrono::steady_clock::now();

      // Main loop for user input handling
      while (true) {
        // check if there is user input
        string input = getch();

        if (!input.empty()) {
          if (input == "left" || input == "right") {
            bool canMoveLeft = (input == "left") &&
                               canMovePiece(initialJ - 1, initialI, rotation,
                                            piece, board, pieces);
            bool canMoveRight = (input == "right") &&
                                canMovePiece(initialJ + 1, initialI, rotation,
                                             piece, board, pieces);
            initialJ += canMoveLeft ? -1 : (canMoveRight ? 1 : 0);
          } else if (input == "a" || input == "d") {
            int direction = (input == "a") ? 3 : 1;
            rotatePiece(rotation, direction, initialJ, pieces, piece, board);
          } else if (input == "s") {
            dropDistance =
                dropPiece(initialJ, rotation, board, pieces, piece, pQueue);
            score += calcScore(linesCleared - temp) + dropScore(dropDistance);
            initialI = 0;

            pieceScores[findPiece(pieceTypes, piece)]++;

            pQueue.pop();
            int random2 = getRandomNumber() % 7;
            pQueue.push(pieceTypes[random2]);
            piece = pQueue.front();
            break; // Break to get the next piece
          } else if (input == "p") {
            pQueue.pop();
            int random = getRandomNumber() % 7;
            pQueue.push(pieceTypes[random]);
            piece = pQueue.front();
            initialI = 0;
            break; // Break to get the next piece
          } else if (input == "r") {
            cout << "\033[?25h";
            stopThread = true;
            timerThread.detach();
            return 0; // Exit the game
          }

          nextPiece = pieces[pQueue.back()][0];
        }

        if (!canMoveDown(initialJ, rotation, piece, board, pieces)) {
          placePiece(board, pieces[piece][rotation], initialI, initialJ);
          pieceScores[findPiece(pieceTypes, piece)]++;

          pQueue.pop();
          int random = getRandomNumber() % 7;
          pQueue.push(pieceTypes[random]);
          piece = pQueue.front();
          initialI = 0;
          initialJ = 6;
          for (int i = 0; i < 4; i++) {
            checkRows(board, linesCleared);
          }
          score += calcScore(linesCleared - temp) + dropScore(dropDistance);
        }
        printBoard(board, pieces, piece, initialJ, initialI.load(), rotation,
                   nextPiece, linesCleared, score, leaderboard, gameCounter,
                   pieceScores);

        this_thread::sleep_for(chrono::milliseconds(16)); // ~60 fps

        // if 1 second has passed to update
        chrono::time_point<chrono::steady_clock> now =
            chrono::steady_clock::now();
        chrono::seconds elapsed =
            chrono::duration_cast<chrono::seconds>(now - inputStartTime);

        if (elapsed.count() >= 1) {
          inputStartTime = now;
        }
        if ((board[0][6] != 0) || (board[0][7] != 0)) {
          cout << "\033[?25l";

          writeScoreData(score);

          bool restart = gameOver(linesCleared, score);

          cout << "\033[?25h" << endl;

          game = false;
          if (!restart) {
            cout << "\033[?25h";
            stopThread = true;

            timerThread.detach();
            return 0; // Exit the game
          }
          break;
        }
      }
    }
  }
}
