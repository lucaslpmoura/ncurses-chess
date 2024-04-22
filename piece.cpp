#include "piece.h"

Piece::Piece(bool desiredColor, std::array<int, 2> pos){;
  color = desiredColor;
  originalPos = pos;
  currentPos = originalPos;
  square = nullptr;
}

Piece::Piece(bool desiredColor, Square *desiredSquare){
  color = desiredColor;
  originalPos = desiredSquare->getPos();
  currentPos = originalPos;
  square = desiredSquare;
}

Piece::~Piece(){
  //cleaning up moves pointers
  for (auto& mv : moves){
    delete(mv);
  }
}

inline bool Piece::operator==(const Piece& p){
  if(
      (name == p.name) &&
      (currentPos == p.currentPos) 
    ){return true;}
  else{
    return false;
  }
}


Pawn::Pawn(bool desiredColor, std::array<int,2> pos): Piece(desiredColor, pos){
			name = "Pawn";
			symbol = 'p';
      if (desiredColor == true){
        moves = {new PieceMove(PAWNMOVE, {1,0}),
                 new PieceMove(PAWNFIRSTMOVE, {2,0})};

      }else{
        moves = {new PieceMove(PAWNMOVE, {-1,0}),
                 new PieceMove(PAWNFIRSTMOVE, {-2,0}),
                 new PieceMove(PAWNCAPTURE, {-1,-1}),
                 new PieceMove(PAWNCAPTURE, {-1, 1})};
      }
}

Pawn::Pawn(bool desiredColor, Square *desiredSquare) : Piece(desiredColor, desiredSquare){
      name = "Pawn";
      symbol = 'p';
      if (desiredColor == true){
        moves = {new PieceMove(PAWNMOVE, {1,0}),
                 new PieceMove(PAWNFIRSTMOVE, {2,0})};

      }else{
        moves = {new PieceMove(PAWNMOVE, {-1,0}),
                  new PieceMove(PAWNFIRSTMOVE, {-2,0}),
                 new PieceMove(PAWNCAPTURE, {-1,-1}),
                 new PieceMove(PAWNCAPTURE, {-1, 1})};
      }
}

Knight::Knight(bool desiredColor, std::array<int,2> pos) : Piece(desiredColor, pos){
      name = "Knight";
      symbol = 'n';
      moves = {new PieceMove(KNIGHTMOVE, {1, 2}),
               new PieceMove(KNIGHTMOVE, {1, -2}),
               new PieceMove(KNIGHTMOVE, {2, 1}),
               new PieceMove(KNIGHTMOVE, {2, -1}),
               new PieceMove(KNIGHTMOVE, {-1, 2}),
               new PieceMove(KNIGHTMOVE, {-1, -2}),
               new PieceMove(KNIGHTMOVE, {-2, 1}),
               new PieceMove(KNIGHTMOVE, {-2, -1})};
}

Knight::Knight(bool desiredColor, Square *desiredSquare) : Piece(desiredColor, desiredSquare){
      name = "Knight";
      symbol = 'n';
      moves = {new PieceMove(KNIGHTMOVE, {1, 2}),
               new PieceMove(KNIGHTMOVE, {1, -2}),
               new PieceMove(KNIGHTMOVE, {2, 1}),
               new PieceMove(KNIGHTMOVE, {2, -1}),
               new PieceMove(KNIGHTMOVE, {-1, 2}),
               new PieceMove(KNIGHTMOVE, {-1, -2}),
               new PieceMove(KNIGHTMOVE, {-2, 1}),
               new PieceMove(KNIGHTMOVE, {-2, -1})};
}

Rook::Rook(bool desiredColor, std::array<int,2> pos) : Piece(desiredColor, pos){
      name = "Rook";
      symbol = 'r';
      moves = {new PieceMove(MOVE, {1, 0})};
};

Rook::Rook(bool desiredColor, Square *desiredSquare) : Piece(desiredColor, desiredSquare){
      name = "Rook";
      symbol = 'r';
      moves = {new PieceMove(MOVE, {1,0})};
}

Bishop::Bishop(bool desiredColor, std::array<int,2> pos) : Piece(desiredColor, pos){
      name = "Bishop";
      symbol = 'b';
      moves = {new PieceMove(MOVE, {1, 1})};
};

Bishop::Bishop(bool desiredColor, Square *desiredSquare) : Piece(desiredColor, desiredSquare){
      name = "Bishop";
      symbol = 'b';
        moves = {new PieceMove(MOVE, {1,1})};
}

Queen::Queen(bool desiredColor, std::array<int,2> pos) : Piece(desiredColor, pos){
      name = "Queen";
      symbol = 'q';
      moves = {new PieceMove(MOVE, {2, 2})};
};

Queen::Queen(bool desiredColor, Square *desiredSquare) : Piece(desiredColor, desiredSquare){
      name = "Queen";
      symbol = 'q';
      moves = {new PieceMove(MOVE, {2,2})};
}

King::King(bool desiredColor, std::array<int,2> pos) : Piece(desiredColor, pos){
      name = "King";
      symbol = 'k';
      moves = {new PieceMove(MOVE, {0, 2})};
};

King::King(bool desiredColor, Square *desiredSquare) : Piece (desiredColor, desiredSquare){
      name = "King";
      symbol = 'k';
      moves = {new PieceMove(MOVE, {0,2})};
}
