#ifndef Halfling_H
#define Halfling_H
#include "enemy.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Board;


class Halfling : public Enemy 
{
 public:
    Halfling(int chamber, pair<int,int> loc, Board& bd, int m);
};

#endif
