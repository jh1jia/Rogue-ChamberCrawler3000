#ifndef Goblin_H
#define Goblin_H
#include "hero.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Board;

class Goblin : public Hero
{
 public:
    Goblin(pair<int,int> loc, int chamber, Board& board);
    virtual void attack(Enemy& aim);
};


#endif
