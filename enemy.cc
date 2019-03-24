#include "enemy.h"
#include "hero.h"
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

Enemy::Enemy(char symbol, int cr, pair<int,int>& loc, Board& bd, int hp, int at, int df, string ra, int m)
:Character(symbol, cr, loc, bd, hp, at, df, ra), money(m)
{}

void Enemy::freeGold()
{}

int Enemy::getMoney()
{
    return money;
}

pair<int,int> Enemy::getGoldLocation()
{
    pair<int,int> noUse;
    cerr << "using wrong virtual function" << endl;
    return noUse;
}

void Enemy::attack(Hero& hero)
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
        ss << " " << logo << " deals " << damage << " damage to PC.";
        hero.changeHp(-1 * damage);
        if(hero.isDead())
        {
            ss << " PC has been killed.";
        }
    }
    hero.addinfo(ss.str());
}

void Enemy::move()
{
    board.statechange(chamber, location, true);
    pair<int,int> backup = location;
    board.select(chamber, location);              
    board.statechange(chamber, location, false);
    board.moveMap(backup, location, *this); 
}

