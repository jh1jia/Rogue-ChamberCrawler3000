#include "shade.h"
#include <utility>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;


Shade::Shade(pair<int,int> loc, int chamber, Board& bd)
: Hero(chamber, loc, bd, 125, 25, 25, "Shade")
{}
