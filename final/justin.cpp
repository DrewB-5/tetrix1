#include "justin.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <unordered_map>
#include <vector>

using namespace std;

// This function  takes the score from the game and writes it to a text file
// called data.txt. If there is no file, it will create one and then write it.
void writeScoreData(int score) {

  ofstream outputFile("data.txt", ios_base::app);

  outputFile << score << endl;

  outputFile.close();
}

// Used for debugging, not used in main. If you (the tester) need to reset
// leaderboard, please just type "rm data.txt" into your terminal and play the
// game again.
void eraseScoreData(vector<int> leaderboard) {
  system("rm data.txt");
  leaderboard.resize(1);
}

// Takes in the data from data.txt so that the leaderboard isn't specific to one
// session of the game. It puts it into a vector (this is important later.)
void grabScoreData(vector<int> &leaderboard) {
  string storedScoreString;

  ifstream inputFile("data.txt");

  while (getline(inputFile, storedScoreString)) {
    int storedScore;
    istringstream stringToInt(storedScoreString);

    stringToInt >> storedScoreString;

    storedScore = stoi(storedScoreString);
    leaderboard.push_back(storedScore);
  }

  inputFile.close();
}

// Using the data vector, it will sort it so that it has a leaderboard from
// highest score to lowest.
void sortScoreData(vector<int> &leaderboard) {
  sort(leaderboard.begin(), leaderboard.end());
}

// Used for debugging
int leaderboardDisplay(int placement, vector<int> leaderboard) {
  return leaderboard[(leaderboard.size() - placement)];
}

