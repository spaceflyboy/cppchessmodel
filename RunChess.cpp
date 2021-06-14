
#include <iostream>
#include "chessgame.hpp"
#include "chesspiece.hpp"
using namespace std;

int main() {
	ChessGame *game = new ChessGame();
	game->initializeBoard_default();
	while(!game->hasEnded()) {
		int startR;
		cin >> startR;
		int startC;
		cin >> startC;
		int endR;
		cin >> endR;
		int endC;
		cin >> endC;
		bool check = makeMove(startR, startC, endR, endC);
		if(check) {
			game->printBoard(cout, true);
		} else {
			cout << "Failed to make move from (" << startR << "," << startC << ") to (" << endR << "," << endC << ")" << endl;
		}
	}
	
}