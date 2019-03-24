#ifndef Board_H
#define Board_H
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <iostream>
using std::pair;
using std::string;
using std::vector;

class Entity;
class Gold;
class Potion;
class Enemy;
class Hero;
class Chamber;

class Board
{
public:
    Board(string filename);
    ~Board();
    void makePlayer(pair<int,int>, int);
    void makeFloor();
    void makeEnemies();
    void makeGold();
    void makePotions();
    void printBoard();
    char getPiece(pair<int,int> loc);
    Gold* searchGold(pair<int,int> loc);
    Potion* searchPotion(pair<int,int> loc);
    Enemy* searchEnemy(pair<int,int> loc);
    void modifymap(const pair<int,int>& loc, char change);
    void statechange(int ch, pair<int,int> loc, bool flag);
    void moveMap(pair<int,int> prev, pair<int,int> post, Entity& c);
    void checkNearby(pair<int,int> loc);
    void findHero(Enemy& foe);
    void play(string command);
    bool isVisible(string str);
    void setVisible(string str);
    void clear();
    void newGold(pair<int,int> loc, int cr, int account);
    bool isover();
    bool again();
    void setRetry(bool b);
    void setWin();
    int getScore();
    bool iswin();
    string getHeroType();
    bool checkCommand(string str);
    void Template();
    void select(int ch, pair<int,int>& loc);
 private:
    bool gameover;
    bool retry;
    bool win;
    int startLine;
    string file;
    Hero* hero;
    vector<string> map;
    vector<Chamber*> chambers;
    vector<Enemy*> enemies; 
    vector<Potion*> potions;
    vector<Gold*> bank;
    vector<string> Pcontainer;   
};

#endif
