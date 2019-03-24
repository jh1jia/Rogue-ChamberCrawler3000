#include "board.h"
#include "hero.h"
#include "potion.h"
#include "gold.h"
#include "chamber.h"
#include "halfling.h"
#include "human.h"
#include "merchant.h"
#include "orc.h"
#include "elf.h"
#include "dwarf.h"
#include "dragon.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "drow.h"
#include "shade.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Enemy;
class Character;
class Entity;

bool Board::isVisible(string str)
{
    vector<string>::iterator p = Pcontainer.begin();
    for(; p != Pcontainer.end(); p++)
    {
        if(*p == str)
        {
            return true;
        }
    }
    return false;
}

void Board::setVisible(string str)
{
    Pcontainer.push_back(str);
}

int Board::getScore()
{
    return hero->getGold();
}

Board::~Board()
{
    for(vector<Chamber*>::iterator p = chambers.begin(); p != chambers.end(); p++) delete *p;
    for(vector<Enemy*>::iterator p = enemies.begin(); p != enemies.end(); p++) delete *p;
    for(vector<Potion*>::iterator p = potions.begin(); p != potions.end(); p++) delete *p;
    for(vector<Gold*>::iterator p = bank.begin(); p != bank.end(); p++) delete *p;
    delete hero;
}

void Board::clear() 
{
    ifstream in(file.c_str());
    if(in.fail())
     {
        cerr << "fail";
    }
    string rowstr;

    map.clear();

    for(vector<Chamber*>::iterator p = chambers.begin(); p != chambers.end(); p++) delete *p;
    for(vector<Enemy*>::iterator p = enemies.begin(); p != enemies.end(); p++) delete *p;
    for(vector<Potion*>::iterator p = potions.begin(); p != potions.end(); p++) delete *p;
    for(vector<Gold*>::iterator p = bank.begin(); p != bank.end(); p++) delete *p;

    chambers.clear();
    enemies.clear();
    potions.clear();
    bank.clear();

    for(int i = 0; i < 5; i++)
    {
        Chamber* p = new Chamber(i, *this);
        chambers.push_back(p); 
    }

    if(file == "defaultFloor.txt")
    {
      while(getline(in, rowstr))
        {
            map.push_back(rowstr);
        }
        in.close();

     makePotions();    
     makeGold();    
     makeEnemies();


    int num = rand() % 5;
    pair<int,int> loc = chambers[num]->makeLocation();
    chambers[num]->setflag(loc, false);
    hero->setLocation(loc);
    hero->setChamber(num);
    modifymap(loc, '@');
    hero->setAtk(hero->getOriginalAtk());
    hero->setDef(hero->getOriginalDef());

    makeFloor();
    }
    else
    {
        Template();
        if(gameover) return;
    }

}

char Board::getPiece(pair<int,int> loc)
{
    return map[loc.first][loc.second];
}

void Board::setWin()
{
    win = true;
}

void Board::checkNearby(pair<int,int> loc)
{
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if(i == 0 && j ==0) continue;
            pair<int,int> temp;
            temp.first = loc.first + i;
            temp.second = loc.second + j;

            Potion* p = searchPotion(temp);
            if(p != NULL && !(p->isUsed()))
            {
                string name;
                if(isVisible(p->getType()))
                {
                    name = p->getType();
                }
                else
                {
                    name = "unknown";
                }
                name = " PC sees an " + name + " potion.";
                hero->addinfo(name); 
            }
        }
    }
}

void Board::findHero(Enemy& foe)
{
    string Erace = foe.getType();

    pair<int,int> site = foe.getLocation();

    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if(i == 0 && j ==0) continue;
            pair<int,int> temp;
            temp.first = site.first + i;
            temp.second = site.second + j;                 
            if(temp == hero->getLocation() && ((Erace == "Merchant" && hero->MisEnraged()) || Erace != "Merchant")) 
            {
                foe.attack(*hero);
                return;
            }
        }
    }

    if(foe.getType() == "Dragon")
    {
        pair<int,int> Gloc = foe.getGoldLocation();

        for(int i = -1; i < 2; i++)
        {
            for(int j = -1; j < 2; j++)
            {
                if(i == 0 && j ==0) continue;
                pair<int,int> temp;
                temp.first = Gloc.first + i;
                temp.second = Gloc.second + j;              
                if(temp == hero->getLocation())
                {
                    foe.attack(*hero);
                    return;
                }
            }
        }
    }
    else 
    {
        foe.move();
    }
}

