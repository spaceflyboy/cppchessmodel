#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H
#include <iostream>
using namespace std;

static constexpr char colorNames[2] = {'w','b'};
class ChessPiece {
protected:
    char name;
    int value;
    int color;
public:
    ChessPiece(char name, int value, int color) : name(name), value(value), color(color) {}
    void print(ostream& sout, bool showColor) {
        if(showColor)
            sout << colorNames[color] << " " << name;
        else
        {
            sout << name;
        }
    }
	virtual bool canCapture(int diffX, int diffY, ChessPiece *target) = 0;
	virtual bool canMove(int diffX, int diffY) = 0;
	friend bool isAlly(ChessPiece *p1, ChessPiece *p2) {
		return p1->color == p2->color;
	}
	virtual ~ChessPiece() {} 
};

class King : public ChessPiece {
    bool hasMoved;
public:
    King(int color) : ChessPiece('K', 0, color), hasMoved(false) {

    }
	~King() {}
	bool canCapture(int diffX, int diffY, ChessPiece *target) {
		if(diffX == 0 && diffY == 0) return false;
		if(!isAlly(this, target)) {
			if(abs(diffX) <= 1 && abs(diffY) <= 1) {
				return true;
			}	
		}
		return false;
	}
};

class Pawn : public ChessPiece {
public:
    Pawn(int color) : ChessPiece('p', 1, color) {

    }
};

class Knight : public ChessPiece {
public:
    Knight(int color) : ChessPiece('N', 3, color) {

    }
};

class Bishop : public ChessPiece {
public:
    Bishop(int color) : ChessPiece('B', 3, color) {

    }
};

class Rook : public ChessPiece {
public:
    Rook(int color) : ChessPiece('R', 5, color) {

    }
};

class Queen : public ChessPiece {
public:
    Queen(int color) : ChessPiece('Q',9, color) {

    }
};

#endif