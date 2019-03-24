#ifndef Gold_H
#define Gold_H
#include "entity.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;
using std::string;

class Board;

class Gold : public Entity
{
private:
    int sum;
    bool hold;
public:
    Gold(pair<int,int>& loc, Board& bd, int chamber,int amount);
    int getGold();
    bool ishold();
    void setfree(bool avail);
};

#endif

