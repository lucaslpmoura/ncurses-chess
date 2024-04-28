//GameEngine: handles the game system, capturing and moving pieces etc.
//Independent of visual interface.

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
  INVALID_PIECE
};

class GameEngine{
  private:
    Board *board;
    
    PieceNames getPieceName(Piece *p);

    

    //these functions return true if there is no piece 
    //interfering the movement, false otherwise
    bool handleOutOfBounds(Piece *p, PieceMove *pm);
    bool handlePieceInFuturePos(Piece *p, std::array<int,2> pieceFuturePos);
    bool handlePieceInFuturePos(Piece *p, PieceMove *pm);
    bool handleEnemyPieceInFuturePos(Piece *p, std::array<int,2> pieceFuturePos);
    bool handleEnemyPieceInFuturePos(Piece *p, PieceMove *pm);
    bool handlePieceInTheWay(Piece *p, PieceMove *pm);

    //checks if moving the king would put him in a check position
    bool handleCheckPosition(King *k, PieceMove *pm);


    //see implementation for why this functions are necessary
    bool handleMovingOutOfCheckPostion(Piece *p, PieceMove *pm);
    void movePiece(Piece *p, PieceMove *move, Board *b);
    bool isKingInCheck(King *k, Board *b);

    std::vector<PieceMove*> getValidPawnMoves(Pawn *p);
    std::vector<PieceMove*> getValidKnightMoves(Knight *n);
    std::vector<PieceMove*> getValidRookMoves(Rook *r);
    std::vector<PieceMove*> getValidBishopMoves(Bishop *b);
    std::vector<PieceMove*> getValidQueenMoves(Queen *q);
    std::vector<PieceMove*> getValidKingMoves(King *k);



    
  public:
    
    std::vector<std::array<int,2>> toPrint;
    GameEngine(Board *b) {board = b;}
    ~GameEngine() {}
    
    std::vector<PieceMove*> getValidPieceMoves(Piece *p);
    std::array<int,2> getPieceFuturePos(Piece *p, PieceMove *move);
    void movePiece(Piece *p, PieceMove *move);
    bool isKingInCheck(King *k);
    
};

#endif
