#include "piece.h"

Piece::Piece(bool desiredColor, std::array<int, 2> pos){;
  color = desiredColor;
  originalPos = pos;
  currentPos = originalPos;
  square = nullptr;
  lastMove = nullptr;
}

Piece::Piece(bool desiredColor, Square *desiredSquare){
  color = desiredColor;
  originalPos = desiredSquare->getPos();
  currentPos = originalPos;
  square = desiredSquare;
  lastMove = nullptr;
}


Piece::~Piece(){
  //cleaning up moves pointers
  if(lastMove != nullptr){
    delete(lastMove);
  }
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

inline bool Piece::operator!=(const Piece& p){
  if(
      (name == p.name) &&
      (currentPos == p.currentPos) 
    ){return false;}
  else{
    return true;
  }
}


Pawn::Pawn(bool desiredColor, std::array<int,2> pos): Piece(desiredColor, pos){
			name = "Pawn";
			symbol = 'p';
      if (desiredColor == true){
        moves = {new PieceMove(PAWNMOVE, {1,0}),
                 new PieceMove(PAWNFIRSTMOVE, {2,0}),
                 new PieceMove(PAWNCAPTURE, {1, -1}),
                 new PieceMove(PAWNCAPTURE, {1, 1})};

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
                 new PieceMove(PAWNFIRSTMOVE, {2,0}),
                 new PieceMove(PAWNCAPTURE, {1, -1}),
                 new PieceMove(PAWNCAPTURE, {1, 1}),
                 new PieceMove(ENPASSANT, {1, 1}),
                 new PieceMove(ENPASSANT, {1, -1})};

      }else{
        moves = {new PieceMove(PAWNMOVE, {-1,0}),
                 new PieceMove(PAWNFIRSTMOVE, {-2,0}),
                 new PieceMove(PAWNCAPTURE, {-1,-1}),
                 new PieceMove(PAWNCAPTURE, {-1, 1}),
                 new PieceMove(ENPASSANT, {-1, 1}),
                 new PieceMove(ENPASSANT, {-1, -1})};
      }
}

Piece* Pawn::clone() const{
  return new Pawn(*this);
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
               new PieceMove(KNIGHTMOVE, {-2, -1}),
               new PieceMove(KNIGHTCAPTURE, {1, 2}),
               new PieceMove(KNIGHTCAPTURE, {1, -2}),
               new PieceMove(KNIGHTCAPTURE, {2, 1}),
               new PieceMove(KNIGHTCAPTURE, {2, -1}),
               new PieceMove(KNIGHTCAPTURE, {-1, 2}),
               new PieceMove(KNIGHTCAPTURE, {-1, -2}),
               new PieceMove(KNIGHTCAPTURE, {-2, 1}),
               new PieceMove(KNIGHTCAPTURE, {-2, -1})};
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
               new PieceMove(KNIGHTMOVE, {-2, -1}),
               new PieceMove(KNIGHTCAPTURE, {1, 2}),
               new PieceMove(KNIGHTCAPTURE, {1, -2}),
               new PieceMove(KNIGHTCAPTURE, {2, 1}),
               new PieceMove(KNIGHTCAPTURE, {2, -1}),
               new PieceMove(KNIGHTCAPTURE, {-1, 2}),
               new PieceMove(KNIGHTCAPTURE, {-1, -2}),
               new PieceMove(KNIGHTCAPTURE, {-2, 1}),
               new PieceMove(KNIGHTCAPTURE, {-2, -1})};
}

Piece* Knight::clone() const{
  return new Knight(*this);
}

Rook::Rook(bool desiredColor, std::array<int,2> pos) : Piece(desiredColor, pos){
      name = "Rook";
      symbol = 'r';
      for (int i = 1; i < 8; i++){
        moves.push_back(new PieceMove(MOVE, {0,i}));
        moves.push_back(new PieceMove(MOVE, {i,0}));
        moves.push_back(new PieceMove(MOVE, {0,-i}));
        moves.push_back(new PieceMove(MOVE, {-i,0}));
        moves.push_back(new PieceMove(CAPTURE, {0,i}));
        moves.push_back(new PieceMove(CAPTURE, {i,0}));
        moves.push_back(new PieceMove(CAPTURE, {0,-i}));
        moves.push_back(new PieceMove(CAPTURE, {-i,0}));
      }
};

