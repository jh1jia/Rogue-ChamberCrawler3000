#ifndef Drow_H
#define Drow_H
#include "hero.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Board;

class Drow : public Hero
{
 public:
    Drow(pair<int,int> loc, int chamber, Board& board);
};

#endif
