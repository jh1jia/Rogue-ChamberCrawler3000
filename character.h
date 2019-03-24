#ifndef Character_H
#define Character_H
#include "entity.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;
using std::string;

class Board;

class Character : public Entity
{
 protected:
    int currentHp, maxHp, atk, def;
 public:
    Character(char symbol, int cr, pair<int,int>& loc, Board& bd, int hp, int at, int df, string ra);
    void changeHp(int num);
    int getDef();
    int getAtk();
    bool isDead();
    int getMaxHp();
    int getCurrentHp();
    void setAtk(int a);
    void setDef(int d);
};

#endif