void pregameScreen() {

  // The following code looks chaotic, however it is just "animating" the
  // title card through ascii art.
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }

  cout << "        \\|__|    \\|_______|     \\|__|    \\|__|\\|__|   \\|__| "
          "/_/___/  \\___\\ "
       << endl;

  usleep(500000);
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }

  cout << "       \\ \\__\\   \\ \\_______\\    \\ \\__\\   \\ \\__\\\\ _\\   "
          "\\ \\__\\  / /   /\\   \\  "
       << endl;
  cout << "        \\|__|    \\|_______|     \\|__|    \\|__|\\|__|   \\|__| "
          "/_/___/  \\___\\ "
       << endl;

  usleep(500000);
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }

  cout << "      \\ \\  \\   \\ \\  \\_|\\ \\    \\ \\  \\   \\ \\  \\\\  "
          "\\|  "
          "\\ \\  \\    / /      \\   "
       << endl;
  cout << "       \\ \\__\\   \\ \\_______\\    \\ \\__\\   \\ \\__\\\\ _\\   "
          "\\ \\__\\  / /   /\\   \\  "
       << endl;
  cout << "        \\|__|    \\|_______|     \\|__|    \\|__|\\|__|   \\|__| "
          "/_/___/  \\___\\ "
       << endl;

  usleep(500000);
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }

  cout << "     \\ \\  \\   \\ \\  \\_|/__    \\ \\  \\   \\ \\   _  _\\  \\ "
          "\\  \\     \\_\\      /   "
       << endl;
  cout << "      \\ \\  \\   \\ \\  \\_|\\ \\    \\ \\  \\   \\ \\  \\\\  "
          "\\|  "
          "\\ \\  \\    / /      \\   "
       << endl;
  cout << "       \\ \\__\\   \\ \\_______\\    \\ \\__\\   \\ \\__\\\\ _\\   "
          "\\ \\__\\  / /   /\\   \\  "
       << endl;
  cout << "        \\|__|    \\|_______|     \\|__|    \\|__|\\|__|   \\|__| "
          "/_/___/  \\___\\ "
       << endl;

  usleep(500000);
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }

  cout << "\\|___ \\  \\_| \\ \\   __/| \\|___ \\  \\_| \\ \\  \\|\\  \\  \\ "
          "\\  \\     \\ \\   \\/   /  "
       << endl;
  cout << "     \\ \\  \\   \\ \\  \\_|/__    \\ \\  \\   \\ \\   _  _\\  \\ "
          "\\  \\     \\_\\      /   "
       << endl;
  cout << "      \\ \\  \\   \\ \\  \\_|\\ \\    \\ \\  \\   \\ \\  \\\\  "
          "\\|  "
          "\\ \\  \\    / /      \\   "
       << endl;
  cout << "       \\ \\__\\   \\ \\_______\\    \\ \\__\\   \\ \\__\\\\ _\\   "
          "\\ \\__\\  / /   /\\   \\  "
       << endl;
  cout << "        \\|__|    \\|_______|     \\|__|    \\|__|\\|__|   \\|__| "
          "/_/___/  \\___\\ "
       << endl;

  usleep(500000);
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }

  cout << "|\\___   ___\\ |\\  ___ \\  |\\___   ___\\ |\\   __  \\   |\\  \\ "
          "  "
          "   |\\   \\  /   / "
       << endl;
  cout << "\\|___ \\  \\_| \\ \\   __/| \\|___ \\  \\_| \\ \\  \\|\\  \\  \\ "
          "\\  \\     \\ \\   \\/   /  "
       << endl;
  cout << "     \\ \\  \\   \\ \\  \\_|/__    \\ \\  \\   \\ \\   _  _\\  \\ "
          "\\  \\     \\_\\      /   "
       << endl;
  cout << "      \\ \\  \\   \\ \\  \\_|\\ \\    \\ \\  \\   \\ \\  \\\\  "
          "\\|  "
          "\\ \\  \\    / /      \\   "
       << endl;
  cout << "       \\ \\__\\   \\ \\_______\\    \\ \\__\\   \\ \\__\\\\ _\\   "
          "\\ \\__\\  / /   /\\   \\  "
       << endl;
  cout << "        \\|__|    \\|_______|     \\|__|    \\|__|\\|__|   \\|__| "
          "/_/___/  \\___\\ "
       << endl;

  usleep(500000);
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }

  cout << " _________    _______    _________    ________     ___        "
          "____  "
          "  ____ "
       << endl;
  cout << "|\\___   ___\\ |\\  ___ \\  |\\___   ___\\ |\\   __  \\   |\\  \\ "
          "  "
          "   |\\   \\  /   / "
       << endl;
  cout << "\\|___ \\  \\_| \\ \\   __/| \\|___ \\  \\_| \\ \\  \\|\\  \\  \\ "
          "\\  \\     \\ \\   \\/   /  "
       << endl;
  cout << "     \\ \\  \\   \\ \\  \\_|/__    \\ \\  \\   \\ \\   _  _\\  \\ "
          "\\  \\     \\_\\      /   "
       << endl;
  cout << "      \\ \\  \\   \\ \\  \\_|\\ \\    \\ \\  \\   \\ \\  \\\\  "
          "\\|  "
          "\\ \\  \\    / /      \\   "
       << endl;
  cout << "       \\ \\__\\   \\ \\_______\\    \\ \\__\\   \\ \\__\\\\ _\\   "
          "\\ \\__\\  / /   /\\   \\  "
       << endl;
  cout << "        \\|__|    \\|_______|     \\|__|    \\|__|\\|__|   \\|__| "
          "/_/___/  \\___\\ "
       << endl;

  usleep(500000);
  cout << endl;
  cout << "A Tetris clone made by Drew B, Grant J, and Justin W." << endl;
  cout << "S. Emrich's CS202 - F24" << endl;

  usleep(3500000);
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }
}

