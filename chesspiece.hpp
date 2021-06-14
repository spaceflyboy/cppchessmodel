#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include <iostream>
using namespace std;

#define KING 0
#define PAWN 1
#define KNIGHT 2
#define BISHOP 3
#define ROOK 4
#define QUEEN 5

static constexpr char colorNames[2] = {'w','b'};
class ChessPiece {
protected:
    char name;
    int value;
    int color;
	int lastMove;
public:
    ChessPiece(char name, int value, int color) : name(name), value(value), color(color), lastMove(-1) {}
    void print(ostream& sout, bool showColor) {
        if(showColor)
            sout << colorNames[color] << " " << name;
        else
        {
            sout << name;
        }
    }
	void hasMoved(int turnNumber) { lastMove = turnNumber; }
	virtual bool canCapture(int sourceR, int sourceC, int destR, int destC, ChessPiece *target) = 0;
	virtual bool canMove(int sourceR, int sourceC, int destR, int destC, ChessPiece *optional) = 0;
	virtual int getType() = 0;
	friend bool isAlly(ChessPiece *p1, ChessPiece *p2);
	bool isAlly(ChessPiece *potential) { return potential->color == this->color; }
	bool isAlly(int color) { return this->color == color; }
	virtual ~ChessPiece() {} 
	int getColor() { return color; }
};

class King : public ChessPiece {
    bool hasMoved;
public:
    King(int color) : ChessPiece('K', 0, color), hasMoved(false) {}
	~King() {}
	bool canCapture(int sourceR, int sourceC, int destR, int destC, ChessPiece *target) {
		int diffX = destC - sourceC;
		int diffY = destR - sourceR;
		if(diffX == 0 && diffY == 0) return false;
		if(!isAlly(this, target)) {
			if(abs(diffX) <= 1 && abs(diffY) <= 1) {
				return true;
			}	
		}
		return false;
	}
	
	bool canMove(int sourceR, int sourceC, int destR, int destC, ChessPiecePtr *optional) {
		int diffX = destC - sourceC;
		int diffY = destR - sourceR;
		if(diffX == 0 && diffY == 0) return false;
		if(abs(diffX) == 2 && diffY == 0) {
			if(hasMoved) return false;
			//check that middle space(s) empty and won't lead to check
			//also check that Rook can move.
			
		}
		if(abs(diffX) <= 1 && abs(diffY <= 1)) return true;
		return false;
	}
	
	bool hasMoved()  { return hasMoved; }
	int getType() { return KING; }
	
};

class Pawn : public ChessPiece {
public:
    Pawn(int color) : ChessPiece('p', 1, color) {

    }
	
	int getType() { return PAWN; }
};

class Knight : public ChessPiece {
public:
    Knight(int color) : ChessPiece('N', 3, color) {

    }
	
	int getType() { return KNIGHT; }
};

class Bishop : public ChessPiece {
public:
    Bishop(int color) : ChessPiece('B', 3, color) {

    }
	
	int getType() { return BISHOP; }
};

class Rook : public ChessPiece {
	bool hasMoved;
public:
    Rook(int color) : ChessPiece('R', 5, color), hasMoved(false) { }
	
	bool hasMoved() { return hasMoved; }
	int getType() { return ROOK; }
};

class Queen : public ChessPiece {
public:
    Queen(int color) : ChessPiece('Q',9, color) {

    }
	int getType() { return QUEEN; }
};

#endif