Rook::Rook(bool desiredColor, Square *desiredSquare) : Piece(desiredColor, desiredSquare){
      name = "Rook";
      symbol = 'r';
      for (int i = 1; i < 8; i++){
        moves.push_back(new PieceMove(MOVE, {0,i}));
        moves.push_back(new PieceMove(MOVE, {i,0}));
        moves.push_back(new PieceMove(MOVE, {0,-i}));
        moves.push_back(new PieceMove(MOVE, {-i,0}));
        moves.push_back(new PieceMove(CAPTURE, {0,i}));
        moves.push_back(new PieceMove(CAPTURE, {i,0}));
        moves.push_back(new PieceMove(CAPTURE, {0,-i}));
        moves.push_back(new PieceMove(CAPTURE, {-i,0}));
      }
}

Piece* Rook::clone() const{
  return new Rook(*this);
}

Bishop::Bishop(bool desiredColor, std::array<int,2> pos) : Piece(desiredColor, pos){
      name = "Bishop";
      symbol = 'b';
      for (int i = 1; i < 8; i++){
        moves.push_back(new PieceMove(MOVE, {i,i}));
        moves.push_back(new PieceMove(MOVE, {-i,i}));
        moves.push_back(new PieceMove(MOVE, {i,-i}));
        moves.push_back(new PieceMove(MOVE, {-i,-i}));
        moves.push_back(new PieceMove(CAPTURE, {i,i}));
        moves.push_back(new PieceMove(CAPTURE, {-i,i}));
        moves.push_back(new PieceMove(CAPTURE, {i,-i}));
        moves.push_back(new PieceMove(CAPTURE, {-i,-i}));
      }
}

Bishop::Bishop(bool desiredColor, Square *desiredSquare) : Piece(desiredColor, desiredSquare){
      name = "Bishop";
      symbol = 'b';
      for (int i = 1; i < 8; i++){
        moves.push_back(new PieceMove(MOVE, {i,i}));
        moves.push_back(new PieceMove(MOVE, {-i,i}));
        moves.push_back(new PieceMove(MOVE, {i,-i}));
        moves.push_back(new PieceMove(MOVE, {-i,-i}));
        moves.push_back(new PieceMove(CAPTURE, {i,i}));
        moves.push_back(new PieceMove(CAPTURE, {-i,i}));
        moves.push_back(new PieceMove(CAPTURE, {i,-i}));
        moves.push_back(new PieceMove(CAPTURE, {-i,-i}));
      }
}

Piece* Bishop::clone() const{
  return new Bishop(*this);
}

Queen::Queen(bool desiredColor, std::array<int,2> pos) : Piece(desiredColor, pos){
      name = "Queen";
      symbol = 'q';
      for (int i = 1; i < 8; i++){
        moves.push_back(new PieceMove(MOVE, {i,i}));
        moves.push_back(new PieceMove(MOVE, {-i,i}));
        moves.push_back(new PieceMove(MOVE, {i,-i}));
        moves.push_back(new PieceMove(MOVE, {-i,-i}));
        moves.push_back(new PieceMove(CAPTURE, {i,i}));
        moves.push_back(new PieceMove(CAPTURE, {-i,i}));
        moves.push_back(new PieceMove(CAPTURE, {i,-i}));
        moves.push_back(new PieceMove(CAPTURE, {-i,-i}));
        moves.push_back(new PieceMove(MOVE, {0,i}));
        moves.push_back(new PieceMove(MOVE, {i,0}));
        moves.push_back(new PieceMove(MOVE, {0,-i}));
        moves.push_back(new PieceMove(MOVE, {-i,0}));
        moves.push_back(new PieceMove(CAPTURE, {0,i}));
        moves.push_back(new PieceMove(CAPTURE, {i,0}));
        moves.push_back(new PieceMove(CAPTURE, {0,-i}));
        moves.push_back(new PieceMove(CAPTURE, {-i,0}));
      }
}