bool Board::checkCommand(string str)
{
    return (str == "no" || str == "so" || str == "ea" || str == "we" || str == "ne" || str == "nw" ||
        str == "sw" || str == "se");
}

void Board::play(string command) 
{
    bool valid = false;

    if(command == "q")
    {
        cout << "You are out of the game." << endl;
        gameover = true;
        return;
    }
    else if(command == "r")
    {
        cout << "Restarts the game." << endl;
        retry = true;
        gameover = true;
        return;
    }
    else if(command.at(0) == 'u')  
    {
        valid = checkCommand(command.erase(0,1));
        if(valid) hero->usePotion(command);
    }
    else if(command.at(0) == 'a')
    {
        valid = checkCommand(command.erase(0,1));
        if(valid) hero->aiming(command);
    }
    else
    {
        valid = checkCommand(command);

        if(valid) 
        {
            hero->action(command);
            if(win)
            {
                gameover = true;
                return;
            }
        }
    }

    if(valid)
    {
        for(vector<Enemy*>::iterator p = enemies.begin(); p != enemies.end(); p++)
        {
            if(hero->isDead()) break;

            if(!(*p)->isDead()) 
            {
               findHero(*(*p));
            }
         }

         if((!(hero->isDead())) && (hero->getType() == "Troll"))
         {
            if(hero->getCurrentHp() != hero->getMaxHp())
            {
                hero->changeHp(5);
                hero->addinfo(" PC regained 5 HP.");
            }
        }

        printBoard();

        if(hero->isDead())
        {
            gameover = true;

            int Score = hero->getGold();
            if(hero->getType() == "Shade") Score *= 2;

            cout << "Sorry, you have lost, but it was a good try." << endl;
            cout << "Final Score: " << Score << endl;
            cout << "Do you want revenge? (y/n): ";

            string ch;
            while(cin >> ch)
            {
            if(ch == "y")
            {
                cout << "Go for it!" << endl;
                retry = true;
                return;
            }
            if(ch == "n")
            {
                cout << "See you next time. Bye!" << endl;
                return;
            }
            cout << "Invalid command. Please enter y or n: "; 
            }
        }
    }
    else
    {
        cout << "Invalid command. Please try again: ";
    }
}

bool Board::again()
{
    return retry;
}

void Board::setRetry(bool b)
{
    retry = b;
}

Potion* Board::searchPotion(pair<int,int> loc)
{
    for(vector<Potion*>::iterator p = potions.begin(); p != potions.end(); p++)
    {
        if((*p)->getLocation() == loc)
        {
            return *p;
        }
    }
    return NULL;
}

Enemy* Board::searchEnemy(pair<int,int> loc)
{
    for(vector<Enemy*>::iterator p = enemies.begin(); p != enemies.end(); p++)
    {
        if((*p)->getLocation() == loc)
        {
            return *p;
        }
    }
    return NULL;
}

Gold* Board::searchGold(pair<int,int> loc)
{
    for(vector<Gold*>::iterator p = bank.begin(); p != bank.end(); p++)
    {
        if((*p)->getLocation() == loc)
        {
            return *p;
        }
    }
    return NULL;
}

void Board::moveMap(pair<int,int> prev, pair<int,int> post, Entity& c) 
{
    modifymap(prev, c.getPrev());
    c.setPrev(map[post.first][post.second]);
    modifymap(post, c.getLogo());
}

void Board::modifymap(const pair<int,int>& loc, char change)
{
    string newstr(1,change);
    map[loc.first].replace(loc.second, 1, newstr);
}

