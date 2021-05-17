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
public:
    ChessGame(int height = 8, int width = 8) : height(height), width(width), king_w_rPos(-1), king_w_cPos(-1), king_b_rPos(-1), king_b_cPos(-1), scr_w(0), scr_b(0) {
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

    void initializeBoard_default(void) {
        
        constexpr int king_w_start_row = 7;
        constexpr int king_w_start_col = 4;
        constexpr int king_b_start_row = 0;
        constexpr int king_b_start_col = 4;

        constexpr int pawn_w_start_row = 6;
        constexpr int pawn_w_start_col = 0;
        constexpr int pawn_b_start_row = 1;
        constexpr int pawn_b_start_col = 0;

        constexpr int knight1_w_start_row = 7; 
        constexpr int knight1_w_start_col = 1;
        constexpr int knight1_b_start_row = 0; 
        constexpr int knight1_b_start_col = 1;

        constexpr int knight2_w_start_row = 7;
        constexpr int knight2_w_start_col = 6;
        constexpr int knight2_b_start_row = 0;
        constexpr int knight2_b_start_col = 6;
        
        constexpr int bishop1_w_start_row = 7;
        constexpr int bishop1_w_start_col = 2;
        constexpr int bishop1_b_start_row = 0;
        constexpr int bishop1_b_start_col = 2;

        constexpr int bishop2_w_start_row = 7;
        constexpr int bishop2_w_start_col = 5;
        constexpr int bishop2_b_start_row = 0;
        constexpr int bishop2_b_start_col = 5;

        constexpr int rook1_w_start_row = 7;
        constexpr int rook1_w_start_col = 0;
        constexpr int rook1_b_start_row = 0;
        constexpr int rook1_b_start_col = 0;

        constexpr int rook2_w_start_row = 7;
        constexpr int rook2_w_start_col = 7;
        constexpr int rook2_b_start_row = 0;
        constexpr int rook2_b_start_col = 7;

        constexpr int queen_w_start_row = 7;
        constexpr int queen_w_start_col = 3;
        constexpr int queen_b_start_row = 0;
        constexpr int queen_b_start_col = 3;
        

        gameBoard[king_w_start_row][king_w_start_col] = new King(WHITE);
        gameBoard[king_b_start_row][king_b_start_col] = new King(BLACK);
        king_w_rPos = king_w_start_row;
        king_w_cPos = king_w_start_col;
        king_b_rPos = king_b_start_row;
        king_b_cPos = king_b_start_col;

        for(int c = pawn_w_start_col; c < width; c++) {
            gameBoard[pawn_w_start_row][c] = new Pawn(WHITE);
        }

        for(int c = pawn_b_start_col; c < width; c++) {
            gameBoard[pawn_b_start_row][c] = new Pawn(BLACK);
        }

        gameBoard[knight1_w_start_row][knight1_w_start_col] = new Knight(WHITE);
        gameBoard[knight2_w_start_row][knight2_w_start_col] = new Knight(WHITE);
        gameBoard[knight1_b_start_row][knight1_b_start_col] = new Knight(BLACK);
        gameBoard[knight2_b_start_row][knight2_b_start_col] = new Knight(BLACK);

        gameBoard[bishop1_w_start_row][bishop1_w_start_col] = new Bishop(WHITE);
        gameBoard[bishop2_w_start_row][bishop2_w_start_col] = new Bishop(WHITE);
        gameBoard[bishop1_b_start_row][bishop1_b_start_col] = new Bishop(BLACK);
        gameBoard[bishop2_b_start_row][bishop2_b_start_col] = new Bishop(BLACK);

        gameBoard[rook1_w_start_row][rook1_w_start_col] = new Rook(WHITE);
        gameBoard[rook2_w_start_row][rook2_w_start_col] = new Rook(WHITE);
        gameBoard[rook1_b_start_row][rook1_b_start_col] = new Rook(BLACK);
        gameBoard[rook2_b_start_row][rook2_b_start_col] = new Rook(BLACK);
        
        gameBoard[queen_w_start_row][queen_w_start_col] = new Queen(WHITE);
        gameBoard[queen_b_start_row][queen_b_start_col] = new Queen(BLACK);

        #if GAMEDEBUG
        printBoard(cout, true);
        #endif
    }

    bool squareIsWhite(int r, int c) {
		return false;
    }

    void printBoard(ostream& sout, bool showColor) {
        for(int r = 0; r < height; r++) {
            for(int c = 0; c < width; c++) {
                if(gameBoard[r][c]) {
                    gameBoard[r][c]->print(sout, showColor);
                    if(c != width-1) sout << " ";
                } else {
					if(showColor) {
						sout << "  ";
					} 
					sout << '.';
					if(c != width-1) sout << " ";
				}
            }
            sout << endl;
        }
    }
	
	/*bool placePiece(ChessPiece *piece, int r, int c) {
		
	}
	
	bool removePiece(ChessPiece *piece, int r, int c) {
		
	}*/

    /*bool makeMove(int sourceR, int sourceC, int destR, int destC) {
        if(sourceR < 0 || sourceR >= height || sourceC < 0 || sourceC >= width || destR < 0 || destR >= height || destC < 0 || destC >= width) return false;
        if(!gameBoard[sourceR][sourceC]) return false;

    }*/
};

#endif
