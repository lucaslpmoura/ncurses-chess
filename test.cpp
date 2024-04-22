#include "test.h"

void testPieces(){
  Pawn *p = new Pawn(0, {0,0});
  Knight *n = new Knight(0, {0,1});
  Rook *r = new Rook(0, {0,2});
  Bishop *b = new Bishop(0, {0,3});
  Queen *q = new Queen(0, {0,4});
  King *k = new King(0, {0,5});
  std::vector<Piece*> pieces = {p, n, r, b, q ,k};
  for(Piece *p : pieces){
    std::cout << p->getName() << " generated at " << p->getCurrentPos()[0] << ", " << p->getCurrentPos()[1] << std::endl;
  }
  for (Piece *p : pieces){
    delete(p);
  }
}

void testSquares(){
  Square *sq = new Square(0, {0,0});
  std::cout << "Initialized a square at " << sq->getPos()[0] << ", " << sq->getPos()[1] << std::endl;
  delete(sq);
}