Queen::Queen(bool desiredColor, Square *desiredSquare) : Piece(desiredColor, desiredSquare){
      name = "Queen";
      symbol = 'q';
      for (int i = 1; i < 8; i++){
        moves.push_back(new PieceMove(MOVE, {i,i}));
        moves.push_back(new PieceMove(MOVE, {-i,i}));
        moves.push_back(new PieceMove(MOVE, {i,-i}));
        moves.push_back(new PieceMove(MOVE, {-i,-i}));
        moves.push_back(new PieceMove(CAPTURE, {i,i}));
        moves.push_back(new PieceMove(CAPTURE, {-i,i}));
        moves.push_back(new PieceMove(CAPTURE, {i,-i}));
        moves.push_back(new PieceMove(CAPTURE, {-i,-i}));
        moves.push_back(new PieceMove(MOVE, {0,i}));
        moves.push_back(new PieceMove(MOVE, {i,0}));
        moves.push_back(new PieceMove(MOVE, {0,-i}));
        moves.push_back(new PieceMove(MOVE, {-i,0}));
        moves.push_back(new PieceMove(CAPTURE, {0,i}));
        moves.push_back(new PieceMove(CAPTURE, {i,0}));
        moves.push_back(new PieceMove(CAPTURE, {0,-i}));
        moves.push_back(new PieceMove(CAPTURE, {-i,0}));
      }
}

Piece* Queen::clone() const{
  return new Queen(*this);
}

King::King(bool desiredColor, std::array<int,2> pos) : Piece(desiredColor, pos){
      name = "King";
      symbol = 'k';
      moves.push_back(new PieceMove(MOVE, {1,1}));
      moves.push_back(new PieceMove(MOVE, {-1,1}));
      moves.push_back(new PieceMove(MOVE, {1,-1}));
      moves.push_back(new PieceMove(MOVE, {-1,-1}));
      moves.push_back(new PieceMove(CAPTURE, {1,1}));
      moves.push_back(new PieceMove(CAPTURE, {-1,1}));
      moves.push_back(new PieceMove(CAPTURE, {1,-1}));
      moves.push_back(new PieceMove(CAPTURE, {-1,-1}));
      moves.push_back(new PieceMove(MOVE, {0,1}));
      moves.push_back(new PieceMove(MOVE, {1,0}));
      moves.push_back(new PieceMove(MOVE, {0,-1}));
      moves.push_back(new PieceMove(MOVE, {-1,0}));
      moves.push_back(new PieceMove(CAPTURE, {0,1}));
      moves.push_back(new PieceMove(CAPTURE, {1,0}));
      moves.push_back(new PieceMove(CAPTURE, {0,-1}));
      moves.push_back(new PieceMove(CAPTURE, {-1,0}));
      moves.push_back(new PieceMove(SMALLCASTLE, {0, 2}));
      moves.push_back(new PieceMove(BIGCASTLE, {0, -2}));
      check_state = false;
};

King::King(bool desiredColor, Square *desiredSquare) : Piece (desiredColor, desiredSquare){
      name = "King";
      symbol = 'k';
      moves.push_back(new PieceMove(MOVE, {1,1}));
      moves.push_back(new PieceMove(MOVE, {-1,1}));
      moves.push_back(new PieceMove(MOVE, {1,-1}));
      moves.push_back(new PieceMove(MOVE, {-1,-1}));
      moves.push_back(new PieceMove(CAPTURE, {1,1}));
      moves.push_back(new PieceMove(CAPTURE, {-1,1}));
      moves.push_back(new PieceMove(CAPTURE, {1,-1}));
      moves.push_back(new PieceMove(CAPTURE, {-1,-1}));
      moves.push_back(new PieceMove(MOVE, {0,1}));
      moves.push_back(new PieceMove(MOVE, {1,0}));
      moves.push_back(new PieceMove(MOVE, {0,-1}));
      moves.push_back(new PieceMove(MOVE, {-1,0}));
      moves.push_back(new PieceMove(CAPTURE, {0,1}));
      moves.push_back(new PieceMove(CAPTURE, {1,0}));
      moves.push_back(new PieceMove(CAPTURE, {0,-1}));
      moves.push_back(new PieceMove(CAPTURE, {-1,0}));
      moves.push_back(new PieceMove(SMALLCASTLE, {0, 2}));
      moves.push_back(new PieceMove(BIGCASTLE, {0, -2}));
      check_state = false;
}

Piece* King::clone() const{
  return new King(*this);
}