void printBoard(
    vector<vector<int>> board,
    unordered_map<string, unordered_map<int, vector<vector<int>>>> &pieces,
    string piece, int initialJ, int initialI, int rotation,
    vector<vector<int>> nextPiece, int linesCleared, int score,
    vector<int> leaderboard, int gameCounter, vector<int> pieceScores) {
  cout << "\033[H"; // move cursor to the top-left corner
  const char *user = getenv("USER");

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (pieces[piece][rotation][i][j] != 0) {
        board[i + initialI][j + initialJ] = pieces[piece][rotation][i][j];
      }
    }
  }

  // This section will output/format the amt of lines cleared and current user
  // score. Also will output the UT logo seen to the right of that on the
  // display.
  cout << "================================     ";

  cout << "\033[38;5;214m◼\033[0m"
       << "   "
       << "\033[38;5;214m◼\033[0m"
       << "     " << endl;

  cout << "|         LINES - ";
  if (linesCleared < 10) {
    cout << "000" << linesCleared << "         |   ";
    for (int i = 0; i < 9; i++) {
      vector<void *> vals;

      cout << "\033[38;5;214m◼\033[0m";
    }
    cout << "   " << endl;
  } else if (linesCleared < 100) {
    cout << "00" << linesCleared << "         |   ";
    for (int i = 0; i < 9; i++) {
      cout << "\033[38;5;214m◼\033[0m";
    }
    cout << "   " << endl;
  } else if (linesCleared < 1000) {
    cout << "0" << linesCleared << "         |   ";
    for (int i = 0; i < 9; i++) {
      cout << "\033[38;5;214m◼\033[0m";
    }
    cout << "   " << endl;
  }

  else if (linesCleared < 10000) {
    cout << linesCleared << "         |   ";
    for (int i = 0; i < 9; i++) {
      cout << "\033[38;5;214m◼\033[0m";
    }
    cout << "   " << endl;
  }

  else {
    cout << "9999         |   ";
    for (int i = 0; i < 9; i++) {
      cout << "\033[38;5;214m◼\033[0m";
    }
    cout << "   " << endl;
  }

  cout << "================================   ";
  for (int i = 1; i <= 9; i++) {
    if (!(i % 2 == 0)) {
      cout << "\033[38;5;214m◼\033[0m";
    } else {
      cout << " ";
    }
  }
  cout << "   " << endl;

  cout << "|        SCORE - ";

  if (score < 10) {
    cout << "00000" << score << "        |     ";
    for (int i = 0; i < 5; i++) {
      cout << "\033[38;5;214m◼\033[0m";
    }
    cout << "     " << endl;
  }

  else if (score < 100) {
    cout << "0000" << score << "        |     ";
    for (int i = 0; i < 5; i++) {
      cout << "\033[38;5;214m◼\033[0m";
    }
    cout << "     " << endl;
  }

  else if (score < 1000) {
    cout << "000" << score << "        |     ";
    for (int i = 0; i < 5; i++) {
      cout << "\033[38;5;214m◼\033[0m";
    }
    cout << "     " << endl;
  }

  else if (score < 10000) {
    cout << "00" << score << "        |     ";
    for (int i = 0; i < 5; i++) {
      cout << "\033[38;5;214m◼\033[0m";
    }
    cout << "     " << endl;
  }

  else if (score < 100000) {
    cout << "0" << score << "        |     ";
    for (int i = 0; i < 5; i++) {
      cout << "\033[38;5;214m◼\033[0m";
    }
    cout << "     " << endl;
  }

  else {
    cout << "ERROR         |     ";
    for (int i = 0; i < 5; i++) {
      cout << "\033[38;5;214m◼\033[0m";
    }
    cout << "     " << endl;
  }

  cout << "================================      ";
  for (int i = 0; i < 3; i++) {
    cout << "\033[38;5;214m◼\033[0m";
  }
  cout << "     " << endl;

  // This begins board output.
  cout << "===============================================" << endl;
  for (int i = 0; i < 20; i++) {
    cout << "| ";
    for (int j = 2; j < 12; j++) {
      if (board[i][j] == 1)
        cout << "\033[35m◼\033[0m ";
      else if (board[i][j] == 2)
        cout << "\033[38;5;9m◼\033[0m ";
      else if (board[i][j] == 3)
        cout << "\033[32m◼\033[0m ";
      else if (board[i][j] == 4)
        cout << "\033[38;5;214m◼\033[0m ";
      else if (board[i][j] == 5)
        cout << "\033[38;5;105m◼\033[0m ";
      else if (board[i][j] == 6)
        cout << "\033[36m◼\033[0m ";
      else if (board[i][j] == 7)
        cout << "\033[33m◼\033[0m ";
      else
        cout << ". ";
      if (j < 11)
        cout << " ";
    }

    // next piece display
    if (i == 0)
      cout << "||    NEXT!   ||";
    if (i == 1) {
      cout << "|| ";
      for (int k = 0; k < 4; k++) {
        if (k != 0)
          cout << " ";
        if (nextPiece[0][k] == 1)
          cout << "\033[35m◼\033[0m ";
        else if (nextPiece[0][k] == 2)
          cout << "\033[38;5;9m◼\033[0m ";
        else if (nextPiece[0][k] == 3)
          cout << "\033[32m◼\033[0m ";
        else if (nextPiece[0][k] == 4)
          cout << "\033[38;5;214m◼\033[0m ";
        else if (nextPiece[0][k] == 5)
          cout << "\033[38;5;105m◼\033[0m ";
        else if (nextPiece[0][k] == 6)
          cout << "\033[36m◼\033[0m ";
        else if (nextPiece[0][k] == 7)
          cout << "\033[33m◼\033[0m ";
        else
          cout << ". ";
      }
      cout << "||";
    }
    if (i == 2) {
      cout << "|| ";
      for (int k = 0; k < 4; k++) {
        if (k != 0)
          cout << " ";
        if (nextPiece[1][k] == 1)
          cout << "\033[35m◼\033[0m ";
        else if (nextPiece[1][k] == 2)
          cout << "\033[38;5;9m◼\033[0m ";
        else if (nextPiece[1][k] == 3)
          cout << "\033[32m◼\033[0m ";
        else if (nextPiece[1][k] == 4)
          cout << "\033[38;5;214m◼\033[0m ";
        else if (nextPiece[1][k] == 5)
          cout << "\033[38;5;105m◼\033[0m ";
        else if (nextPiece[1][k] == 6)
          cout << "\033[36m◼\033[0m ";
        else if (nextPiece[1][k] == 7)
          cout << "\033[33m◼\033[0m ";
        else
          cout << ". ";
      }
      cout << "||";
    }
    if (i == 3) {
      cout << "|| ";
      for (int k = 0; k < 4; k++) {
        if (k != 0)
          cout << " ";
        if (nextPiece[2][k] == 1)
          cout << "\033[35m◼\033[0m ";
        else if (nextPiece[2][k] == 2)
          cout << "\033[38;5;9m◼\033[0m ";
        else if (nextPiece[2][k] == 3)
          cout << "\033[32m◼\033[0m ";
        else if (nextPiece[2][k] == 4)
          cout << "\033[38;5;214m◼\033[0m ";
        else if (nextPiece[2][k] == 5)
          cout << "\033[38;5;105m◼\033[0m ";
        else if (nextPiece[2][k] == 6)
          cout << "\033[36m◼\033[0m ";
        else if (nextPiece[2][k] == 7)
          cout << "\033[33m◼\033[0m ";
        else
          cout << ". ";
      }
      cout << "||";
    }
    if (i == 4) {
      cout << "|| ";
      for (int k = 0; k < 4; k++) {
        if (k != 0)
          cout << " ";
        if (nextPiece[3][k] == 1)
          cout << "\033[35m◼\033[0m ";
        else if (nextPiece[3][k] == 2)
          cout << "\033[38;5;9m◼\033[0m ";
        else if (nextPiece[3][k] == 3)
          cout << "\033[32m◼\033[0m ";
        else if (nextPiece[3][k] == 4)
          cout << "\033[38;5;214m◼\033[0m ";
        else if (nextPiece[3][k] == 5)
          cout << "\033[38;5;105m◼\033[0m ";
        else if (nextPiece[3][k] == 6)
          cout << "\033[36m◼\033[0m ";
        else if (nextPiece[3][k] == 7)
          cout << "\033[33m◼\033[0m ";
        else
          cout << ". ";
      }
      cout << "||";
    }

    // Leaderboard output. Takes data from sorted leaderboard vector to output
    // correct data.
    if (i == 5) {
      cout << "|===============";
    }
    if (i == 6) {

      cout << "| LEADERBOARD! ";
    }

    if (i == 7) {
      if (leaderboard.size() > 0) {
        cout << "|" << user << " " << leaderboard[leaderboard.size() - 1];
      } else {
        cout << "|" << user << "  NULL";
      }
    }
    if (i == 8) {
      if (leaderboard.size() > 1) {
        cout << "|" << user << " " << leaderboard[leaderboard.size() - 2];
      } else {
        cout << "|" << user << "  NULL";
      }
    }
    if (i == 9) {
      if (leaderboard.size() > 2) {
        cout << "|" << user << " " << leaderboard[leaderboard.size() - 3];
      } else {
        cout << "|" << user << "  NULL";
      }
    }
    if (i == 10) {
      if (leaderboard.size() > 3) {
        cout << "|" << user << " " << leaderboard[leaderboard.size() - 4];
      } else {
        cout << "|" << user << "  NULL";
      }
    }
    if (i == 11) {
      if (leaderboard.size() > 4) {
        cout << "|" << user << " " << leaderboard[leaderboard.size() - 5];
      } else {
        cout << "|" << user << "  NULL";
      }
    }

    // This section begins the piece stat section. It will output the amount of
    // pieces placed per type using a vector in which each index of the vector
    // corresponds to a piece, and then will add 1 to that index's data to get a
    // proper amount of pieces placed.
    if (i == 12) {
      cout << "|===============";
    }
    if (i == 13) {
      cout << "|L-Pieces:";
      if (pieceScores[3] < 10) {
        cout << "  00" << pieceScores[3] << "|";
      } else if (pieceScores[3] < 100) {
        cout << "  0" << pieceScores[3] << "|";
      } else if (pieceScores[3] < 1000) {
        cout << "  " << pieceScores[3] << "|";
      }
    }
    if (i == 14) {
      cout << "|O-Pieces:";
      if (pieceScores[6] < 10) {
        cout << "  00" << pieceScores[6] << "|";
      } else if (pieceScores[6] < 100) {
        cout << "  0" << pieceScores[6] << "|";
      } else if (pieceScores[6] < 1000) {
        cout << "  " << pieceScores[6] << "|";
      }
    }
    if (i == 15) {
      cout << "|I-Pieces:";
      if (pieceScores[1] < 10) {
        cout << "  00" << pieceScores[1] << "|";
      } else if (pieceScores[1] < 100) {
        cout << "  0" << pieceScores[1] << "|";
      } else if (pieceScores[1] < 1000) {
        cout << "  " << pieceScores[1] << "|";
      }
    }
    if (i == 16) {
      cout << "|T-Pieces:";
      if (pieceScores[5] < 10) {
        cout << "  00" << pieceScores[5] << "|";
      } else if (pieceScores[5] < 100) {
        cout << "  0" << pieceScores[5] << "|";
      } else if (pieceScores[5] < 1000) {
        cout << "  " << pieceScores[5] << "|";
      }
    }
    if (i == 17) {
      cout << "|P-Pieces:";
      if (pieceScores[4] < 10) {
        cout << "  00" << pieceScores[4] << "|";
      } else if (pieceScores[4] < 100) {
        cout << "  0" << pieceScores[4] << "|";
      } else if (pieceScores[4] < 1000) {
        cout << "  " << pieceScores[4] << "|";
      }
    }
    if (i == 18) {
      cout << "|S-Pieces:";
      if (pieceScores[0] < 10) {
        cout << "  00" << pieceScores[0] << "|";
      } else if (pieceScores[0] < 100) {
        cout << "  0" << pieceScores[0] << "|";
      } else if (pieceScores[0] < 1000) {
        cout << "  " << pieceScores[0] << "|";
      }
    }
    if (i == 19) {
      cout << "|Z-Pieces:";
      if (pieceScores[2] < 10) {
        cout << "  00" << pieceScores[2] << "|";
      } else if (pieceScores[2] < 100) {
        cout << "  0" << pieceScores[2] << "|";
      } else if (pieceScores[2] < 1000) {
        cout << "  " << pieceScores[2] << "|";
      }
    }

    cout << endl;
  }
  cout << "===============================================" << endl;
}

