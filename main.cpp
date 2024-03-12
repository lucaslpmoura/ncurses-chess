#include "test.h"
#include "board.h"
#include "textrenderer.h"
#include "defines.h"
#include "cursor.h"
#include "gameengine.h"

int cursor = 1;

int main(){
  //test block
  std::cout << "======TEST BLOCK======" << std::endl;
  testPieces();
  testSquares();
  std::cout << "=======TEST BLOCK=====" << std::endl;

  //intialization block
  Board *board = new Board();
  GameEngine gameEngine(board);

  WINDOW* win = initscr();
  wresize(win,100,100);
  cbreak();
  noecho();
  keypad(win, true);
  curs_set(0);

  start_color();
  init_color(COLOR_BLACK, 127, 111, 95);
  init_pair(1, COLOR_BLUE, COLOR_WHITE);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_WHITE);
  init_pair(4, COLOR_RED, COLOR_BLACK);
  
  init_pair(5, COLOR_WHITE, COLOR_BLUE);

  TextRenderer r(win, board);
  r.blinkingCursor(true);

  Cursor cursor(board);
  cursor.setSquare(board->getSquare({3,3}));

  bool flag = true;
  int ch = 0;
  int totalSize = 50;
  while(flag){
    r.drawBoard(board->getSquares(), SQ_SIZE, 1, 2);
    r.drawPieces(board->getPieces(),SQ_SIZE, 1, 2, 3,4);
    r.drawCursor(cursor, SQ_SIZE, 1, 2);
    r.drawPieceMoves(cursor.getPiece(), gameEngine.getValidPieceMoves(cursor.getPiece()), SQ_SIZE, 1, 2, 3, 4);

    ch = wgetch(win);
    switch(ch){
      case KEY_RIGHT:
        if(cursor.getPos()[1] < 7){
          cursor.moveCursorX(1);
        }
        break;
      case KEY_LEFT:
        if(cursor.getPos()[1] > 0){
          cursor.moveCursorX(-1);
        }
        break;
      case KEY_UP:
        if(cursor.getPos()[0] > 0) {
          cursor.moveCursorY(-1);
        }
        break;
      case KEY_DOWN:
        if(cursor.getPos()[0] < 7) {
          cursor.moveCursorY(1);
        }
        break;
      //RETURN key
      case 10: {
        //toggleBlinkingCursor needs to be called if:
        //1 - cursor has not piece selected and selects one;
        //2 - cursor has a piece selected and selects the same one again;
        Piece *p = board->getPiece(cursor.getSquare());

        //no piece selected
        if (cursor.getPiece() == nullptr){
          if(p != nullptr){
            cursor.setPiece(p);
            r.toggleBlinkingCursor();
          }

        //piece selected
        }else{
          if(p == cursor.getPiece()) {
            cursor.setPiece(nullptr);
            r.toggleBlinkingCursor();
          }
          //if the cursor position matches an valid move for its selected piece, 
          //it moves the piece.
          for (PieceMove *move : gameEngine.getValidPieceMoves(cursor.getPiece())){
            if (cursor.getPos() == gameEngine.getPieceFuturePos(cursor.getPiece(), move)){
              gameEngine.movePiece(cursor.getPiece(), move);
              cursor.setPiece(nullptr);
              r.toggleBlinkingCursor();
              break;
            }
          }
        }

        break;
      }


      
      case KEY_F(1):
        flag = false;
        break;
    }
    wrefresh(win);
  }
  std::cout<<"Reached end of window." << std::endl;
  wrefresh(win);
  endwin(); 
  std::cout << totalSize << std::endl;
  std::cout << gameEngine.toPrint.size() << "b" << std::endl;
  for (auto& p : gameEngine.toPrint){
    std::cout << p[0] << ", " << p[1] << std::endl;
  }
  
  return 0;
}





