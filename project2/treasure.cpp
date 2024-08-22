#include "treasure.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

treasure::treasure() {}

void treasure::setPos(int p){
    _position = p;
}
int treasure::getPos(){
    return _position;
}

void treasure::setRiddle(Riddle r){
    _riddle = r;
}
Riddle treasure::getRiddle(){
    return _riddle;
}
