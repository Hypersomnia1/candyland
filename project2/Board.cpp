#include "Board.h"

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    _treasure_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }
    for(int i = 0; i < _player_positions.size(); i++){
        _player_positions.at(i) = 1;
    } // loop thru players
}

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    // vector<int> player_present;
    // for(int i = 0; i < _player_positions.size(); i++){
    //     if(_player_positions.at(i) == position){
    //         player_present.push_back(i);
    //     }
    // }
    bool plrfound = false;
    // if (position==_player_positions.at(0)){
    //     cout << "1";
    // } else if (position==_player_positions.at(1)){
    //     cout << "2";
    // }
    for (int i = 0; i < _player_positions.size(); i++){
        if (position==_player_positions.at(i)-1){
            cout << i+1;
            plrfound = true;
            break;
        }
    }
    if (!plrfound)
    {
        cout << " ";
    }
    cout << " " << RESET;
}

void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

void Board::createSpecialTiles()
{
    srand(time(0));
    for (int i = 2; i<82;i++){
        if (rand()%4==1){
            Special_Tile temp = {i,rand()%4};
            _specialtiles.push_back(temp);
            //vector of special tiles = i
        }
    }
    //code
}

void Board::addPlayer(int pos)
{
    _player_positions.push_back(pos);
}

bool Board::setPlayerPosition(int new_position, int player_selected)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player_positions.at(player_selected) = new_position;
        return true;
    }
    return false;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}
 
Gummied Board::getGummyAtTile(int board_position){
    for (int i = 0; i < _gummied_positions.size();i++){
        if (_gummied_positions.at(i).tileindex==board_position){
            return _gummied_positions.at(i);
        }
    }
    return Gummied();
}

int Board::getPlayerPosition(int player_selected) const
{
    return _player_positions.at(player_selected);
}

Special_Tile Board::getSpecialTile(int position){
    Special_Tile blank = {-1,-1};
    for (int i = 0; i < _specialtiles.size();i++){
        if (position == _specialtiles.at(i).tile_num){
            return _specialtiles.at(i);
        }
    }
    return blank;
}

bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::addTreasure(int position)
{
    if (_treasure_count >= _MAX_TREASURES)
    {
        return false;
    }
    _treasure_position[_treasure_count] = position;
    _treasure_count++;
    return true;
}

bool Board::isPositionTreasure(int board_position)
{
    for (int i = 0; i < _treasure_count; i++)
    {
        if(_treasure_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}
void Board::treasureUsed(int board_position){
    for (int i = 0; i < _treasure_count; i++)
    {
        if(_treasure_position[i] == board_position)
        {
            _treasure_position[i]=-100;
        }
    }
}

bool Board::addGummyTile(int playerindex, int tileindex,int effval){
    for (int i = 0; i < _gummied_positions.size();i++){
        if (_gummied_positions.at(i).tileindex==tileindex){
            return false;
        }
    }
    Gummied temp = {playerindex,tileindex,effval};
    _gummied_positions.push_back(temp);
    return true;
}

void Board::removeGummyTile(int tileindex){
    for (int i = 0; i < _gummied_positions.size();i++){
        if (_gummied_positions.at(i).tileindex==tileindex){
            _gummied_positions.erase(_gummied_positions.begin() + i);
        }
    }
}
bool Board::isPositionGummy(int board_position){
    for (int i = 0; i < _gummied_positions.size();i++){
        if (_gummied_positions.at(i).tileindex==board_position){
            return true;
        }
    }
    return false;
}

bool Board::movePlayer(int tile_to_move_forward,int player_selected)
{
    int new_player_position = tile_to_move_forward + _player_positions.at(player_selected);
    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    _player_positions.at(player_selected) = new_player_position;
    return true;
}