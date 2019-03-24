#include "elf.h"
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

Elf::Elf(int chamber, pair<int,int> loc, Board& bd, int m)   
: Enemy('E', chamber, loc, bd, 140, 30, 10, "Elf", m)
{}

void Elf::attack(Hero& hero) 
{
    int damage = ceil((100 / (100 * 1.0 + hero.getDef()) * atk)); 

    for(int i = 1; i <= 2; i++)
    {
        if((i == 2 && (hero.getType() == "Drow")) || hero.isDead()) break;

        stringstream ss;
        bool miss = rand() % 2;
        if(miss)
        {
            ss << " " << logo << "'s attack missed.";
        }
        else
        {
            ss << " " << logo << " deals " << damage << " damage to PC.";
            hero.changeHp(-1 * damage);
            if(hero.isDead())
            {
                ss << " PC has been killed.";
            }
        }
        hero.addinfo(ss.str());
    }
}
