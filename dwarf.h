#ifndef Dwarf_H
#define Dwarf_H
#include "enemy.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Board;


class Dwarf : public Enemy 
{
 public:
    Dwarf(int chamber, pair<int,int> loc, Board& bd, int m);
};

#endif
