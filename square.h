#ifndef SQUARE_H
#define SQUARE_H

#include <array>

class Square{
  private:
    std::array<int,2> sqPos;
    bool color; //0 white 1 black
  public:
    Square(bool desiredColor, std::array<int,2> desiredPos) {sqPos = desiredPos; color = desiredColor;}
    Square(Square *other_sq){sqPos = other_sq->sqPos; color = other_sq->color;}
    Square* clone() const{return new Square(*this);}
    ~Square(){};
    std::array<int,2> getPos(){return sqPos;}
    bool getColor() {return color;}

    inline bool operator==(const Square& sq){return sqPos == sq.sqPos;}
//    inline bool operator==(const Square* sq){return sqPos == sq->sqPos;}
};


#endif
