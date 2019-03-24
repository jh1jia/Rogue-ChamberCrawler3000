#ifndef Vampire_H
#define Vampire_H
#include "hero.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Enemy;

class Vampire : public Hero
{
 public:
    Vampire(pair<int,int> loc, int chamber, Board& board);
    virtual void attack(Enemy& aim);
};

#endif
