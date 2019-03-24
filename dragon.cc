#include "dragon.h"
#include "gold.h"
#include <utility>
#include <string>
#include <iostream>
using namespace std;

Dragon::Dragon(int chamber, pair<int,int> loc, Board& bd, Gold& g) 
: Enemy('D', chamber, loc, bd, 150, 20, 20, "Dragon", 0), mygold(g)
{}

void Dragon::freeGold()
{
    mygold.setfree(false);
}

pair<int,int> Dragon::getGoldLocation()
{
    return mygold.getLocation();
}