bool Board::isover()
{
    return gameover;
}

bool Board::iswin()
{
    return win;
}

void Board::makeEnemies() 
{
    cout << "make" << endl;
    for(int i=0; i<20; i++) 
    {
        Enemy* p = NULL;
        int chamber = rand() % 5;
        pair<int,int> location = chambers[chamber]->makeLocation();
        statechange(chamber, location, false);

        int account = rand() % 2 + 1;
        int type = rand() % 18;
        
        if(type < 2)
        {
            p = new Merchant(chamber, location, *this, 4);
        }
        else if(type < 4)
        {
            p = new Orc(chamber, location, *this, account);
        }
        else if(type < 6)
        {
            p = new Elf(chamber, location, *this, account);
        }
        else if(type < 9)
        {
            p = new Dwarf(chamber, location, *this, account);
        }
        else if(type < 13)
        {
            p = new Human(chamber, location, *this, 4);
        }
        else
        {
            p = new Halfling(chamber, location, *this, account); 
        }
        enemies.push_back(p);
        modifymap(location, p->getLogo());
    }
}

void Board::makePlayer(pair<int,int> l = pair<int,int>(-1,-1), int ch = -1)
{
    string race;
    int num;
    pair<int,int> location;

    if(ch == -1)
    {
        num = rand() % 5;
        location = chambers[num]->makeLocation(); 
    }
    else
    {
        location = l;
        num = ch;
    }
    chambers[num]->setflag(location, false); 

    cout << "Welcome to CC3K!" << endl;
    cout << "Available Heros:" << endl;
    cout << "[d] Drow:    HP:150, Atk:25, Def:15. Effect of Potions magnified by 1.5" << endl;
    cout << "[s] Shade:   HP:125, Atk:25, Def:25. Has a 50% increase to the final score" << endl;
    cout << "[v] Vampire: HP:50,  Atk:25, Def:25. Gains 5 HP per successful attack and no maximum HP" << endl;
    cout << "[t] Troll:   Hp:120, Atk:25, Def:15. Regains 5 HP every turn, maxHp:120" << endl;
    cout << "[g] Goblin:  Hp:110, Atk:15, Def:20. Steals 5 gold from every slain enemy" << endl;
    cout << "What's your choice: ";

    while(cin >> race)
    {
        if(race == "q")
        {
            cout << "You are out of the game." << endl;
            gameover = true;
            return;
        }
        if(race == "r")
        {
            cout << "Restarts the game." << endl;
            retry = true;
            gameover = true;
            return;
        }
        if(race == "v")
        {
            hero = new Vampire(location, num, *this); break;
        }
        if(race == "g")
        {
            hero = new Goblin(location, num, *this); break;
        }
        if(race == "t")
        {
            hero = new Troll(location, num, *this); break;
        }
        if(race == "d")
        {
            hero = new Drow(location, num, *this); break;
        }
        if(race == "s")
        {
            hero = new Shade(location, num, *this); break; 
        }
        cout << "User's choice was invalid, please try again: ";
    }
   modifymap(location, hero->getLogo());
}


void Board::makeFloor()
{
    int select;
    int playersite = hero->getChamber();
    do{
        select = rand() % 5;
    }while(select == playersite);

    chambers[select]->makeStair();
}

void Board::printBoard() 
{
    for(int i = 0; i < 25; i++)
    {
        cout << map[i] << endl;
    }

    cout << "Race: " << hero->getType() << ". ";
    cout << "Gold: " << hero->getGold() << endl;
    cout << "HP: " << hero->getCurrentHp() << endl;
    cout << "Atk: " << hero->getAtk() << endl;
    cout << "Def: " << hero->getDef() << endl;
    cout << "Action: " << hero->getInfo() << endl;
}

void Board::statechange(int ch, pair<int,int> loc, bool flag) 
{
    chambers[ch]->setflag(loc, flag);
}

