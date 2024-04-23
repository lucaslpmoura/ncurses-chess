#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "board.h"
#include <cmath>

enum PieceNames{
  PAWN,
  KNIGHT,
  ROOK,
  BISHOP,
  QUEEN,
  KING,
};

class GameEngine{
  private:
    Board *board;
    
    PieceNames getPieceName(Piece *p);

    std::vector<PieceMove*> getValidPawnMoves(Pawn *p);
    std::vector<PieceMove*> getValidKnightMoves(Knight *n);
    std::vector<PieceMove*> getValidRookMoves(Rook *r);
    //these functions return true if there is no piece 
    //interfering the movement, false otherwise
    bool handleOutOfBounds(Piece *p, PieceMove *pm);
    bool handlePieceInFuturePos(Piece *p, std::array<int,2> pieceFuturePos);
    bool handlePieceInFuturePos(Piece *p, PieceMove *pm);
    bool handleEnemyPieceInFuturePos(Piece *p, std::array<int,2> pieceFuturePos);
    bool handleEnemyPieceInFuturePos(Piece *p, PieceMove *pm);
    bool handlePieceInTheWay(Piece *p, PieceMove *pm);
    
  public:
    
    std::vector<std::array<int,2>> toPrint;
    GameEngine(Board *b) {board = b;}
    ~GameEngine() {}
    
    std::vector<PieceMove*> getValidPieceMoves(Piece *p);
    std::array<int,2> getPieceFuturePos(Piece *p, PieceMove *move);
    void movePiece(Piece *p, PieceMove *move);
};

#endif
