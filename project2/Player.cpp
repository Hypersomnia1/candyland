#include "Player.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

Player::Player() {}

Player::Player(int stamina, double gold, Candy candy_array[_MAX_CANDY_AMOUNT], int candy_arr_size) {
 _stamina = stamina;
 _gold = gold;
 for (int i = 0; i < candy_arr_size && _candy_amount < _MAX_CANDY_AMOUNT; i++) {
     if (candy_array[i].name.empty()) continue;
     _inventory[_candy_amount++] = candy_array[i];
 }
}

int Player::getCandyAmount() { return _candy_amount; }

void Player::skipTurn(int skips){ _skipTurns += skips;}
int Player::getSkipValue(){ return _skipTurns; }

void Player::setStamina(int stamina) { _stamina = stamina; }
int Player::getStamina() { return _stamina; }

void Player::setPlrName(string name) { _plrname = name; }
string Player::getPlrName() { return _plrname; }

void Player::setCharName(string name) { _charName = name; } // Might have to include adding candies from char to player inventory
string Player::getCharName() { return _charName; }

void Player::setGold(double gold) { _gold = gold; }
double Player::getGold() { return _gold; }


void Player::printInventory() {
 for (int i = 0; i < _MAX_CANDY_AMOUNT; i++) {
 if (_inventory[i].name.empty()) {
   cout << "|[Empty]";
 } else {
   cout << "|[" << _inventory[i].name << "]";
 }
 if (i % 3== 2) cout << "|" << endl;
 }
} 
bool Player::isInventoryFull(){
    if (_candy_amount == _MAX_CANDY_AMOUNT){
        return true;
    }
    return false;
}


Candy Player::findCandy(string candy_name) {
 for (int i = 0; i < _candy_amount; i++) {
     if (_inventory[i].name == candy_name) return _inventory[i];
 }
 return Candy();
}
vector<Candy> Player::findCandyByType(string candy_type){
    vector<Candy> found;
    for (int i = 0; i < _candy_amount; i++) {
     if (_inventory[i].candy_type == candy_type) found.push_back(_inventory[i]);
    }
    return found;
}

bool Player::addCandy(Candy candy) {
 if (_candy_amount >= _MAX_CANDY_AMOUNT) return false;
 _inventory[_candy_amount++] = candy;
 return true;
}

bool Player::removeCandy(string candy_name) {
 for (int i = 0; i < _candy_amount; i++) {
     if (_inventory[i].name == candy_name) {
         for (int j = i; j < _candy_amount - 1; j++) {
             _inventory[j] = _inventory[j + 1];
         }
         _inventory[--_candy_amount] = Candy();
         return true;
     }
 }
 return false;
}

void Player::giveRR(){
    _has_RobberRepel = true;
}
bool Player::hasRR(){
    return _has_RobberRepel;
}

// add rock paper scissors against bot

bool Player::playRockPaperScissors()
{
    // if(players[0].getCandyAmount() == 0 || players[1].getCandyAmount() == 0)
    // {
    //     cout << "Not enough candy!" << endl;
    // }
    // else
    // {
        // string candy1;
        // string candy2;
        // Candy p1;
        // Candy p2;
        // cout << "Player 1 Inventory" << endl;
        // playerUser.printInventory();
        // cout << "Player 1: Select candy to bet" << endl;
        // getline(cin, candy1);
        // cin.clear();

        // while(playerUser.findCandy(candy1).name == "")
        // {
        //     cout << "Invalid selection!" << endl;
        //     getline(cin, candy1);
        // }
        // p1 = playerUser.findCandy(candy1);

        // cout << "Player 2 Inventory" << endl;
        // players[1].printInventory();
        // cout << "Player 2: Select candy to bet" << endl;
        // getline(cin, candy2);
        // cin.clear();

        // while(players[1].findCandy(candy2).name == "")
        // {
        //     cout << "Invalid selection!" << endl;
        //     getline(cin, candy2);
        // }
        // p2 = players[1].findCandy(candy2);


        char choice1;
        char choice2;
        string input;
        do
        {
            cout << "Player " << _plrname << ": Enter r, p, or s" << endl;
            getline(cin,input);
            choice1 = input[0];
            while(choice1 != 'r' && choice1 != 'p' && choice1 != 's')
            {
                cout << "Invalid selection!" << endl;
                getline(cin,input);
                choice1 = input[0];
            }
            // cout << "Player 2: Enter r, p, or s" << endl;
            // cin >> choice2;
            // while(choice2 != 'r' && choice2 != 'p' && choice2 != 's')
            // {
            //     cout << "Invalid selection!" << endl;
            //     cin >> choice2;
            // }
            srand(time(0));
            int random_number = rand()%3;
            switch(random_number){
                case(0):
                    choice2 = 'r';
                    break;
                case(1):
                    choice2 = 'p';
                    break;
                case(2):
                    choice2 = 's';
                    break;
            }
            cout << "Computer chose: " << choice2 << endl;
            if(choice1 == choice2)
            {
                cout << "Tie! Play again" << endl;
            }
        }while(choice1 == choice2);

        if((choice1 == 'p' && choice2 == 'r') || (choice1 == 'r' && choice2 == 's') || (choice1 == 's' && choice2 == 'p'))
        {
            cout << "Player " << _plrname << " has won!" << endl;

            return true;

            // playerUser.addCandy(p2);
            // players[1].removeCandy(candy2);
        }
        else
        {
            cout << "Player " << _plrname << " has lost!" << endl;

            return false;

            // players[1].addCandy(p1);
            // players[0].removeCandy(candy1);
        }
    //}
}
