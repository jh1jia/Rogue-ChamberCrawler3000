#include "gold.h"
#include <utility>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Gold::Gold(pair<int,int>& loc, Board& bd, int chamber,int amount)
:Entity('G', chamber, loc, bd, "gold"), sum(amount) 
{
    if(amount == 6)
    {
        hold = true;
    }
    else
    {
        hold = false;
    }
}

int Gold::getGold() 
{ 
    return sum;
}

bool Gold::ishold() 
{
    return hold;
}
void Gold::setfree(bool b) 
{
    hold = b;
}

