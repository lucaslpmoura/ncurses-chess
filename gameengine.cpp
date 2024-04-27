#include "gameengine.h"


PieceNames GameEngine::getPieceName(Piece *p){
  std::string name = p->getName();
  if(name == "Pawn") {return PAWN;}
  if(name == "Knight") {return KNIGHT;}
  if(name == "Rook") {return ROOK;}
  if(name == "Bishop"){return BISHOP;}
  if(name == "Queen") {return QUEEN;}
  if(name == "King") {return KING;}
}

bool GameEngine::handleOutOfBounds(Piece *p, PieceMove *pm){
  std::array<int,2> pieceFuturePos = getPieceFuturePos(p, pm);
  if(
      (pieceFuturePos[0] > 7) ||
      (pieceFuturePos[0] < 0) ||
      (pieceFuturePos[1] > 7) ||
      (pieceFuturePos[1] < 0)
      ){return false;}

  return true;
}

//checks to see if there is an other piece in the postion that the piece is trying to move
bool GameEngine::handlePieceInFuturePos(Piece *p, std::array<int,2> pieceFuturePos){
  for (Piece *boardPiece : board->getPieces()){
    if((boardPiece->getCurrentPos() == pieceFuturePos) && !(boardPiece == p)){
      return false;
    }
  }
  return true; 
}


//checks to see if there is an enemy piece in the postion that the piece is trying to move
bool GameEngine::handleEnemyPieceInFuturePos(Piece *p, std::array<int,2> pieceFuturePos){
  for (Piece *boardPiece : board->getPieces()){
    if((boardPiece->getCurrentPos() == pieceFuturePos) && (boardPiece->getColor() == !p->getColor())){
      return false;
    }
  }
  return true;
}

bool GameEngine::handlePieceInFuturePos(Piece *p, PieceMove *pm){
    std::array<int,2> pieceFuturePos = {p->getCurrentPos()[0] + pm->getPieceDisplacement()[0],
                                        p->getCurrentPos()[1] + pm->getPieceDisplacement()[1]};
    return handlePieceInFuturePos(p, pieceFuturePos);
}

bool GameEngine::handleEnemyPieceInFuturePos(Piece *p, PieceMove *pm){
    std::array<int,2> pieceFuturePos = {p->getCurrentPos()[0] + pm->getPieceDisplacement()[0],
                                        p->getCurrentPos()[1] + pm->getPieceDisplacement()[1]};
    return handleEnemyPieceInFuturePos(p, pieceFuturePos);
}




//the approch to this function is finding every square the piece needs to travel
//in order to do its move, than checking every one to see if there is another piece on it
bool GameEngine::handlePieceInTheWay(Piece *p, PieceMove *pm){

    int pieceXPos = p->getCurrentPos()[1];
    int pieceYPos = p->getCurrentPos()[0];

    std::vector<std::array<int,2>> pieceTransientPositions;

    int pmY  = pm->getPieceDisplacement()[0];
    int pmX = pm->getPieceDisplacement()[1];

    switch(abs(pmY) == abs(pmX)){
      case false:

        //left-right movement
        if(pmY == 0){
          if(pmX > 0){
            for(int i = pmX; i > 0; i--){
              pieceTransientPositions.push_back({pieceYPos, pieceXPos+i});
            }
          }else{
            for(int i = pmX; i < 0; i++){
              pieceTransientPositions.push_back({pieceYPos, pieceXPos + i});
            }
          }
        }
        if(pmX == 0){
           if(pmY > 0){
            for(int i = pmY; i > 0; i--){
              pieceTransientPositions.push_back({pieceYPos + i, pieceXPos});
            }
          }else{
            for(int i = pmY; i < 0; i++){
              pieceTransientPositions.push_back({pieceYPos + i, pieceXPos});
            }
          }
        }
        break;
      
      //diagonal movement
      //cases:
      //x > 0, y > 0;
      //x < 0, y > 0;
      //x > 0, y < 0;
      //x < 0, y < 0;
      case true:
        if((pmX > 0) && (pmY > 0)){
          for(int i = pmX; i > 0; i--){
            pieceTransientPositions.push_back({pieceYPos + i, pieceXPos+ i});
          }
        }
        if((pmX < 0) && (pmY > 0)){
          for(int i = pmX; i < 0; i++){
            pieceTransientPositions.push_back({pieceYPos - i, pieceXPos + i});
          }
        }
        if((pmX > 0) && (pmY < 0)){
          for(int i = pmX; i > 0; i--){
            pieceTransientPositions.push_back({pieceYPos - i, pieceXPos + i});
          }
        }
        if((pmX < 0) && (pmY < 0)){  
          for(int i = pmX; i < 0; i++){
            pieceTransientPositions.push_back({pieceYPos + i, pieceXPos+ i});
          }
        }
        break;
    }

    //removes pieceFuturePos from the transientPositions vector so that moves that capture pieces 
    //are only blocked by the first enemy piece that it finds
    pieceTransientPositions.erase(std::remove(pieceTransientPositions.begin(), pieceTransientPositions.end(), getPieceFuturePos(p, pm)), pieceTransientPositions.end());
    
    if(pieceTransientPositions.size() == 0){
      return true;
    }

    for(auto& pTP : pieceTransientPositions){
      if(!handlePieceInFuturePos(p, pTP)){
        return false;
      }
    }
    return true;
}


