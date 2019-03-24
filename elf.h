#ifndef Elf_H
#define Elf_H
#include "enemy.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Board;

class Elf : public Enemy 
{
 public:
    Elf(int chamber, pair<int,int> loc, Board& bd, int m);
    virtual void attack(Hero& hero);
};

#endif
