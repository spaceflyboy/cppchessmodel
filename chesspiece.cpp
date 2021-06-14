#include "chesspiece.hpp"

friend bool isAlly(ChessPiece *p1, ChessPiece *p2) {
	return p1->color == p2->color;
}