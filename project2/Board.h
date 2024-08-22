#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;

struct Candy
{
    string name;
    string description;
    string effect;
    int effect_value;
    string candy_type;
    double price;
    
};

struct Character
{
    string name;
    int stamina,gold;
    vector<Candy> candies;
};

struct Tile
{
    string color;
    string tile_type;
};

struct Special_Tile
{
    int tile_num;
    int special_type;
};

struct Gummied{
    int playerSet;
    int tileindex;
    int candyEffect;
};

struct Card{
    string color;
    int x2;
};

struct Riddle{
    string riddle;
    string answer;

};


class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count;
    const static int _MAX_TREASURES = 3;
    int _treasure_position[_MAX_CANDY_STORE];
    int _treasure_count;
    vector<Gummied> _gummied_positions;
    vector<int> _player_positions;
    vector<Special_Tile> _specialtiles;

public:
    Board();

    void resetBoard();
    void displayTile(int);
    void displayBoard();
    void createSpecialTiles();
    void addPlayer(int);

    bool setPlayerPosition(int, int);

    int getBoardSize() const;
    int getCandyStoreCount() const;
    Gummied getGummyAtTile(int);
    int getPlayerPosition(int) const;

    Special_Tile getSpecialTile(int);

    bool addCandyStore(int);
    bool isPositionCandyStore(int);

    bool addTreasure(int);
    bool isPositionTreasure(int);
    void treasureUsed(int);

    bool addGummyTile(int playerindex, int tileindex, int effval);
    void removeGummyTile(int tileindex);
    bool isPositionGummy(int);

    bool movePlayer(int tile_to_move_forward, int player_selected);
};

#endif