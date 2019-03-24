#ifndef Entity_H
#define Entity_H
#include <iostream>
#include <string>
#include <utility>
using std::pair;
using std::string;

class Board;

class Entity
{
protected:
    char logo, prevLogo;
    int chamber;
    pair<int,int> location;
    Board& board;
    string race;
public:
    Entity(char symbol, int cr, pair<int,int>& loc, Board& bd, string ra);
    virtual ~Entity();
    void setPrev(char type);
    int getChamber();
    pair<int,int> getLocation();
    void setLocation(pair<int,int> loc);
    char getPrev();
    string getType();
    char getLogo();
    void setChamber(int c);
    Board& getboard();
};

#endif
