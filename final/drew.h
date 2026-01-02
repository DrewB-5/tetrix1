#ifndef DREW_H
#define DREW_H
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <atomic>
#include <mutex>

extern std::mutex mtx;
extern std::atomic<int> initialI;

int getRandomNumber();
void setMap(std::unordered_map<std::string, std::unordered_map<int, std::vector<std::vector<int>>>> &pieces);
void setNonCanonicalMode(bool enable);
bool kbhit();
std::string getch();
int dropPiece(int& initialJ, int& rotation, std::vector<std::vector<int>>& board, std::unordered_map<std::string, std::unordered_map<int, std::vector<std::vector<int>>>>& pieces, std::string& piece, std::queue<std::string>& pQueue);
void rotatePiece(int& rotation, int direction, int initialJ, const std::unordered_map<std::string, std::unordered_map<int, std::vector<std::vector<int>>>>& pieces, const std::string& piece, const std::vector<std::vector<int>>& board);
bool canMovePiece(int initialJ, int initialI, int rotation, const std::string& piece, const std::vector<std::vector<int>>& board, const std::unordered_map<std::string, std::unordered_map<int, std::vector<std::vector<int>>>>& pieces);
bool canMoveDown(int initialJ, int rotation, const std::string& piece, std::vector<std::vector<int>>& board, const std::unordered_map<std::string, std::unordered_map<int, std::vector<std::vector<int>>>>& pieces);
void placePiece(std::vector<std::vector<int>>& board, const std::vector<std::vector<int>>& currentPiece, int initialI, int initialJ);

#endif