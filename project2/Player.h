#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Board.h"

using namespace std;

class Player {
private:
  string _plrname;
  const static int _MAX_CANDY_AMOUNT = 9;
  int _stamina = 0;
  double _gold = 0;
  Candy _inventory[_MAX_CANDY_AMOUNT] = {};
  int _candy_amount = 0;
  string _charName;
  int _skipTurns = 0;
  bool _has_RobberRepel = false;

public:
  Player();
  Player(int stamina, double gold, Candy candy_array[_MAX_CANDY_AMOUNT], int candy_arr_size);

  int getCandyAmount();

  void skipTurn(int);
  int getSkipValue();

  void setPlrName(string name);
  string getPlrName();

  void setCharName(string name);
  string getCharName();

  void setStamina(int stamina);
  int getStamina();

  void setGold(double gold);
  double getGold();

  void printInventory();
  bool isInventoryFull();

  Candy findCandy(string candy_name);
  vector<Candy> findCandyByType(string candy_type);

  bool addCandy(Candy candy);

  bool removeCandy(string candy_name);

  void giveRR();
  bool hasRR();

  bool playRockPaperScissors();
};


#endif // PLAYER_H