void Board::makePotions()
{
    for(int i=0; i<10; i++) 
    {
        int chamber = rand() % 5;
        pair<int,int> location = chambers[chamber]->makeLocation();
        modifymap(location, 'P');
        statechange(chamber, location, false);
        
        int type = rand() % 6;
        if(type == 0)
        {
            Potion* p = new Potion(location, *this, "WA", chamber);
            potions.push_back(p);
            continue;
        }
        if(type == 1)
        {
            Potion* p = new Potion(location, *this, "BA", chamber);
            potions.push_back(p);
            continue;
        }
        if(type == 2)
        {
            Potion* p = new Potion(location, *this, "RH", chamber);
            potions.push_back(p);
            continue;
        }
        if(type == 3)
        {
            Potion* p = new Potion(location, *this, "PH", chamber);
            potions.push_back(p);
            continue;
        }
        if(type == 4)
        {
            Potion* p = new Potion(location, *this, "BD", chamber);
            potions.push_back(p);
            continue;
        }
        if(type == 5)
        {
            Potion* p = new Potion(location, *this, "WD", chamber);
            potions.push_back(p);
            continue;
        }
    }
}

void Board::makeGold() 
 {
    for(int i = 0; i < 10; i++) 
    {
        int type = rand() % 8;
        int chamber = rand() % 5;

        pair<int,int> location = chambers[chamber]->makeLocation();
        modifymap(location, 'G');
        chambers[chamber]->setflag(location, false);

        if(type == 0) // dragon hoard
        {
            Gold* g = new Gold(location, *this, chamber, 6);
            bank.push_back(g);
            pair<int, int> Gloc = location;
            chambers[chamber]->aroundSelect(Gloc);
            modifymap(Gloc, 'D');
            statechange(chamber, Gloc, false);
            Enemy* e = new Dragon(chamber, Gloc, *this, *g);
            enemies.push_back(e);
            continue;
        }

        if(type < 3) // small pile
        {
            Gold* g = new Gold(location, *this, chamber, 1);
            bank.push_back(g); 
            continue;
        }

        Gold* g = new Gold(location, *this, chamber, 2); // normal pile
        bank.push_back(g);
    }
}

void Board::select(int ch, pair<int,int>& loc)
{
    chambers[ch]->aroundSelect(loc);
}

void Board::newGold(pair<int,int> loc, int cr, int account)
{
    Gold* g = new Gold(loc, *this, cr, account);
    bank.push_back(g); 
    modifymap(loc, 'G');
    (chambers[cr])->setflag(loc, false);
}

string Board::getHeroType()
{
    return hero->getType();
}

Board::Board(string f)
{
    gameover = false;
    retry = false;
    win = false;
    file = f;
    startLine = 0;

    for(int i = 0; i < 5; i++)
    {
        Chamber* p = new Chamber(i, *this);
        chambers.push_back(p);  
    }

    if(file == "defaultFloor.txt")
    {
        string rowstr;
        ifstream in(f.c_str());
        if(in.fail())
        {
            cerr << "fail";
        }

        while(getline(in, rowstr))
        {
            map.push_back(rowstr);
        }
        in.close();

        makePlayer();
        if(gameover)
        {
            return;
        }
        makeFloor();
        makePotions(); 
        makeGold(); 
        makeEnemies();
    }
    else
    {
        Template();
        if(gameover) return;
    }
}

