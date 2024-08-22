#ifndef TREASURE_H
#define TREASURE_H

#include <iostream>
#include <vector>
#include "Board.h"

#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;


class treasure
{
private:
    int _position;
    //int reward;
    Riddle _riddle;
public:
    treasure();

    void setPos(int p);
    int getPos();

    void setRiddle(Riddle r);
    Riddle getRiddle();

};

#endif