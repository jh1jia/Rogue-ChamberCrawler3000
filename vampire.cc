#include "vampire.h"
#include "enemy.h"
#include "board.h"
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

Vampire::Vampire(pair<int,int> loc, int chamber, Board& bd) 
: Hero(chamber, loc, bd, 50, 25, 25, "Vampire")
{}

void Vampire::attack(Enemy& aim) 
{
    stringstream ss;
    int damage = ceil((100 / (100 * 1.0 + aim.getDef())) * atk);
    int miss = 0;

    if(aim.getType() == "Halfling") miss = rand() % 2;
    if((aim.getType() == "Merchant") && !(MisEnraged())) setEnrageM();

    if(miss)
    {
        ss << " " << logo << "'s attack missed.";
    }
    else
    { 
        ss << "PC deals " << damage << " damage to " << aim.getLogo()
        << "(" << aim.getCurrentHp() << " HP).";
        aim.changeHp(-1 * damage);

        int add;
        if(aim.getType() == "Dwarf")
        {
            add = -5;
            ss << " PC lose 5 HP.";
        }
        else
        {
            add = 5;
            ss << " PC gains 5 HP.";
        }
        changeHp(add);

        if(aim.isDead())
        {
            ss << " You beated " << aim.getLogo() << ".";
            board.modifymap(aim.getLocation(), '.');
            board.statechange(aim.getChamber(), aim.getLocation(), true);
            if(aim.getType() == "Dragon")
            {
                aim.freeGold();
            }
            else if(aim.getType() == "Human" || aim.getType() == "Merchant")
            {
                board.newGold(aim.getLocation(), aim.getChamber(), 4);
                ss << " " << aim.getType() << " dropped 4 gold.";
            }
            else // other enemy
            {
                gold += aim.getMoney();
                ss << " PC got " << aim.getMoney() << " gold.";
            }
        }
        if(isDead())
        {
            ss << " PC is dead.";                          
        }
    }
    info = ss.str();
}
