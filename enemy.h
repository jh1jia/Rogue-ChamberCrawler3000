#ifndef Enemy_H
#define Enemy_H
#include "character.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;

class Hero;

class Enemy : public Character
{
 protected:
    int money;
 public:
    Enemy(char symbol, int cr, pair<int,int>& loc, Board& bd, int hp, int at, int df, string ra, int m);
    virtual void attack(Hero& hero);
    virtual void freeGold();
    virtual pair<int,int> getGoldLocation();
    int getMoney();
    void move();
};

#endif
