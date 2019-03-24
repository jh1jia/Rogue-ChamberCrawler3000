#ifndef Orc_H
#define Orc_H
#include "enemy.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Board;

class Orc : public Enemy 
{
 public:
    Orc(int chamber, pair<int,int> loc, Board& bd, int m);
    virtual void attack(Hero& hero);
};

#endif
