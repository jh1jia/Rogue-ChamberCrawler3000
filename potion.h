#ifndef Potion_H
#define Potion_H
#include "entity.h"
#include <iostream>
#include <string>
#include <utility>
using std::pair;
using std::string;

class Hero;

class Potion : public Entity
{
private:
    int value;
    bool used;
 public:
    Potion(pair<int,int>& loc, Board& bd, string type, int chamber);
    void usedby(Hero& hero); 
    bool isUsed();
    void setUsed();
};


#endif

