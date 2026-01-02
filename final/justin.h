#ifndef JUSTIN_H
#define JUSTIN_H
#include <string>
#include <unordered_map>
#include <vector>

void pregameScreen(); // Title card sequence.
void display();       // Backbone of the entire game, displays the game.
void writeScoreData(int score); // Writes score to data.txt.
void eraseScoreData(
    std::vector<int>
        leaderboard); // Erases data.txt and clears out the leaderboard vector.
void grabScoreData(std::vector<int> &leaderboard); // Grabs data.txt and inputs
// into leaderboard vector.
void sortScoreData(
    std::vector<int> &leaderboard); // Sorts score least to greatest.
int leaderboardDisplay(
    int placement,
    std::vector<int> leaderboard); // Displays the score for 1st through 5th
void printBoard(
    std::vector<std::vector<int>> board,
    std::unordered_map<std::string,
                       std::unordered_map<int, std::vector<std::vector<int>>>>
        &pieces,
    std::string piece, int initialJ, int initialI, int rotation,
    std::vector<std::vector<int>> nextPiece, int linesCleared, int score,
    std::vector<int> leaderboard, int gameCounter, std::vector<int> pieceScore);
bool gameOver(int linesCleared, int score); // Ending screen
#endif
