#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

class ChessPiece {
    char name;
    int value;
    ChessPiece(char name, int value) : name(name), value(value) {}
};

class King : public ChessPiece {
    King() : ChessPiece('K', 0) {

    }
};

class Pawn : public ChessPiece {
    Pawn() : ChessPiece('p', 1) {

    }
};

class Knight : public ChessPiece {
    Knight() : ChessPiece('N', 3) {

    }
};

class Bishop : public ChessPiece {
    Bishop() : ChessPiece('B', 3) {

    }
};

class Rook : public ChessPiece {
    Rook() : ChessPiece('R', 5) {

    }
};

class Queen : public ChessPiece {
    Queen() : ChessPiece('Q',9);
};

#endif