//this fucntions checks every enemy piece to see if it has an capture movement
//that lands on the same square as the king 
bool GameEngine::handleCheckPosition(King *k, PieceMove *pm){
  for(Piece *p : board->getPieces()){
    //piece cant be a king: would lead to infinte loop
    if((p->getColor() != k->getColor()) && (p->getName() != "King")){
      //for checking the piece movements that would lead to a check position,
      //getValidPieceMoves() cant be used because it only works for current positions of the board
      //a 3 step solution is used in this function

      //1st step: find all moves of piece that are captures
      std::vector<PieceMove*> all_capture_moves;
      for (PieceMove *mv : p->getMoves()){
        if(
          (mv->getMoveType() == CAPTURE) ||
          (mv->getMoveType() == KNIGHTCAPTURE) ||
          (mv->getMoveType() == PAWNCAPTURE)
        ){all_capture_moves.push_back(mv);}
      }

      //2nd step: check if capture moves would meet valid criteria
      std::vector<PieceMove*> valid_capture_moves;
      for (PieceMove *mv : all_capture_moves){
        switch(mv->getMoveType()){
          case KNIGHTCAPTURE:
            if(handleOutOfBounds(p, mv)){
              valid_capture_moves.push_back(mv);
            }
            break;

          //CAPTURE and PAWNCAPTURE
          default:
            if((handleOutOfBounds(p,mv)) && (handlePieceInTheWay(p, mv))){
              valid_capture_moves.push_back(mv);
            }
            break;
        }
      }

      //3rd step: check if move would put king in a position to be checked
      for (PieceMove *mv : valid_capture_moves){
        if(getPieceFuturePos(p,mv) == getPieceFuturePos(k, pm)){
          return false;
        }
      }
    }
  }
  return true;
}


//specfic functions for handling each type of piece valid moves
//done separate for organization propouses
//bishop, rook and queen could one function, but still

std::vector<PieceMove*> GameEngine::getValidPawnMoves(Pawn *p){
  std::vector<PieceMove*> validMoves;
  bool pawn_color = p->getColor();
  for(PieceMove *pm : p->getMoves()){
    switch(pm->getMoveType()){
      case PAWNMOVE:
        if(
            (handleOutOfBounds(p, pm)) &&
            (handlePieceInFuturePos(p, pm))
        ){validMoves.push_back(pm);}
        break;
      case PAWNFIRSTMOVE:
        if(
            (handleOutOfBounds(p,pm)) &&
            (handlePieceInFuturePos(p,pm)) &&
            (handlePieceInTheWay(p,pm)) &&
            (p->getCurrentPos() == p->getOriginalPos())
          ){validMoves.push_back(pm);}
        break;
      case PAWNCAPTURE:
        if(
            (handleOutOfBounds(p,pm)) && 
            (!handleEnemyPieceInFuturePos(p,pm))
          ){validMoves.push_back(pm);}
        break;
      //TODO
      case ENPASSANT:
        break;
      default:
        return {};
    } 
  } 
  return validMoves;
}

std::vector<PieceMove*> GameEngine::getValidKnightMoves(Knight *n){
  std::vector<PieceMove*> validMoves;
  bool knight_color = n->getColor();
  for (PieceMove *pm : n->getMoves()){
    switch(pm->getMoveType()){
      case KNIGHTMOVE:
        if(
            (handleOutOfBounds(n, pm)) &&
            (handlePieceInFuturePos(n, pm))
          ){validMoves.push_back(pm);}
        break;
      case KNIGHTCAPTURE:
        if(
            (handleOutOfBounds(n, pm)) &&
            (!handleEnemyPieceInFuturePos(n, pm))
          ){validMoves.push_back(pm);}
        break;
      default:
        return {};
    }
  }
  return validMoves;
}


