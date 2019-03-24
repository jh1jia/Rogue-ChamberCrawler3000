#ifndef Hero_H
#define Hero_H
#include "character.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;
using std::string;

class Enemy;

class Hero : public Character 
{
 protected:
    int gold;
    int floorNo;
    int atkBackup, defBackup;
    string info;
    bool enrageM;
 public:
    Hero(int cr, pair<int,int>& loc, Board& bd, int hp, int at, int df, string ra);
    void changeAtk(int num);
    void changeDef(int num);
    void addinfo(string);
    void action(string direction);
    virtual void attack(Enemy& aim);
    string getInfo();
    void moveUpdate(string, pair<int,int>&);
    int checkroom(pair<int,int> loc);
    void usePotion(string direction);
    void aiming(string direction);
    int getFloor();
    int getGold();
    int getOriginalAtk();
    int getOriginalDef();
    bool MisEnraged();
    void setEnrageM();
};

#endif

