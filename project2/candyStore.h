#ifndef CANDYSTORE_H
#define CANDYSTORE_H

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

// struct CandyStore
// {
//     vector<Candy> candies;
//     string name;
//     int position;
// };

class candyStore
{
private:
    int _position;
    string _name;
    vector<Candy> _candies;
public:
    candyStore();

    void setPos(int p);
    int getPos();

    void setName(string n);
    string getName();

    void setCandies(vector<Candy> c);
    vector<Candy> getCandy();

    void displayVector();

};

#endif