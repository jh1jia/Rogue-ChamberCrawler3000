#ifndef Human_H
#define Human_H
#include "enemy.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Board;

class Human : public Enemy 
{
 public:
    Human(int chamber, pair<int,int> loc, Board& bd, int m);
};

#endif
