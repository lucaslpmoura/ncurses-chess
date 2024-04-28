#ifndef PIECEMOVE_H
#define PIECEMOVE_H

#include <vector>
#include <array>

enum moveType{
  //all pieces
  MOVE,
  CAPTURE,

  //pawn
  PAWNMOVE,
  PAWNFIRSTMOVE,
  PAWNCAPTURE,
  PROMOTION,
  ENPASSANT,

  //KNIGHT
  KNIGHTMOVE,
  KNIGHTCAPTURE,

  //king
  SMALLCASTLE,
  BIGCASTLE,
};

class PieceMove{
  private:
    moveType type;
    std::array<int,2> pieceDisplacement;
  public:
    PieceMove(moveType desiredType, std::array<int,2> desiredDisplacement){type = desiredType; pieceDisplacement = desiredDisplacement;};
    ~PieceMove(){};
    moveType getMoveType() const {return type;};
    std::array<int,2> getPieceDisplacement() const {return pieceDisplacement;};
};

#endif
