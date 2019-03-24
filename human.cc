#include "human.h"
#include <utility>
#include <string>
#include <iostream>
using namespace std;

Human::Human(int chamber, pair<int,int> loc, Board& bd, int m)
: Enemy('H', chamber, loc, bd, 140, 20, 20, "Human", m)
{}
