#ifndef PIECE_H
#define PIECE_H


#include <vector>
#include <array>
#include <iostream>
#include "piecemove.h"
#include "square.h"

class Piece{
	protected:
		std::string name;
		char symbol;
		bool color; //0- white, 1 black
		std::array<int,2> originalPos;
		std::array<int, 2> currentPos;
    Square *square;
    std::vector<PieceMove*> moves; // all moves a piece can make, valid moves are handled by the game engine
	public:
		Piece(bool desiredColor, std::array<int,2> pos);
    Piece(bool desiredColor, Square *desiredSquare);
    Piece(Piece *other_piece);
		virtual ~Piece();
		std::string getName() {return name;};
		char getSymbol() {return symbol;};
		bool getColor() {return color;};
		std::array<int,2> getOriginalPos() {return originalPos;};
		std::array<int, 2> getCurrentPos() {return currentPos;};
		void setCurrentPos(std::array<int,2> newPos) {currentPos = newPos;};
    void setSquare(Square *sq) {square = sq;}
    Square* getSquare() {return square;}
    std::vector<PieceMove*> getMoves() {return moves;};
		virtual void f() = 0;

    inline bool operator==(const Piece& p);
    inline bool operator!=(const Piece& p);

		
};

class Pawn : public Piece{
	public:
		Pawn(bool desiredColor, std::array<int,2> pos);		
    Pawn(bool desiredColor, Square *desiredSquare);
		void f() {std::cout << "I'm a pawn!" << std::endl;};
};

class Knight : public Piece{
  public:
    Knight(bool desiredColor, std::array<int,2> pos);
    Knight(bool desiredColor, Square *desiredSquare);
    void f() {std::cout << "I'm  a knight!" << std::endl;}
};

class Rook : public Piece{
  public:
    Rook(bool desiredColor, std::array<int,2> pos);
    Rook(bool desiredColor, Square *desiredSquare);
    void f() {std::cout << "I'm a rook!" << std::endl;}
};

class Bishop : public Piece{
  public:
    Bishop(bool desiredColor, std::array<int,2> pos);
    Bishop(bool desiredColor, Square *desiredSquare);
    void f() {std::cout << "I'm a bishop!" << std::endl;}
};

class Queen: public Piece{
  public:
    Queen(bool desiredColor, std::array<int,2> pos);
    Queen(bool desiredColor, Square *desiredSquare);
    void f() {std::cout << "I'm a Queen!" << std::endl;}
};

class King: public Piece{
  private:
    //true - is in check, false - not in check
    bool check_state;
  public:
    King(bool desiredColor, std::array<int,2> pos);
    King(bool desiredColor, Square *desiredSquare);
    King(King *otherKing);
    bool isInCheck() {return check_state;}
    void setCheckState(bool new_check_state) {check_state = new_check_state;}
    void f() {std::cout << "I'm a King!" << std::endl;}
};
#endif
