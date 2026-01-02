#ifndef GRANT_H
#define GRANT_H
#include <vector>

int checkRows(std::vector<std::vector<int>> &board, int &linesCleared);
void resetBoard(std::vector<std::vector<int> >& wipedBoard, int score);
int calcScore(int clearCount);
int dropScore(int dropDistance);

#endif