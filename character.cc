#include "character.h"
#include <utility>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


Character::Character(char symbol, int cr, pair<int,int>& loc, Board& bd, int hp, int at, int df, string ra)
: Entity(symbol,cr,loc,bd,ra),currentHp(hp),maxHp(hp),atk(at),def(df)
{}

void Character::setAtk(int a)
{
    atk = a;
}

void Character::setDef(int d)
{
    def = d;
}

void Character::changeHp(int num)
{
    currentHp += num;

    if(currentHp > maxHp)
    {
        if(race == "Vampire") maxHp = currentHp;
        else currentHp = maxHp;
    }
    if(currentHp < 0)
    {
        currentHp = 0;
    }
}

int Character::getDef()
{
    return def;
}

int Character::getAtk()
{
    return atk;
}

bool Character::isDead()
{
    return currentHp == 0;
}

int Character::getMaxHp()
{
    return maxHp;
}

int Character::getCurrentHp()
{
    return currentHp;
}


