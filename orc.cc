#include "orc.h"
#include "hero.h"
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

Orc::Orc(int chamber, pair<int,int> loc, Board& bd, int m) 
: Enemy('O', chamber, loc, bd, 180, 30, 25, "Orc", m)
{}

void Orc::attack(Hero& hero) 
{
    stringstream ss;
    int damage = ceil((100 / (100 * 1.0 + hero.getDef()) * atk));
    bool miss = rand() % 2;

    if(miss)
    {
        ss << " " << logo << "'s attack missed.";
    }
    else
    {
        if(hero.getType() == "Goblin")
        {
            ss << " " << logo << " deals " << damage << " damage(50% more) to PC.";
            hero.changeHp(-1 * damage * 1.5);
        }
        else
        {
            ss << " " << logo << " deals " << damage << " damage to PC.";
            hero.changeHp(-1 * damage);
        }
        if(hero.isDead())
        {
            ss << " PC has been killed.";
        }
    }
    hero.addinfo(ss.str());
}