std::vector<PieceMove*> GameEngine::getValidRookMoves(Rook *r){
  std::vector<PieceMove*> validMoves;
  bool rook_color = r->getColor();
  for (PieceMove *pm : r->getMoves()){
    switch(pm->getMoveType()){
      case MOVE:
        if(
            (handleOutOfBounds(r, pm)) &&
            (handlePieceInFuturePos(r, pm)) &&
            (handlePieceInTheWay(r, pm))
          ){validMoves.push_back(pm);}
        break;
      case CAPTURE:
        if(
            (handleOutOfBounds(r, pm)) &&
            (handlePieceInTheWay(r,pm)) &&
            (!handleEnemyPieceInFuturePos(r, pm))
          ){validMoves.push_back(pm);}
        break;
      default:
        return {};
    }
  }
  return validMoves;
}



std::vector<PieceMove*> GameEngine::getValidBishopMoves(Bishop *b){
  std::vector<PieceMove*> validMoves;
  bool bishop_color = b->getColor();
  for (PieceMove *pm : b->getMoves()){
    switch(pm->getMoveType()){
      case MOVE:
        if(
            (handleOutOfBounds(b, pm)) &&
            (handlePieceInFuturePos(b, pm)) &&
            (handlePieceInTheWay(b, pm))
          ){validMoves.push_back(pm);}
        break;
      case CAPTURE:
        if(
            (handleOutOfBounds(b, pm)) &&
            (handlePieceInTheWay(b,pm)) &&
            (!handleEnemyPieceInFuturePos(b, pm))
          ){validMoves.push_back(pm);}
        break;
      default:
        return {};
    }
  }
  return validMoves;
}

std::vector<PieceMove*> GameEngine::getValidQueenMoves(Queen *q){
  std::vector<PieceMove*> validMoves;
  bool queen_color = q->getColor();
  for (PieceMove *pm : q->getMoves()){
    switch(pm->getMoveType()){
      case MOVE:
        if(
            (handleOutOfBounds(q, pm)) &&
            (handlePieceInFuturePos(q, pm)) &&
            (handlePieceInTheWay(q, pm))
          ){validMoves.push_back(pm);}
        break;
      case CAPTURE:
        if(
            (handleOutOfBounds(q, pm)) &&
            (handlePieceInTheWay(q,pm)) &&
            (!handleEnemyPieceInFuturePos(q, pm))
          ){validMoves.push_back(pm);}
        break;
      default:
        return {};
    }
  }
  return validMoves;
}

std::vector<PieceMove*> GameEngine::getValidKingMoves(King *k){
  std::vector<PieceMove*> validMoves;
  bool king_color = k->getColor();
  for (PieceMove *pm : k->getMoves()){
    switch(pm->getMoveType()){
      //TODO: Implement king not being able to move to check positions
      case MOVE:
        if(
            (handleOutOfBounds(k, pm)) &&
            (handlePieceInFuturePos(k, pm)) &&
            (handlePieceInTheWay(k, pm)) &&
            (handleCheckPosition(k, pm))
          ){validMoves.push_back(pm);}
        break;
      case CAPTURE:
        if(
            (handleOutOfBounds(k, pm)) &&
            (handlePieceInTheWay(k,pm)) &
            (!handleEnemyPieceInFuturePos(k, pm)) &&
            (handleCheckPosition(k, pm))
          ){validMoves.push_back(pm);}
        break;
      default:
        return {};
    }
  }
  return validMoves;
}

std::array<int,2> GameEngine::getPieceFuturePos(Piece *p, PieceMove *move){
  return {(p->getCurrentPos()[0] + move->getPieceDisplacement()[0]),
          (p->getCurrentPos()[1] + move->getPieceDisplacement()[1])};
}

std::vector<PieceMove*> GameEngine::getValidPieceMoves(Piece *p){
  if(p == nullptr) {return {};}
  switch(getPieceName(p)){
    case PAWN:
      return getValidPawnMoves(dynamic_cast<Pawn*>(p));
    case KNIGHT:
      return getValidKnightMoves(dynamic_cast<Knight*>(p));
    case ROOK:
      return getValidRookMoves(dynamic_cast<Rook*>(p));
    case BISHOP:
      return getValidBishopMoves(dynamic_cast<Bishop*>(p));
    case QUEEN:
      return getValidQueenMoves(dynamic_cast<Queen*>(p));
    case KING:
      return getValidKingMoves(dynamic_cast<King*>(p));
    default:
      return {};
  }
}

void GameEngine::movePiece(Piece *p, PieceMove *move){
  if (
      (move->getMoveType() == PAWNCAPTURE) ||
      (move->getMoveType() == CAPTURE) ||
      (move->getMoveType() == KNIGHTCAPTURE)
     ){
    board->removePiece(board->getPiece(board->getSquare(getPieceFuturePos(p,move))));
  }
  p->setCurrentPos(getPieceFuturePos(p, move));
  p->setSquare(board->getSquare(p->getCurrentPos()));

}

