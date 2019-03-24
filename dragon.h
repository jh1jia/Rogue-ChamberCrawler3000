#ifndef Dragon_H
#define Dragon_H
#include "enemy.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Gold;

class Dragon : public Enemy
{
private:
    Gold& mygold;
public: 
    Dragon(int chamber, pair<int,int> loc, Board& bd, Gold& g);
    virtual void freeGold();
    virtual pair<int,int> getGoldLocation();
};


#endif
