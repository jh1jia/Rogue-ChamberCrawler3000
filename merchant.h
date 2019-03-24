#ifndef Merchant_H
#define Merchant_H
#include "enemy.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Board;


class Merchant : public Enemy 
{
 public:
    Merchant(int chamber, pair<int,int> loc, Board& bd, int m);
};

#endif
