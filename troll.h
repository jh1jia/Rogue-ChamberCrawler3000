#ifndef Troll_H
#define Troll_H
#include "hero.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Board;


class Troll : public Hero
{
 public:
    Troll(pair<int,int> loc, int chamber, Board& board);
};

#endif
