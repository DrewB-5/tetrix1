#include "grant.h"

using namespace std;

int calcScore(int clearCount) { // Scoring for each line cleared at once, 1-4.
  if (clearCount == 1) {
    return 40;
  }
  if (clearCount == 2) {
    return 100;
  }
  if (clearCount == 3) {
    return 300;
  }
  if (clearCount == 4) {
    return 1200;
  }

  return 0;
}

int dropScore(int dropDistance){

  return (20-dropDistance)+(dropDistance*2); //Score equation for piece falling and piece placed


}

int checkRows(vector<vector<int>> & board, int &linesCleared){ //Checking board vector for a complete row of non-zero values
	int index = -1;
	for(int i = 0; i < 20; i++){ //Playing field width
		bool full = true;
		for(int j = 2; j < 12; j++){ //Playing field height
			if(board[i][j] == 0){
				full = false;
				break;
			}
		}
		if(full){
			index = i;
			break;
		}
	}

	if (index != -1) {
		board.erase(board.begin() + index); //Clearing the line, dropping established blocks
		board.insert(board.begin(), vector<int>(14, 0));
		linesCleared++; //For score
	}
	
	return 0;
}

void resetBoard(vector<vector<int> > &wipedBoard, int score){

    wipedBoard.resize(22, vector<int>(14, 0)); //reset board vector

    score = 0; //global
}
