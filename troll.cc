#include "troll.h"
#include <utility>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

Troll::Troll(pair<int,int> loc, int chamber, Board& bd) 
: Hero(chamber, loc, bd, 120, 25, 15, "Troll")
{}
