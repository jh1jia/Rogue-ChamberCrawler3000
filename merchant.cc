#include "merchant.h"
#include <utility>
#include <string>
#include <iostream>
using namespace std;

Merchant::Merchant(int chamber, pair<int,int> loc, Board& bd, int m)  
: Enemy('M', chamber, loc, bd, 30, 70, 5, "Merchant", m)
{}
