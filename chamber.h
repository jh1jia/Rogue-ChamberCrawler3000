#ifndef Chamber_H
#define Chamber_H
#include <iostream>
#include <utility>
#include <vector>
using std::pair;
using std::vector;

class Board;

class Chamber 
{
public:
    Chamber(int, Board&);
    ~Chamber();
    bool isValid(int row, int col);
    void setflag(const pair<int,int>& loc, bool valid);
    pair<int,int> makeLocation();
    void makeStair();
    int getStartCol();
    int getStartRow();
    void aroundSelect(pair<int,int>& loc);
private:
    vector<bool*> validSpace;
    int number, startRow, startCol, height, width;
    Board& board;
};

#endif