// This function is more ascii art to output "game over" and the final
// score/lines cleared. Also asks user if they'd like to play again.
bool gameOver(int linesCleared, int score) {
  char YN;
  bool YNbool = false;
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }
  cout << "  \\/_____/   \\/_/\\/_/   \\/_/  \\/_/   \\/_____/      "
          "\\/_____/  "
          " \\/_/      \\/_____/   \\/_/ /_/"
       << endl;
  usleep(500000);
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }
  cout << " \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_\\ \\ \\_\\  \\ \\_____\\     "
          "\\ \\_____\\  \\ \\__|    \\ \\_____\\  \\ \\_\\ \\_\\"
       << endl;
  cout << "  \\/_____/   \\/_/\\/_/   \\/_/  \\/_/   \\/_____/      "
          "\\/_____/  "
          " \\/_/      \\/_____/   \\/_/ /_/"
       << endl;
  usleep(500000);
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }
  cout << "\\ \\ \\__ \\  \\ \\  __ \\  \\ \\ \\-./\\ \\  \\ \\  __\\      \\ "
          "\\ \\/\\ \\  \\ \\ \\'/   \\ \\  __\\   \\ \\  __<"
       << endl;
  cout << " \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_\\ \\ \\_\\  \\ \\_____\\     "
          "\\ \\_____\\  \\ \\__|    \\ \\_____\\  \\ \\_\\ \\_\\"
       << endl;
  cout << "  \\/_____/   \\/_/\\/_/   \\/_/  \\/_/   \\/_____/      "
          "\\/_____/  "
          " \\/_/      \\/_____/   \\/_/ /_/"
       << endl;

  usleep(500000);
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }
  cout << "/\\  ___\\   /\\  __ \\   /\\ '-./  \\   /\\  ___\\      /\\  __ "
          "\\ "
          "  /\\ \\ / /  /\\  ___\\   /\\  == \\"
       << endl;
  cout << "\\ \\ \\__ \\  \\ \\  __ \\  \\ \\ \\-./\\ \\  \\ \\  __\\      \\ "
          "\\ \\/\\ \\  \\ \\ \\'/   \\ \\  __\\   \\ \\  __<"
       << endl;
  cout << " \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_\\ \\ \\_\\  \\ \\_____\\     "
          "\\ \\_____\\  \\ \\__|    \\ \\_____\\  \\ \\_\\ \\_\\"
       << endl;
  cout << "  \\/_____/   \\/_/\\/_/   \\/_/  \\/_/   \\/_____/      "
          "\\/_____/  "
          " \\/_/      \\/_____/   \\/_/ /_/"
       << endl;
  usleep(500000);
  for (int i = 0; i < 100; i++) {
    cout << endl;
  }
  cout << " ______     ______     __    __     ______        ______     __   "
          "__   ______     ______"
       << endl;
  cout << "/\\  ___\\   /\\  __ \\   /\\ '-./  \\   /\\  ___\\      /\\  __ "
          "\\ "
          "  /\\ \\ / /  /\\  ___\\   /\\  == \\"
       << endl;
  cout << "\\ \\ \\__ \\  \\ \\  __ \\  \\ \\ \\-./\\ \\  \\ \\  __\\      \\ "
          "\\ \\/\\ \\  \\ \\ \\'/   \\ \\  __\\   \\ \\  __<"
       << endl;
  cout << " \\ \\_____\\  \\ \\_\\ \\_\\  \\ \\_\\ \\ \\_\\  \\ \\_____\\     "
          "\\ \\_____\\  \\ \\__|    \\ \\_____\\  \\ \\_\\ \\_\\"
       << endl;
  cout << "  \\/_____/   \\/_/\\/_/   \\/_/  \\/_/   \\/_____/      "
          "\\/_____/  "
          " \\/_/      \\/_____/   \\/_/ /_/"
       << endl;
  usleep(500000);
  cout << '\n'
       << "You cleared " << linesCleared << " lines and your score was "
       << score << "!" << endl;
  cout << '\n' << "Would you like to play again? (y/n): ";
  while (cin >> YN) {

    // Validate the input
    if (YN != 'y' && YN != 'n') {
      cerr << "Invalid input! Please type 'y' or 'n'" << endl;
    } else {
      if (YN == 'y') {
        YNbool = true;
        return YNbool;
      } else {
        return YNbool;
      }
    }
  }
  return false;
  cout << endl;
}
