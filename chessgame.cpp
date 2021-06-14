#include "chessgame.hpp"

	void ChessGame::initializeBoard_default(void) {
        
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
		whiteKing = gameBoard[king_w_start_row][king_w_start_col];
		blackKing = gameBoard[king_b_start_row][king_b_start_col];
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

		active = true;
        #if GAMEDEBUG
        printBoard(cout, true);
        #endif
    }
	
	void ChessGame::printBoard(ostream& sout, bool showColor) {
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
	
	bool ChessGame::verifyMoveLegality(int sourceR, int sourceC, int destR, int destC) {
		ChessPiece *target = gameBoard[destR][destC];
		ChessPiece *toMove = gameBoard[sourceR][sourceC];
		if((toMove->getColor() == WHITE && !this->whiteToMove) || (toMove->color == BLACK && this->whiteToMove)) return false;
		ChessPiece *optional = nullptr;
		bool kingSafe = noThreats(sourceR, sourceC, toMove);
		if(target == nullptr) {
			
			if(toMove->getType() == 0) {
					//CASTLING CONTINGENCY
				if(destR - sourceR == 0) {
					if(destC - sourceC == 2) {
						optional = gameBoard[sourceR][sourceC+3];
					} else if(destC - sourceC == -2) {
						optional = gameBoard[sourceR][sourceC-4];
					}
					if(optional && !kingSafe) return false;
				}
			} else if(toMove->getType() == 1) {
					//EN PASSANT CONTINGENCY
				
			}
			
			
			bool check = toMove->canMove(sourceR, sourceC, destR, destC, optional);
			if(check) {
				gameBoard[sourceR][sourceC]->performMove
			} else {
				return false;
			}
		} else {
			bool check = toMove->canCapture(sourceR, sourceC, destR, destC, target);
			if(check) {
				
			} else {
				return false;
			}
		}
	}
	
	bool ChessGame::makeMove(int sourceR, int sourceC, int destR, int destC) {
        if(sourceR < 0 || sourceR >= height || sourceC < 0 || sourceC >= width || destR < 0 || destR >= height || destC < 0 || destC >= width) return false;
        if(!gameBoard[sourceR][sourceC]) return false;
		if(verifyMoveLegality(int sourceR, int sourceC, int destR, int destC) {
			//perform the move now that we know its legal
			
		} else {
			cout << "Illegal move. Cannot move from (" << sourceR << "," << sourceC << ") to (" << destR << "," << destC << ")" << endl;
			return false;
		}
    }
	
	bool ChessGame::noThreats(int r, int c, int safe_color) {
		vector<pair<int, int>> knightSquares = getKnightSquares(r, c);
		for(const auto& p: knightSquares) {
			ChessPiece *check = gameboard[get<0>(p), get<1>(p)];
			if(check) {
				if(!check->isAlly(safe_color)) {
					if(check->getType() == 2) return false; //Enemy knight threatening this square
				}
			}
		}
		
		//Check for Pawns (Since they pose a limited threat it seems more efficient to check them separately)
		if(safe_color == WHITE) {
			if(r-1 >= 0) {
				if(c-1 >= 0) {
					ChessPiece *p = gameBoard[r-1][c-1];
					if(p && p->getType() == 1) {
						if(!p->isAlly(WHITE)) return false;
					}
				}
				
				if(c+1 < 8) {
					ChessPiece *p = gameBoard[r-1][c+1];
					if(p && p->getType() == 1) {
						if(!p->isAlly(WHITE)) return false;
					}
				}
			}
		} else {
			if(r+1 < 8) {
				if(c-1 >= 0) {
					ChessPiece *p = gameBoard[r+1][c-1];
					if(p && p->getType() == 1) {
						if(!p->isAlly(BLACK)) return false;
					}
				} 
				
				if(c+1 < 8) {
					ChessPiece *p = gameBoard[r+1][c+1];
					if(p && p->getType() == 1) {
						if(!p->isAlly(BLACK)) return false;
					}
				}
			}
		}
		
		
		
		//Now we need to check 8 directions for immediate threats not prevented by friendly pieces. 
		int traceR = r-1;
		int traceC = c-1;
		bool done = false;
		while(traceR >= 0 && traceC >= 0 && !done) {
			ChessPiece *trace = gameBoard[traceR][traceC];
			if(trace) {
				if(!trace->isAlly(safeColor)) {
					if(trace->getType() == 3) return false;
				} else {
					done = true;
				}
			}
			traceR--;
			traceC--;
		}
		done = false;
		traceR = r-1;
		traceC = c;
		
		while(traceR >= 0 && !done) {
			ChessPiece *trace = gameBoard[traceR][traceC];
			if(trace) {
				if(!trace->isAlly(safeColor)) {
					if(trace->getType() == 4 || trace->getType() == 5) return false;
				} else {
					done = true;
				}
			}
			traceR--;
		}
		done = false;
		traceR = r-1;
		traceC = c+1;
		
		while(traceR >= 0 && traceC < 8 && !done) {
			ChessPiece *trace = gameBoard[traceR][traceC];
			if(trace) {
				if(!trace->isAlly(safeColor)) {
					if(trace->getType() == 3) return false;
				} else {
					done = true;
				}
			}
			traceR--;
			traceC++;
		}
		done = false;
		traceC = c-1;
		traceR = r;
		
		while(traceC >= 0 && !done) {
			ChessPiece *trace = gameBoard[traceR][traceC];
			if(trace) {
				if(!trace->isAlly(safeColor)) {
					if(trace->getType() == 4 || trace->getType == 5) return false;
				} else {
					done = true;
				}
			}
			traceC--;
		}
		done = false;
		traceR = r+1;
		traceC = c-1;
		
		while(traceR < 8 && traceC >= 0 && !done) {
			ChessPiece *trace = gameBoard[traceR][traceC];
			if(trace) {
				if(!trace->isAlly(safeColor)) {
					if(trace->getType() == 3) return false;
				} else {
					done = true;
				}
			}
			traceR++;
			traceC--;
		}
		done = false;
		traceR = r+1;
		traceC = c;
		
		while(traceR < 8 && !done) {
			ChessPiece *trace = gameBoard[traceR][traceC];
			if(trace) {
				if(!trace->isAlly(safeColor)) {
					if(trace->getType() == 4 || trace->getType() == 5) return false;
				} else {
					done = true;
				}
			}
			traceR++;
		}
		done = false;
		traceR = r+1;
		traceC = c+1;
		while(traceR < 8 && traceC < 8 && !done) {
			ChessPiece *trace = gameBoard[traceR][traceC];
			if(trace) {
				if(!trace->isAlly(safeColor)) {
					if(trace->getType() == 3) return false;
				} else {
					done = true;
				}
			}
			traceR++;
			traceC++;
		}
		done = false;
		traceR = r;
		traceC = c+1;
		while(traceC < 8 && !done) {
			ChessPiece *trace = gameBoard[traceR][traceC];
			if(trace) {
				if(!trace->isAlly(safeColor)) {
					if(trace->getType() == 4 || trace->getType() == 5) return false;
				} else {
					done = true;
				}
			}
			traceC++;
		}
		
		return true;
	}
	
	vector<pair<int, int>> ChessGame::getKnightSquares(int r, int c) {
		vector<pair<int,int>> result;
		result.reserve(8);
		
		if(r-2 >= 0) {
			if(c-2 >= 0) {
				result.emplace_back(r-1,c-2);
				result.emplace_back(r-2,c-1);
			} else if(c-1 >= 0) {
				result.emplace_back(r-2, c-1);
			}
			
			if(c+2 < 8) {
				result.emplace_back(r-1,c+2);
				result.emplace_back(r-2,c+1);
			} else if(c+1 < 8) {
				result.emplace_back(r-2,c+1);
			}
		} else if(r-1 >= 0) {
			if(c-2 >= 0) {
				result.emplace_back(r-1,c-2);
			}
			
			if(c+2 < 8) {
				result.emplace_back(r-1,c+2);
			}
		}
		
		if(r+2 < 8) {
			if(c-2 >= 0) {
				result.emplace_back(r+1,c-2);
				result.emplace_back(r+2,c-1);
			} else if(c-1 >= 0) {
				result.emplace_back(r+2,c-1);
			}
			
			if(c+2 < 8) {
				result.emplace_back(r+1,c+2);
				result.emplace_back(r+2,c+1);
			} else if(c+1 < 8) {
				result.emplace_back(r+2,c+1);
			}
		} else if(r+1 < 8) {
			if(c-2 >= 0) {
				result.emplace_back(r+1,c-2);
			} 
			
			if(c+2 < 8) {
				result.emplace_back(r+1,c+2);
			}
		}
		
		return result;
	}