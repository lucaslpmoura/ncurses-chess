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


bool GameEngine::handlePieceInFuturePos(Piece *p, std::array<int,2> pieceFuturePos){
  for (Piece *boardPiece : board->getPieces()){
    if((boardPiece->getCurrentPos() == pieceFuturePos) && !(boardPiece == p)){
      return false;
    }
  }
  return true; 
}

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

    switch(pmY == pmX){
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
      
      //TODO: diagonal movement
      case true:
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

