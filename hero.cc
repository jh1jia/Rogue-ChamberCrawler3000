#include "hero.h"
#include "enemy.h"
#include "board.h"
#include "gold.h"
#include "potion.h"
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

Hero::Hero(int cr, pair<int,int>& loc, Board& bd, int hp, int at, int df, string ra)
:Character('@', cr, loc, bd, hp, at, df, ra), gold(0), floorNo(1), enrageM(false), atkBackup(at), defBackup(df), info("Player character has spawned.")
{}

bool Hero::MisEnraged()
{
    return enrageM;
}

void Hero::setEnrageM()
{
    enrageM = true;
}

int Hero::getOriginalAtk()
{
    return atkBackup;
}

int Hero::getOriginalDef()
{
    return defBackup;
}

string Hero::getInfo()
{
    return info;
}

void Hero::addinfo(string str)
{
    info += str;
}

void Hero::changeAtk(int num)
{
    atk += num;
    if(atk < 0) atk = 0;
}

void Hero::changeDef(int num)
{
    def += num;
    if(def < 0) def = 0;
}

void Hero::moveUpdate(string direction, pair<int,int>& site)
{
    if(direction == "no") 
    {
        site.first -= 1;
        info = "PC moves North. ";
        return;
    } 
    if (direction == "so")
    {
        site.first += 1;
        info = "PC moves South. ";
        return;
    } 
    if (direction == "we") 
    {
        site.second -= 1;
        info = "PC moves West. ";
        return;
    }
    if (direction == "ea") 
    {
        site.second += 1;
        info = "PC moves East. ";
        return;
    } 
    if (direction == "nw") 
    {
        site.first -= 1;
        site.second -= 1;
        info = "PC moves NorthWest. ";
        return;
    } 
    if (direction == "ne") 
    {
        site.first -= 1;
        site.second += 1;
        info = "PC moves NorthEast. ";
        return;
    } 
    if (direction == "sw") 
    {
        site.first += 1;
        site.second -= 1;
        info = "PC moves SouthWest. ";
        return;
    }
    if (direction == "se") 
    {
        site.first += 1;
        site.second += 1;
        info = "PC moves SouthEast. ";
        return;
    } 
}


void Hero::action(string direction)
{
    pair<int,int> prev = location;
    pair<int,int> substitute = location;

    moveUpdate(direction,substitute);
    char piece = board.getPiece(substitute);

    if(piece == ' ')
    {
        info = "No Road For Hero!";
        return;
    }
    if(piece == '-' || piece == '|')
    {                                
        info = "You can't walk through wall."; 
        return;
    }
    if(piece == 'O' || piece == 'H' || piece == 'W' || piece == 'E' || piece == 'D' ||
        piece == 'L' || piece == 'M' || piece == 'P') 
    {
        info = "Something is blocking you!";
        return;
    }
    if(piece == '\\')
    {
        floorNo++;
        if(floorNo == 6)
        {
            board.setWin();
            return;
        }
        info += "Time to go down a level! ";
        prevLogo = '.';
        board.clear();

    }
    if(piece == '#')
    {
        setLocation(substitute);
        board.moveMap(prev, location, *this);
        return;
    }
    if(piece == '.')
    {  
        setLocation(substitute);
        if(prevLogo == '+')
        {
            chamber = checkroom(location);
        }
        else if(prevLogo != 'G')
        {
            board.statechange(chamber, prev, true); 
        }
        board.moveMap(prev, location, *this);
        board.statechange(chamber, location, false);
    }
    else if(piece == '+')
    {
        setLocation(substitute);
        if(prevLogo == '.')
        {
            board.statechange(chamber, prev, true);
        }
        board.moveMap(prev, location, *this);
    }
    else if(piece == 'G')
    {
        setLocation(substitute);
        if(prevLogo == '.') 
        {
            board.statechange(chamber, prev, true);  
        }
        Gold* p = board.searchGold(location);

        if(p->ishold())
        {
            info += "G is under Dragon's protection!";
            board.moveMap(prev, location, *this);
        }
        else
        {
            stringstream ss;
            ss << p->getGold();
            gold += p->getGold();
            info = info + "PC find " + ss.str() + " gold.";
            board.moveMap(prev, location, *this);
            setPrev('.'); 
        }        
    }

    board.checkNearby(location);
}


int Hero::checkroom(pair<int,int> loc)
{
    if(loc.first >= 3 && loc.first <= 7)
    {
        if(loc.second <= 29)
        {
            return 0;
        }
        return 3;
    }
    if(loc.first >= 8 && loc.first <= 13)
    {
        if(loc.second <= 50)
        {
            return 2;
        }
        return 3;
    }
    if(loc.second <= 27)
    {
        return 1;
    }
    return 4;
}

int Hero::getGold()
{
    return gold;
}

int Hero::getFloor()
{
    return floorNo;
}


void Hero::usePotion(string direction)
{
    pair<int,int> prev = location;
    pair<int,int> substitute = location;
    moveUpdate(direction, substitute);
    char piece = board.getPiece(substitute);

    if(piece != 'P')
    {
        info = "No any Potion there.";
        return;
    }
    setLocation(substitute);
    if(prevLogo == '.')
    {
        board.statechange(chamber, prev, true);  
    }
    Potion* p = board.searchPotion(location);
    string str = p->getType();
    info = "PC uses " + str + ".";
    p->usedby(*this);  
    board.moveMap(prev, location, *this);
    setPrev('.');
}

void Hero::aiming(string direction)
{
    pair<int,int> substitute = location;
    moveUpdate(direction, substitute);
    char piece = board.getPiece(substitute);

    if(piece != 'O' && piece != 'H' && piece != 'W' && piece != 'E' && piece != 'D' && piece != 'L' && piece != 'M')
    {
        info = "There is no any enemy there.";
        return;
    }
    
    Enemy* aim = board.searchEnemy(substitute);                  
    if(aim == NULL)
    {
        info = "There is no any enemy there.";
        return;
    }
    attack(*aim);
}

void Hero::attack(Enemy& aim) 
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
                cout << gold << endl;
                ss << " PC got " << aim.getMoney() << " gold.";
            }
        }
    }
    info = ss.str();
}
