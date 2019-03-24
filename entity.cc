#include "entity.h"
#include <utility>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

Entity::Entity(char symbol, int cr, pair<int,int>& loc, Board& bd, string ra)
:logo(symbol),prevLogo('.'),chamber(cr),location(loc),board(bd),race(ra)
{}

Board& Entity::getboard()
{
    return board;
}

void Entity::setPrev(char type) 
{
    prevLogo = type;
}

int Entity::getChamber()
{
    return chamber;
}

void Entity::setChamber(int c)
{
    chamber = c;
}

pair<int,int> Entity::getLocation()
{
    return location;
}

void Entity::setLocation(pair<int,int> loc)
{
    location.first = loc.first;
    location.second = loc.second;
}

Entity::~Entity()
{}

char Entity::getLogo()
{
    return logo;
}

char Entity::getPrev()
{
    return prevLogo;
}

string Entity::getType()
{
    return race;
}

