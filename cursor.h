#ifndef CURSOR_H
#define CURSOR_H

#include "board.h"

class Cursor{
  private:
    Board* board;
    Piece* selected_piece;
    Square* selected_square;
    std::array<int,2> cursorPos;
    void setSquare() {selected_square = board->getSquare(cursorPos);}
  public:
    Cursor(Board* b){board = b; selected_piece = nullptr; selected_square = nullptr; cursorPos = {3,3};}
    ~Cursor() {};
    void setPiece(Piece *p) {selected_piece = p;}
    void setSquare(Square *sq){selected_square = sq; cursorPos = sq->getPos();}
    Piece* getPiece() {return selected_piece;}
    Square* getSquare() {return selected_square;}

    void moveCursorX(int x) {cursorPos = {cursorPos[0], cursorPos[1] + x}; setSquare();}
    void moveCursorY(int y) {cursorPos = {cursorPos[0] + y, cursorPos[1]}; setSquare();}
    std::array<int,2> getPos() {return cursorPos;}
};

#endif
