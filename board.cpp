#include "board.h"

Board::Board(){
  initializeSquares();
  initializePieces();
}

Board::~Board(){
  cleanup();
}

Piece* Board::getPiece(Square *sq){
  for(Piece *p : allPieces){
    if (p->getSquare() == sq){
      return p;
    }
  }
  return nullptr;
}

void Board::removePiece(Piece *p){
  if (p == nullptr) {return;}
  for (Piece *piece : allPieces){
    if (piece == p){
      allPieces.erase(std::remove(allPieces.begin(), allPieces.end(), piece), allPieces.end());
    }
  }
}

Square* Board::getSquare(Piece *p){
  for(Square *sq : allSquares){
    if(sq->getPos() == p->getCurrentPos()){
      return sq;
    }
  }
  return nullptr;
}

Square* Board::getSquare(std::array<int,2> pos){
  for(Square *sq : allSquares){
    if(sq->getPos() == pos) {return sq;}
  }
  return nullptr;
}

Square* Board::getSquare(int index){
  if((index > 63) || (index < 0)) {return nullptr;}
  else{return allSquares[index];}
}

std::vector<Piece*> Board::getPieces(){
  return allPieces;
}


void Board::initializePieces(){
  for (int i = 48; i < 56; i++){;
    Pawn *p = new Pawn(WHITE, allSquares[i]);
    allPieces.push_back(p);
  }
  for (int i = 8 ; i < 16; i++){
    Pawn *p = new Pawn(BLACK, allSquares[i]);
    allPieces.push_back(p);
  }

  Knight *bn1 = new Knight(BLACK, allSquares[1]);
  Knight *bn2 = new Knight(BLACK, allSquares[6]);
  Knight *wn1 = new Knight(WHITE, allSquares[57]);
  Knight *wn2 = new Knight(WHITE, allSquares[62]);
  allPieces.push_back(wn1);
  allPieces.push_back(wn2);
  allPieces.push_back(bn1);
  allPieces.push_back(bn2);

  Rook *br1 = new Rook(BLACK, allSquares[0]);
  Rook *br2 = new Rook(BLACK, allSquares[7]);
  Rook *wr1 = new Rook(WHITE, allSquares[56]);
  Rook *wr2 = new Rook(WHITE, allSquares[63]);
  allPieces.push_back(wr1);
  allPieces.push_back(wr2);
  allPieces.push_back(br1);
  allPieces.push_back(br2);

  Bishop *bb1 = new Bishop(BLACK, allSquares[2]);
  Bishop *bb2 = new Bishop(BLACK, allSquares[5]);
  Bishop *wb1 = new Bishop(WHITE, allSquares[58]);
  Bishop *wb2 = new Bishop(WHITE, allSquares[61]);
  allPieces.push_back(wb1);
  allPieces.push_back(wb2);
  allPieces.push_back(bb1);
  allPieces.push_back(bb2);

  Queen *bq = new Queen(BLACK, allSquares[3]);
  Queen *wq = new Queen(WHITE, allSquares[59]);
  allPieces.push_back(wq);
  allPieces.push_back(bq);

  King *bk = new King(BLACK, allSquares[4]);
  King *wk = new King(WHITE, allSquares[60]);
  allPieces.push_back(wk);
  allPieces.push_back(bk);
}

void Board::initializeSquares(){
  bool sqColor = WHITE;
  for (int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      Square *sq = new Square(sqColor, {i,j});
      allSquares.push_back(sq);
      if(j != 7){
        sqColor = !sqColor;
      }
    }
  }
  std::cout <<  "Number of squares initialized: " << allSquares.size() << std::endl;
  std::cout << "Comparison test: " << (allSquares[0] == allSquares[1]) << " (false means it's working)" << std::endl;
}

void Board::cleanup(){
  for(Piece *p : allPieces){
    delete(p);
  }
  for(Square *sq : allSquares){
    delete(sq);
  }
}