#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

class ChessPiece {
    char name;
    int value;
    int color;
    static constexpr char colorNames[2] = ['w','b'];
    ChessPiece(char name, int value) : name(name), value(value) {}
    void print(ostream& sout, bool showColor) {
        if(showColor)
            sout << colorNames[color] << " " << name;
        else
        {
            sout << name;
        }
    }
};

class King : public ChessPiece {
    bool hasMoved;
    King(int color) : ChessPiece('K', 0, color), hasMoved(false) {

    }
};

class Pawn : public ChessPiece {
    Pawn(int color) : ChessPiece('p', 1, color) {

    }
};

class Knight : public ChessPiece {
    Knight(int color) : ChessPiece('N', 3, color) {

    }
};

class Bishop : public ChessPiece {
    Bishop(int color) : ChessPiece('B', 3, color) {

    }
};

class Rook : public ChessPiece {
    Rook(int color) : ChessPiece('R', 5, color) {

    }
};

class Queen : public ChessPiece {
    Queen(int color) : ChessPiece('Q',9, color) {

    }
};

#endif