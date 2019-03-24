#include "halfling.h"
#include <utility>
#include <string>
using namespace std;

Halfling::Halfling(int chamber, pair<int,int> loc, Board& bd, int m) 
: Enemy('L', chamber, loc, bd, 100, 15, 20, "Halfling", m)
{}
