#include "potion.h"
#include "hero.h"
#include "board.h"
#include <utility>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Potion::Potion(pair<int,int>& loc, Board& bd, string type, int chamber)
:Entity('P', chamber, loc, bd, type), used(false)
{
    if(type == "RH" || type == "PH")
    {
        if(type == "RH") value = 10;
        else value = -10;
    }
    else if(type == "BA" || type == "BD")
    {
        value = 5;
    }
    else if(type == "WA" || type == "WD")
    {
        value = -5;
    }
}

void Potion::usedby(Hero& hero) 
{
    int temp = value;
    if(hero.getType() == "Drow") temp *= 1.5;

    if(race == "RH" || race == "PH")
        hero.changeHp(temp);
    else if(race == "BA" || race == "WA")
        hero.changeAtk(temp);
    else if(race == "BD" || race == "WD")
        hero.changeDef(temp);

    if(!(board.isVisible(race)))
    {
        board.setVisible(race);
    }

    used = true;
}

void Potion::setUsed()
{
    used = true;
}

bool Potion::isUsed()
{
    return used;
}

