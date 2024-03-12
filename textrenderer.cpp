#include "textrenderer.h"


TextRenderer::TextRenderer(WINDOW* selected_win, Board *selected_board){
  win = selected_win;
  board = selected_board;
  blink_cursor = false;
}

TextRenderer::~TextRenderer(){}

void TextRenderer::drawSquare(int size, int color_pair){
  int y,x;
  getyx(win, y, x);
  attron(COLOR_PAIR(color_pair));
  for (int i =1; i <= size-2; i++){
    for(int j = 0; j < size ; j++){
      waddch(win, ' '); 
    }
    move(y+i, x);
  }
  attroff(COLOR_PAIR(color_pair));
}

void TextRenderer::drawSquare(Square* sq, int size, int color_pair){
  std::array<int,2> sqPos = sq->getPos();
  move(sqPos[0]*(size-2), sqPos[1]*size);
  drawSquare(size, color_pair);
}

void TextRenderer::drawHollowSquare(Square *sq, int size, int color_pair){
  move(sq->getPos()[0]*(size-2), sq->getPos()[1]*size);
  for(int i = 0; i < size - 2; i++){
    for (int j = 0; j < size; j++){
      if(
          (i == 0) ||
          (i == size - 3) ||
          (j == 0) ||
          (j == (size-1))
        ){waddch(win, '*');}
      else{
        int y,x;
        getyx(win, y,x);
        move(y, x+1);
      }
    }
    move(sq->getPos()[0]*(size-2) + i + 1, sq->getPos()[1]*size);
  }
}

//color_pairs
//1 - white squares
//2 - black squares
void TextRenderer::drawTickInMiddleOfSquare(Square *sq, int size, int color_pair1, int color_pair2){
  //moves to middle of square (mod 2 in case of odd size)
  move((sq->getPos()[0]*(size-2) + (size-2)%2), (sq->getPos()[1]*size + (size/2)));
  int selected_color_pair;
  if (!sq->getColor()) {selected_color_pair = color_pair1;}
  else {selected_color_pair = color_pair2;}
  wattron(win,COLOR_PAIR(selected_color_pair));
  waddch(win, '*');
  wattroff(win, COLOR_PAIR(selected_color_pair));
}

//draws a tick in all 4 cardinal directions (N -> E -> S -> W)
//colors:
//1 - white sq 
//2 - black sq
void TextRenderer::drawCompassPointsInSquare(Square *sq, int size, int color_pair1, int color_pair2){
  std::array<int,2> middleOfSquare =  {sq->getPos()[0]*(size-2) + (size-2)%2, sq->getPos()[1]*size + (size/2)};
  int selected_color_pair;
  if (!sq->getColor()) {selected_color_pair = color_pair1;} 
  else {selected_color_pair = color_pair2;}
  wattron(win, COLOR_PAIR(selected_color_pair));
  // N
  move(middleOfSquare[0] - (size-2)%2, middleOfSquare[1]);
  waddch(win, '$');
  // E 
  move(middleOfSquare[0], middleOfSquare[1] + size/2);
  waddch(win, '$');
  //S 
  move(middleOfSquare[0] + (size-2)%2, middleOfSquare[1]);
  waddch(win, '$');
  //W 
  move(middleOfSquare[0], middleOfSquare[1] - size/2);
  waddch(win, '$');

  wattroff(win,COLOR_PAIR(selected_color_pair));
}

void TextRenderer::drawPiece(Piece *piece, int size,int color_pair){
  std::array<int,2> piecePos = piece->getCurrentPos();
  move(piecePos[0]*(size-2) + (size-2)/2, piecePos[1]*size + size/2);
  attron(COLOR_PAIR(color_pair));
  waddch(win, piece->getSymbol());
  attroff(COLOR_PAIR(color_pair));
}

void TextRenderer::drawPieceMove(Piece *piece, PieceMove *pieceMove, int size, int color_pair1, int color_pair2){
  std::array<int,2> pieceFuturePos = {piece->getCurrentPos()[0] + pieceMove->getPieceDisplacement()[0],
                                      piece->getCurrentPos()[1] + pieceMove->getPieceDisplacement()[1]};
  Square *sq = board->getSquare(pieceFuturePos);
  if ((pieceMove->getMoveType() == PAWNCAPTURE) ||
      (pieceMove->getMoveType() == KNIGHTCAPTURE) ||
      (pieceMove->getMoveType() == CAPTURE)
     ){drawCompassPointsInSquare(sq, size, color_pair1, color_pair2);}
  else{
    drawTickInMiddleOfSquare(sq, size, color_pair1, color_pair2);
  }
}

//color_pairs:
//1 & 2 - white pieces, white & black squares
//3 & 4 - blakc pieces, white & black squares
void TextRenderer::drawPieces(std::vector<Piece*> pieces, int size, int color_pair1, int color_pair2, int color_pair3, int color_pair4){
  for(Piece *p : pieces){
    int selected_color_pair = 1;
    switch (p->getSquare()->getColor()){
      case 0:
        if(p->getColor() == 0){selected_color_pair = color_pair1;}
        else{selected_color_pair = color_pair3;}
        break;
      case 1:
        if(p->getColor() == 0) {selected_color_pair = color_pair2;}
        else{selected_color_pair = color_pair4;}
        break;
    } 
    drawPiece(p, size, selected_color_pair);
  }   
  move(0, 0);
}


void TextRenderer::drawPieceMoves(Piece *piece, std::vector<PieceMove*> pieceMoves, int size, int color_pair1, int color_pair2, int color_pair3, int color_pair4){
  if(piece == nullptr) {return;}
  int selected_color_pair = 1;
  for (PieceMove *move : pieceMoves){
    if (!piece->getColor()){
      drawPieceMove(piece, move, size, color_pair1, color_pair2);
    }else{
      drawPieceMove(piece, move, size, color_pair3, color_pair4);
    }
  } 
}

void TextRenderer::drawBoard(std::vector<Square*> squares, int sqSize, int color_pair1, int color_pair2){
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      drawSquare(squares[i*8 + j], sqSize, color_pair1);
      if(j!=7){
        int aux = color_pair1;
        color_pair1 = color_pair2;
        color_pair2 = aux;
      }
    }
  }
}

//color_pair1 - white squares
//color_pair2 - black squares
void TextRenderer::drawCursor(Cursor cs, int size, int color_pair1,int color_pair2){
  int selected_color_pair;
  if(cs.getSquare()->getColor() == 0) {selected_color_pair = color_pair1;}
  else {selected_color_pair = color_pair2;}

  if (blink_cursor) {wattron(win, A_BLINK | COLOR_PAIR(selected_color_pair));}
  else {wattron(win, COLOR_PAIR(selected_color_pair));}
  drawHollowSquare(cs.getSquare(), size, selected_color_pair);
  if (blink_cursor) {wattroff(win, A_BLINK | COLOR_PAIR(selected_color_pair));}
  else {wattroff(win, COLOR_PAIR(selected_color_pair));} 
}



void TextRenderer::helloWorld(){
  WINDOW *win = initscr();			
  printw("Hello World !!!");	
  wrefresh(win);			
  wgetch(win);			
  endwin();
}


