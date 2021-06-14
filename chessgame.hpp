#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <iostream>
#include <vector>
#include "chesspiece.hpp"
using namespace std;

#define WHITE 0
#define BLACK 1
#define GAMEDEBUG 1
class ChessGame {
    vector<vector<ChessPiece *>> gameBoard;
    int height;
    int width;
    int king_w_rPos;
    int king_w_cPos;
    int king_b_rPos;
    int king_b_cPos;
    int scr_w;
    int scr_b;
	int turnNumber;
	bool active;
	bool whiteToMove;
	ChessPiece *whiteKing;
	ChessPiece *blackKing;
public:
    ChessGame(int height = 8, int width = 8) : height(height), width(width), king_w_rPos(-1), king_w_cPos(-1), king_b_rPos(-1), king_b_cPos(-1), scr_w(0), scr_b(0), turnNumber(-1), active(false), whiteToMove(true) {
        gameBoard.reserve(height*width);
        for(int r = 0; r < height; r++) {
			vector<ChessPiece *> row;
			row.reserve(width);
            for(int c = 0; c < width; c++) {
                row.emplace_back();
            }
			gameBoard.emplace_back(row);
        }
    }

    ~ChessGame() {
        for(int r = 0; r < height; r++) {
            for(int c = 0; c < width; c++) {
                if(gameBoard[r][c]) delete gameBoard[r][c];
            }
        }
    }

    void initializeBoard_default(void);

    //bool squareIsWhite(int r, int c);

    void printBoard(ostream& sout, bool showColor);
	
	bool hasEnded() { return !active; }
	
	/*bool placePiece(ChessPiece *piece, int r, int c) {
		
	}
	
	bool removePiece(ChessPiece *piece, int r, int c) {
		
	}*/

    bool makeMove(int sourceR, int sourceC, int destR, int destC);
};

#endif
