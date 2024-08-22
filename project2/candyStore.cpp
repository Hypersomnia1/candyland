#include "candyStore.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

candyStore::candyStore() {}

void candyStore::setPos(int p){
    _position = p;
}
int candyStore::getPos(){
    return _position;
}


void candyStore::setName(string n){
    _name = n;
}
string candyStore::getName(){
    return _name;
}

void candyStore::setCandies(vector<Candy> c){
    _candies = c;
}
vector<Candy> candyStore::getCandy(){
    return _candies;
}

void candyStore::displayVector(){

    int vec_size = _candies.size();
    cout << "Here is a list of candies in the candy store " << _name << ":"<< endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < vec_size; i++){
        cout << "----------------------------" << endl
        << "Name: " << _candies.at(i).name << endl
        << "Description: " << _candies.at(i).description << endl
        << "Effect: " << _candies.at(i).effect << endl
        << "Effect Value: " << _candies.at(i).effect_value << endl
        << "Candy Type: " << _candies.at(i).candy_type << endl
        << "Price: " << _candies.at(i).price << endl;
    }
    cout << endl;
}

