#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "defines.h"
#include "square.h"
#include <algorithm>

class Board{
  private:
    std::vector<Piece*> allPieces;
    std::vector<Square*> allSquares;
    void initializePieces();
    void initializeSquares();
    void cleanup();

    King* whiteKing;
    King* blackKing;
  public:
    Board();
    Board(const Board *otherBoard);
    ~Board();
    Piece* getPiece(Square *sq);
    void removePiece(Piece *p);
    Square* getSquare(Piece *p);
    Square* getSquare(std::array<int,2> pos);
    Square* getSquare(int index);

    std::vector<Piece*> getPieces();
    King* getKing(bool color);
    std::vector<Square*> getSquares(){return allSquares;}
};

#endif
