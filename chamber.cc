#include "chamber.h"
#include "board.h"
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

Chamber::Chamber(int num, Board& bd) 
: number(num), board(bd) 
{
    // left up board
    if(num == 0)      
    { 
        height = 4;
        width = 26;
        startRow = 3;
        startCol = 3;
    }
    else if(num == 1)   // left down board
    {  
        height = 7;
        width = 21;
        startRow = 15;
        startCol = 4;
    }
    else if(num == 2)   // central board
    {   
        height = 3;
        width = 12;
        startRow = 10;
        startCol = 38;
    }
    else if(num == 3)  // right up board
    { 
        height = 10;
        width = 37;
        startRow = 3;
        startCol = 39;
    }
    else if(num == 4)   // right down board
    { 
        height = 6;
        width = 39;
        startRow = 16;
        startCol = 37;
    }

    for(int i = 0; i < height; i++) 
    {
        validSpace.push_back(new bool[width]);
    }

    for(vector<bool*>::iterator p = validSpace.begin(); p != validSpace.end(); p++)
    {
        for(int i = 0; i < width; i++) 
        {
            (*p)[i] = true;
        }
    }

    if(num == 4)
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 28; j++)
            {
                validSpace[i][j] = false;
            }
        }
    }
    else if(num == 3)
    {
        for(int i = 4; i < height; i++)
        {
            for(int j = 0; j < 22; j++)
            {
                validSpace[i][j] = false;
            }
        }
        for(int i = 0; i < 2; i++)
        {
            for(int j = 23; j < width; j++)
            {
                validSpace[i][j] = false;
            }
        }
        for(int j = 31; j < width; j++)
        {
            validSpace[2][j] = false;
        }
        for(int j = 34; j < width; j++)
        {
            validSpace[3][j] = false;
        }
    }
}

Chamber::~Chamber() 
{
    for(vector<bool*>::iterator p = validSpace.begin(); p != validSpace.end(); p++)
    {
        delete [] *p;
    }
}

bool Chamber::isValid(int row, int col) 
{
    return (row >= 0 && row < height && col >= 0 && col < width)? validSpace[row][col] : false;
}

void Chamber::aroundSelect(pair<int,int>& loc)
{
    int x, y;
    do
    {
        x = rand() % 3 - 1;
        y = rand() % 3 - 1;

    }while((x == 0 && y == 0) || !(isValid(loc.first + x - startRow, loc.second + y - startCol))); 

    loc.first += x;
    loc.second += y;
}

pair<int,int> Chamber::makeLocation() 
{
    int x, y;
    do
    {
        x = rand() % height;
        y = rand() % width;

    }while(!isValid(x, y));
    pair<int,int> location(x + startRow, y + startCol);
    return location;
}

void Chamber::setflag(const pair<int,int>& loc, bool flag) 
{
    int inrow = loc.first - startRow;
    int incol = loc.second - startCol;
    validSpace[inrow][incol] = flag;
}

void Chamber::makeStair() 
{
    pair<int, int> location = makeLocation();
    setflag(location, false);
    board.modifymap(location, '\\');
}
