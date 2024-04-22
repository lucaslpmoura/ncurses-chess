#include "textrenderer.h"


TextRenderer::TextRenderer(WINDOW* selected_win, Board *selected_board, int selected_sqSize, std::array<int,4> selected_color_pairs){
  win = selected_win;
  board = selected_board;
  blink_cursor = false;
  square_size = selected_sqSize;
  color_pairs = selected_color_pairs;
}

TextRenderer::~TextRenderer(){}

void TextRenderer::drawSquare(int color_pair){
  int y,x;
  getyx(win, y, x);
  attron(COLOR_PAIR(color_pair));
  for (int i =1; i <= square_size-2; i++){
    for(int j = 0; j < square_size ; j++){
      waddch(win, ' '); 
    }
    move(y+i, x);
  }
  attroff(COLOR_PAIR(color_pair));
}

void TextRenderer::drawSquare(Square* sq, int color_pair){
  std::array<int,2> sqPos = sq->getPos();
  move(sqPos[0]*(square_size-2), sqPos[1]*square_size);
  drawSquare(color_pair);
}

void TextRenderer::drawHollowSquare(Square *sq, int color_pair){
  move(sq->getPos()[0]*(square_size-2), sq->getPos()[1]*square_size);
  for(int i = 0; i < square_size - 2; i++){
    for (int j = 0; j < square_size; j++){
      if(
          (i == 0) ||
          (i == square_size - 3) ||
          (j == 0) ||
          (j == (square_size-1))
        ){waddch(win, '*');}
      else{
        int y,x;
        getyx(win, y,x);
        move(y, x+1);
      }
    }
    move(sq->getPos()[0]*(square_size-2) + i + 1, sq->getPos()[1]*square_size);
  }
}

//color_pairs
//1 - white squares
//2 - black squares
void TextRenderer::drawTickInMiddleOfSquare(Square *sq, int color_pair1, int color_pair2){
  //moves to middle of square (mod 2 in case of odd size)
  move((sq->getPos()[0]*(square_size-2) + (square_size-2)%2), (sq->getPos()[1]*square_size + (square_size/2)));
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
void TextRenderer::drawCompassPointsInSquare(Square *sq, int color_pair1, int color_pair2){
  std::array<int,2> middleOfSquare =  {sq->getPos()[0]*(square_size-2) + (square_size-2)%2, sq->getPos()[1]*square_size + (square_size/2)};
  int selected_color_pair;
  if (!sq->getColor()) {selected_color_pair = color_pair1;} 
  else {selected_color_pair = color_pair2;}
  wattron(win, COLOR_PAIR(selected_color_pair));
  // N
  move(middleOfSquare[0] - (square_size-2)%2, middleOfSquare[1]);
  waddch(win, '$');
  // E 
  move(middleOfSquare[0], middleOfSquare[1] + square_size/2);
  waddch(win, '$');
  //S 
  move(middleOfSquare[0] + (square_size-2)%2, middleOfSquare[1]);
  waddch(win, '$');
  //W 
  move(middleOfSquare[0], middleOfSquare[1] - square_size/2);
  waddch(win, '$');

  wattroff(win,COLOR_PAIR(selected_color_pair));
}

void TextRenderer::drawPiece(Piece *piece,int color_pair){
  std::array<int,2> piecePos = piece->getCurrentPos();
  move(piecePos[0]*(square_size-2) + (square_size-2)/2, piecePos[1]*square_size + square_size/2);
  attron(COLOR_PAIR(color_pair));
  waddch(win, piece->getSymbol());
  attroff(COLOR_PAIR(color_pair));
}

void TextRenderer::drawPieceMove(Piece *piece, PieceMove *pieceMove, int color_pair1, int color_pair2){
  std::array<int,2> pieceFuturePos = {piece->getCurrentPos()[0] + pieceMove->getPieceDisplacement()[0],
                                      piece->getCurrentPos()[1] + pieceMove->getPieceDisplacement()[1]};
  Square *sq = board->getSquare(pieceFuturePos);
  if ((pieceMove->getMoveType() == PAWNCAPTURE) ||
      (pieceMove->getMoveType() == KNIGHTCAPTURE) ||
      (pieceMove->getMoveType() == CAPTURE)
     ){drawCompassPointsInSquare(sq, color_pair1, color_pair2);}
  else{
    drawTickInMiddleOfSquare(sq, color_pair1, color_pair2);
  }
}

//color_pairs:
//1 & 2 - white pieces, white & black squares
//3 & 4 - blakc pieces, white & black squares
void TextRenderer::drawPieces(std::vector<Piece*> pieces){ 
  for(Piece *p : pieces){
    if(p != nullptr){
      int selected_color_pair = 1;
      switch (p->getSquare()->getColor()){
        case 0:
          if(p->getColor() == 0){selected_color_pair = color_pairs[0];}
          else{selected_color_pair = color_pairs[2];}
          break;
        case 1:
          if(p->getColor() == 0) {selected_color_pair = color_pairs[1];}
          else{selected_color_pair = color_pairs[3];}
          break;
      } 
      drawPiece(p, selected_color_pair);
    }
  }   
  move(0, 0);
}


void TextRenderer::drawPieceMoves(Piece *piece, std::vector<PieceMove*> pieceMoves){
  if(piece == nullptr) {return;}
  for (PieceMove *move : pieceMoves){
    if (!piece->getColor()){
      drawPieceMove(piece, move, color_pairs[0], color_pairs[1]);
    }else{
      drawPieceMove(piece, move, color_pairs[2], color_pairs[3]);
    }
  } 
}

void TextRenderer::drawBoard(std::vector<Square*> squares){
  int color_pair = 0;
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      drawSquare(squares[i*8 + j], color_pairs[color_pair]);
      if(j!=7){
        color_pair = (color_pair + 1) % 2;
      }
    }
  }
}

//color_pair1 - white squares
//color_pair2 - black squares
void TextRenderer::drawCursor(Cursor cs){
  int selected_color_pair;
  if(cs.getSquare()->getColor() == 0) {selected_color_pair = color_pairs[0];}
  else {selected_color_pair = color_pairs[1];}

  if (blink_cursor) {wattron(win, A_BLINK | COLOR_PAIR(selected_color_pair));}
  else {wattron(win, COLOR_PAIR(selected_color_pair));}
  drawHollowSquare(cs.getSquare(), selected_color_pair);
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