void Board::Template() 
{
    string rowstr;
    ifstream in(file.c_str());
    if(in.fail())
    {
        cerr << "fail";
    }
    int endLine = startLine + 25;
    int count = 0;
    do
    {
        getline(in, rowstr);

        if(count >= startLine)
        {
            map.push_back(rowstr);
        }
        count++;

    }while(count < endLine);
    in.close();
    startLine += 25;

    for(int i = 0; i < 25; i++) 
    {
        for(int j = 0; j < 79; j++)
        {
            pair<int, int> location(i,j);
            char c = map[i][j];
            int chamber = -1;

            
            if(c == '@')
            {

                chamber = hero->checkroom(location); //
                if(endLine == 25) 
                {
                    makePlayer(location, chamber);
                    if(gameover) return;
                }
                else
                {
                    hero->setLocation(location);
                    hero->setChamber(chamber);
                }
    
            }
            else if(c == 'H' || c == 'W' || c == 'L' || c == 'E' || c == 'O' || c == 'M')
            {

                chamber = hero->checkroom(location);
                int account = rand() % 2 + 1;
                Enemy* p;
                if(c == 'H')
                {
                    p = new Human(chamber, location, *this, 4);
                }
                else if(c == 'W')
                {
                    p = new Dwarf(chamber, location, *this, account); 
                }
                else if(c == 'L')
                {
                    p = new Halfling(chamber, location, *this, account); 
                }
                else if(c == 'E')
                {
                    p = new Elf(chamber, location, *this, account);
                }
                else if(c == 'M')
                {
                    p = new Merchant(chamber, location, *this, 4); 
                }
                else if(c == 'O')
                {
                    p = new Orc(chamber, location, *this, account);
                }
                enemies.push_back(p);
            }
            else if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5')
            {
                chamber = hero->checkroom(location);
                Potion* p;
                if(c == '0')
                {
                    p = new Potion(location, *this, "RH", chamber);
                }
                else if(c == '1')
                {
                    p = new Potion(location, *this, "BA", chamber); 
                }
                else if(c == '2')
                {
                    p = new Potion(location, *this, "BD", chamber); 
                }
                else if(c == '3')
                {
                    p = new Potion(location, *this, "PH", chamber);
                }
                else if(c == '4')
                {
                    p = new Potion(location, *this, "WA", chamber);
                }
                else if(c == '5')
                {
                    p = new Potion(location, *this, "WD", chamber);
                }
                potions.push_back(p);
                modifymap(location, 'P');
            }
            else if(c == '6' || c == '7' || c == '8' || c == '9')
            {
                chamber = hero->checkroom(location);
                Gold* p;
                if(c == '6')
                {
                    p = new Gold(location, *this, chamber, 2);
                }
                else if(c == '7')
                {
                    p = new Gold(location, *this, chamber, 1);
                }
                else if(c == '8')
                {
                    p = new Gold(location, *this, chamber, 4); 
                }
                else if(c == '9')
                {
                    p = new Gold(location, *this, chamber, 6); 
                    pair<int,int> temp = location;
                    temp.second += 1;
                    Enemy* e = new Dragon(chamber, temp, *this, *p); 
                    enemies.push_back(e);
                    statechange(chamber, temp, false);
                }
                bank.push_back(p);
                modifymap(location, 'G');
            }
            else if(c == '\\')
            {
                chamber = hero->checkroom(location);
            }
            if(chamber != -1)
                {
                    statechange(chamber, location, false);
                }
        }
    }
}

int main(int argc, char* argv[])
{
    srand((unsigned)time(NULL));
    string file = "defaultFloor.txt";

    if(argc == 2)
    {
        file = argv[1];
        cout << file;
    }

    Board* mb = NULL;
    do
    {
        delete mb;
        mb = new Board(file);

        if(mb->again()) continue;
        if(mb->isover()) return 0;
        
        mb->printBoard();

        string command;
        while(!(mb->isover()) && cin >> command)
        {
            mb->play(command);
        }

        if(mb->iswin())
        {
            int Score = mb->getScore();
            if(mb->getHeroType() == "Shade") Score *= 2;

            cout << "Congratulations, you have won the game!" << endl;
            cout << "Final Score: " << Score << endl;
            cout << "Would you like to play again? (y/n): ";

            string ch;
            while(cin >> ch)
            {
                if(ch == "y")
                {
                    cout << "Go for it!" << endl;
                    mb->setRetry(true);
                    break;
                }
                if(ch == "n")
                {
                    cout << "See you next time. Bye!" << endl;
                    break;
                }
                cout << "Invalid command. Please enter y or n: "; 
            }
        }   

    }while(mb->again());
    delete mb;
    return 0;
}

