#include "drow.h"
#include <utility>
#include <string>
#include <iostream>
using namespace std;

Drow::Drow(pair<int,int> loc, int chamber, Board& bd) 
: Hero(chamber, loc, bd, 150, 25, 15, "Drow")
{}
