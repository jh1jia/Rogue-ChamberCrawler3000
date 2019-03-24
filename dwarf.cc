#include "dwarf.h"
#include <utility>
#include <string>
#include <iostream>
using namespace std;

Dwarf::Dwarf(int chamber, pair<int,int> loc, Board& bd, int m) 
: Enemy('W', chamber, loc, bd, 100, 20, 30, "Dwarf", m)
{}
