#ifndef Shade_H
#define Shade_H
#include "hero.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Board;

class Shade : public Hero
{
 public:
    Shade(pair<int,int> loc, int chamber, Board& board);
};


#endif
