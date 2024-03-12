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

    bool blink_cursor;

    Board *board;

    void drawSquare(int size, int color_pair);
    void drawSquare(Square *sq, int size, int color_pair);
    void drawHollowSquare(Square *sq, int size, int color_pair);
    void drawTickInMiddleOfSquare(Square *sq, int size, int color_pair1, int color_pair2);
    void drawPiece(Piece *piece, int size, int color_pair);
    void drawPieceMove(Piece *piece, PieceMove *pieceMove, int size, int color_pair1, int color_pair2);
  public:
    TextRenderer(WINDOW* selected_win, Board *selected_board);
    ~TextRenderer();
    void blinkingCursor(bool state){blink_cursor = state;}
    void toggleBlinkingCursor(){blink_cursor = !blink_cursor;}
    void drawPieces(std::vector<Piece*> pieces,  int size, int color_pair1, int color_pair2, int color_pair3, int color_pair4);
    void drawPieceMoves(Piece *piece, std::vector<PieceMove*> pieceMoves, int size, int color_pair1, int color_pair2, int color_pair3, int color_pair4);
    void drawBoard(std::vector<Square*> squares, int size, int color_pair1, int color_pair2);
    void drawCursor(Cursor cs, int size, int color_pair1, int color_pair2);

    void helloWorld();

    void drawCompassPointsInSquare(Square *sq, int size, int color_pair1, int color_pair2);
};
#endif
