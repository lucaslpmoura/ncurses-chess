//Creates an layer on top of the ncurses library, creating methods for rendering text-based chess elements

#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <curses.h>
#include <iostream>
#include <vector>
#include "board.h"
#include "cursor.h"

class TextRenderer{
  private:
    WINDOW* win;


    //used for controling blinking of the cursor
    bool blink_cursor;

    Board *board;
    
    //color pairs used in ncurses rednering
    //0 - white piece, white square
    //1 - white piece, black square
    //2 - black piece, white square
    //3 - black piece, black square
    std::array<int,4> color_pairs;


    //defines the sie of the drawn squares
    int square_size;


    //private methods used for drawing single elementes
    void drawSquare(int color_pair);
    void drawSquare(Square *sq, int color_pair);
    void drawHollowSquare(Square *sq, int color_pair);
    void drawTickInMiddleOfSquare(Square *sq, int color_pair1, int color_pair2);
    void drawCompassPointsInSquare(Square *sq, int color_pair1, int color_pair2);
    void drawPiece(Piece *piece, int color_pair);
    void drawPieceMove(Piece *piece, PieceMove *pieceMove, int color_pair1, int color_pair2);
  public:
    TextRenderer(WINDOW* selected_win, Board *selected_board, int selected_sqSize, std::array<int,4> selected_color_pairs);
    ~TextRenderer();

    //public interface for drawing groups of rendering elements
    void blinkingCursor(bool state){blink_cursor = state;}
    void toggleBlinkingCursor(){blink_cursor = !blink_cursor;}
    void drawPieces(std::vector<Piece*> piece);
    void drawPieceMoves(Piece *piece, std::vector<PieceMove*> pieceMoves);
    void drawBoard(std::vector<Square*> squares);
    void drawCursor(Cursor cs); 

    void helloWorld();

};
#endif
