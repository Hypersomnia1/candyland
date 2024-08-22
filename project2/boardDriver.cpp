#include "Board.h"
#include "candyStore.h"
#include "Player.h"
#include "treasure.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
/*
Instructions to run:
g++ -std=c++17 -Wall -Werror -Wpedantic boardDriver.cpp Board.cpp candyStore.cpp Player.cpp treasure.cpp
./a.out
*/
using namespace std;

string convertToLower(string in){
    string out = "";
    for (char c : in) {
        out += tolower(c);
    }
    return out;
}

void writeGameStats(string winnerName,int totalturns){
    ofstream statfile;
    statfile.open("gameResults.txt");
    statfile << "Winner: Player " << winnerName << endl << "Total Turns Played: " << totalturns << endl;
    statfile.close();
}
candyStore findCandyStoreWithPosition(candyStore stores[3], const int STORE_SIZE, int position){
    candyStore found_store;
    for (int i = 0; i<STORE_SIZE; i++){
        if (stores[i].getPos() == position){
            return stores[i];
        }
    }
    return found_store;
}

void displayCharacters(vector<Character> chars){
    cout << "----------------------------" << endl;
    
    for (int i = 0; i<chars.size();i++){
        
        cout << "Name: " << chars.at(i).name << endl
        << "Stamina: " << chars.at(i).stamina << endl
        << "Gold: " << chars.at(i).gold << endl << "Candies:" << endl;
        for (int j = 0; j<chars.at(i).candies.size();j++){
            cout << "[" << chars.at(i).candies.at(j).name << "]";
        }
        cout << endl << "----------------------------" << endl;
    }
}

int getDistanceNeeded(int currentPos, string targetcolor) {
    //{"Minty Green", "Bubblegum Blue", "Cotton Candy Magenta"}
   int newPosition = currentPos-1;
   int targetPos, movedist;
   //find color

    if (targetcolor == "Cotton Candy Magenta"){
        
        targetPos = 0;
    } else if (targetcolor == "Minty Green"){
        targetPos = 1;
    } else if (targetcolor == "Bubblegum Blue"){
        targetPos = 2;
    } 

    for(int i = 0; i < 3;i++){ // RUN BELOW CODE 3 TIMES WITH 1 2 AND 3 NewPos = 0
        if (newPosition%3==i){//FOR WHATEVER THE CURRENT POSITION IS Issue is here
            if (i - targetPos==0){ // same color
                movedist = 3;
            } else if (i - targetPos == -1||i - targetPos == 2){ //target is very next color or 2 before
                movedist = 1;
            } else if (i - targetPos == -2||i - targetPos == 1){ //target 2 colors next or 1 before
                movedist = 2;
            } 
        }
    }
   // Increment the position based on the color
   

   return movedist;
}

bool Unscramble(){
    string input;
    vector<string> candywords = {"TAFFY","CHOCOLATE","SWEET","TREAT","DESSERT","GUMDROP","FUDGE","PEPPERMINT","JELLYBEAN","LICORICE","MINT","TOFFEE","GUM","TRUFFLES","LOLLIPOPS","CARAMEL","GUMMY"};
    srand(time(0));
    int amount = rand()%4+1;
    cout << "You will need to unscramble "  << amount << " words in a row." << endl;
    for (int i = 0;i<amount;i++){
        int randin = rand()%candywords.size();
        string scrambled = candywords.at(randin);

        
        for (int k = scrambled.length() - 1; k > 0; --k) {
            int j = rand() % (k + 1);
            swap(scrambled[k], scrambled[j]);
        }

        cout << "Unscramble word "<< i <<": " << scrambled << endl;
        getline(cin,input);
        if (input!=candywords.at(randin)){
            cout << "Wrong! The word was " << candywords.at(randin) << endl;
            return false;
        } else {
            cout << "Correct!" << endl;
        }

        candywords.erase(candywords.begin()+randin);
    }
    return true;
}

int main()
{
    Board board;
    int moves;
    int position;
    int player_count;


    //load candies
    ifstream infile;
    
    infile.open("candies.txt");
    string line;
    vector<string> names,descriptions,effects,types;
    vector<int> effectValues;
    vector<float> prices;



    while (getline(infile, line)) { 
        // create a stringstream variable and associate to a string variable
        stringstream ss(line);
        
        // this is to tokenize each line into 6 parts - because we know they have 6 parts
        string token;
        //getline(ss, token, '|');
        for (int i=0; i<6; i++) {
            getline(ss, token, '|');
            
              //Name|Description|Effect type|Effect value|Candy type|Price
            switch(i){
                case(0):
                    names.push_back(token);
                    break;
                case(1):
                    descriptions.push_back(token);
                    break;
                case(2):
                    effects.push_back(token);
                    break;
                case(3):
                    effectValues.push_back(stoi(token));
                    break;
                case(4):
                    types.push_back(token);
                    break;
                case(5):
                    prices.push_back(stof(token));
                    break;
            }
            
        }
    }
    Candy candyList[11];
    for (int i = 0; i < sizeof(candyList)/sizeof(candyList[0]);i++){
        candyList[i] = {names.at(i),descriptions.at(i),effects.at(i),effectValues.at(i),types.at(i),prices.at(i)};
    }
    //-----------
    ifstream infile2;
    infile2.open("characters.txt");
    string line2;
    vector<string> charNames;
    vector<int> staminas,golds;
    vector<vector<Candy>> charCandies;


    while (getline(infile2, line2)) { 
        // create a stringstream variable and associate to a string variable
        stringstream ss(line2);
        
        // this is to tokenize each line into 6 parts - because we know they have 6 parts
        string token2;
        //getline(ss, token, '|');
        for (int i=0; i<4; i++) {
            getline(ss, token2, '|');
            
              //Name|Description|Effect type|Effect value|Candy type|Price
            switch(i){
                case(0):
                    charNames.push_back(token2);
                    break;
                case(1):
                    staminas.push_back(stoi(token2));
                    break;
                case(2):
                    golds.push_back(stoi(token2));
                    break;
                case(3): // Put candy vectors
                    string splitThis;
                    stringstream ss2(token2);
                    vector<string> charCandyNames;
                    vector<Candy> actualCandyList;
                    while(getline(ss2, splitThis, ',')){
                        charCandyNames.push_back(splitThis);
                    }
                    for (int j = 0; j < charCandyNames.size(); j++){
                        //cout << "charCandyNames at j is: " << charCandyNames.at(j) << " | j is " << j << endl;
                        for (int k = 0; k < sizeof(candyList)/sizeof(candyList[0]);k++){
                            if (charCandyNames.at(j) == candyList[k].name){
                                //cout << "CandyList added for j " << j << " is: " << candyList[k].name << endl;
                                actualCandyList.push_back(candyList[k]);
                            }
                        }
                    }
                    // for (int i = 0; i < sizeof(actualCandyList)/sizeof(actualCandyList[0]);i++){
                            
                    // }
                    charCandies.push_back(actualCandyList);
                    actualCandyList.clear();
                    break;
            }
            
        }
    }

    vector<Character> charList;
    //cout << "Charlist size is" << endl;
    for (int i = 0; i < charNames.size();i++){
        Character pushChar = {charNames.at(i),staminas.at(i),golds.at(i),charCandies.at(i)};
        charList.push_back(pushChar);
    }
    //-----
    ifstream infile3;
    infile3.open("riddles.txt");
    string line3;
    vector<string> question,answer;
    while (getline(infile3, line3)) { 
        // create a stringstream variable and associate to a string variable
        stringstream ss(line3);
        
        // this is to tokenize each line into 6 parts - because we know they have 6 parts
        string token;
        //getline(ss, token, '|');
        for (int i=0; i<2; i++) {
            getline(ss, token, '|');
            
              //Name|Description|Effect type|Effect value|Candy type|Price
            switch(i){
                case(0):
                    question.push_back(token);
                    break;
                case(1):
                    answer.push_back(token);
                    break;
            }
            
        }
    }
    vector<Riddle> riddles;
    for (int i = 0; i < question.size();i++){
        Riddle pushRid = {question.at(i),answer.at(i)};
        riddles.push_back(pushRid);
    }


    

    srand(time(0));
    vector<Candy> v1,v2,v3;
    Candy c1 = candyList[rand()%11];
    Candy c2 = candyList[rand()%11];
    Candy c3 = candyList[rand()%11];
    v1.push_back(c1);
    v2.push_back(c2);
    v3.push_back(c3);
    for (int i = 0; i<2;i++){
        
        c1 = candyList[rand()%11];
        c2 = candyList[rand()%11];
        c3 = candyList[rand()%11];

        bool isduplicate = true;
        while (isduplicate){
            for (int i = 0; i < v1.size();i++){
                if(c1.name==v1.at(i).name){
                    isduplicate = true;
                    c1 = candyList[rand()%11];
                } else {
                    isduplicate = false;
                }
                if(c2.name==v2.at(i).name){
                    isduplicate = true;
                    c2 = candyList[rand()%11];
                } else {
                    isduplicate = false;
                }
                if(c3.name==v3.at(i).name){
                    isduplicate = true;
                    c3 = candyList[rand()%11];
                } else {
                    isduplicate = false;
                }
            }
        }

            v1.push_back(c1);
            v2.push_back(c2);
            v3.push_back(c3);
        
        
    }
    

    vector<Candy> candies_arr[3] = {v1, v2, v3};

    candyStore s1;
    candyStore s2;
    candyStore s3;
    // s1.setPos(24);
    //  = {v1, "Store 1", 24};
    // CandyStore s2 = {v2, "Store 2", 53};
    // CandyStore s3 = {v3, "Store 3", 75};

    const int arrsize = 3;
    candyStore store_arr[arrsize] = {s1, s2, s3};

    

    srand(time(0));
    //Magenta is 
    int pos1 = (rand()%26 + 2);
    int pos2 = (rand()%27 + 28);
    int pos3 = (rand()%27 + 55);

    int adjustPos1 = (pos1-(pos1%3))+1;
    if (adjustPos1==1){
        adjustPos1+=3;
    }


    int storepos[arrsize] = {adjustPos1,(pos2-(pos2%3))+2,(pos3-(pos3%3))+3};
    //Each candy store has different types of candies. Candy stores will be randomly positioned on the Candyland trail with a small constraint. In the first 27 tiles, a candy store will be on a magenta-colored tile. Between tiles 28 and 54, a candy store will appear on a green-colored tile. And from tile 55 to 82, a candy store will be on a blue tile.
    for (int i = 0; i < arrsize; i++){
        store_arr[i].setPos(storepos[i]);
        string storeName = "Store " + to_string(i);
        store_arr[i].setName(storeName);
        store_arr[i].setCandies(candies_arr[i]);
        board.addCandyStore(store_arr[i].getPos());
    }

    candyStore starterStore;
    vector<Candy> starterStoreCandies;
    starterStore.setName("Starter Store");
    int rc1 = rand()%3;
    int rc2 = rand()%4+3;
    int rc3 = rand()%4+7;

    
    starterStoreCandies.push_back(candyList[rc1]);
    starterStoreCandies.push_back(candyList[rc2]);
    starterStoreCandies.push_back(candyList[rc3]);
    
    starterStore.setCandies(starterStoreCandies);

    board.createSpecialTiles();
    treasure treasures[3];
    srand(time(0));
    
    
    vector<Riddle> tempriddle = riddles;
    for (int i = 0; i < 3; i++){
        int randpos = rand()%80+2;
        bool isUnique;
        do {
            randpos = rand() % 80 + 2;
            isUnique = true; // Set to true initially

            for (int j = 0; j < i; j++) {
                if (randpos == treasures[j].getPos()) {
                    isUnique = false;
                    randpos = rand()%80 + 2; // Generate new randpos
                    break;
                }
            }
        } while (!isUnique);
    
        treasures[i].setPos(randpos);
        int tempIndex = rand()%tempriddle.size();
        Riddle randomRiddle = tempriddle.at(tempIndex);
        tempriddle.erase(tempriddle.begin()+tempIndex);
        treasures[i].setRiddle(randomRiddle);
        board.addTreasure(treasures[i].getPos());
    }
    //Name|Description|Effect type|Effect value|Candy type|Price
    Candy vigorjellybean = {"Jellybean of Vigor","Offers stamina regeneration, providing a significant boost to player stamina","stamina",50,"magical",0};
    Candy treasureTruffle = {"Treasure Hunter's Truffle","Allows the player to unlock a hidden treasure from anywhere","treasure",1,"treasure",0};
    // Candy tempor[2] = {vigorjellybean,treasureTruffle};
    // for (int i = 0; i <2; i++){
    // cout << "----------------------------" << endl
    //     << "Name: " << tempor[i].name << endl
    //     << "Description: " << tempor[i].description << endl
    //     << "Effect: " << tempor[i].effect << endl
    //     << "Effect Value: " << tempor[i].effect_value << endl
    //     << "Candy Type: " << tempor[i].candy_type << endl
    //     << "Price: " << tempor[i].price << endl;
    // }


    // for(int j = 0; j < 3; j++){
    //     cout << "Name: " << store_arr[j].getName() << endl;
    //     cout << "Position: " << store_arr[j].getPos() << endl;
    //     cout << "Vector info: " << endl;
    //     store_arr[j].displayVector();

    // }
    //board.displayBoard();
    string input;
    cout << "Welcome to the game of candyland. Please enter the number of participants:" << endl;
    getline(cin,input);
    player_count = stoi(input);
    while (player_count < 2){
        
            cout << "Minimum of 2 players required! Please re-enter the number of participants:" << endl;
            getline(cin,input);
            player_count = stoi(input);
        
    }
    bool shopping;
    vector<Player> players;
    for (int i = 0;i < player_count; i++){
        board.addPlayer(1);
        Player loadPlr;
        cout << "Enter Player " << i+1 << " Name:" << endl;
        getline(cin,input);
        loadPlr.setPlrName(input);
        
        cout << "Awesome! Here is a list of characters a player can select from:" << endl;
        //make a display character function
        displayCharacters(charList);

        cout << "The selected character is:" << endl;
        getline(cin,input);
        for (int i = 0;i<charList.size();i++){
            if (input == charList.at(i).name){
                loadPlr.setGold(charList.at(i).gold);
                loadPlr.setStamina(charList.at(i).stamina);
                loadPlr.setCharName(charList.at(i).name);
                for (int j = 0; j< charList.at(i).candies.size();j++){
                    loadPlr.addCandy(charList.at(i).candies.at(j));
                }
            }
            
        }
        // TODO: fre
        players.push_back(loadPlr);

        cout << "Would you like an initial visit to the Candy Store? (Yes or No)" << endl;
        getline(cin,input);
        if (convertToLower(input)=="yes"){
            
            //show store
            cout << "You have entered the starter candy store with " << players.at(i).getGold() << " gold." << endl;
            //startdiscount
            cout << "Would you like to try for a 10 percent discount? If fail, you will be overcharged 10 percent." << endl;
            double discountFactor = 1.0;
            getline(cin,input);
            if (convertToLower(input)=="yes"){
                if(Unscramble()){
                    cout << "Congratulations! You earned a 10 percent discount in this store! It will be applied when you buy a candy." << endl;
                    discountFactor = .9;
                } else{
                    discountFactor = 1.1;
                }
                
            }
            //if (discountFactor!=1.0){cout << "The price of the candy has been affected by a factor of" << discountFactor << endl;}
            starterStore.displayVector();
            
            shopping = true;
            while(shopping){
            cout << "Enter the name of Candy to purchase (or EXIT to leave):" << endl;
            getline(cin,input);
                if (convertToLower(input)!="exit"){
                    bool candyFound = false;
                    for (int j = 0; j< starterStore.getCandy().size();j++){
                        if (input==starterStore.getCandy().at(j).name){
                            candyFound = true;
                            if(players.at(i).getGold()>=starterStore.getCandy().at(j).price && !players.at(i).isInventoryFull()){
                                cout << "Success! Candy has been added to your inventory" << endl;
                                if (discountFactor!=1.0){cout << "The price of the candy has been affected by a factor of " << discountFactor << endl;}
                                players.at(i).setGold(players.at(i).getGold()-(starterStore.getCandy().at(j).price*discountFactor));
                                players.at(i).addCandy(starterStore.getCandy().at(j));
                                cout << "You now have " << players.at(i).getGold() << " gold." << endl;
                                
                            } else {
                                cout << "Purchase Failed. Either you don't have enough coins or your inventory is full." << endl;
                            }
                        }
                        
                    }
                    if (candyFound==false){
                            cout << "Candy name not found." << endl;
                        }
                } else{ shopping = false;}
            }
            
        }
    }
    int allturns = 0;
    int plrselected = 0;
    int maxStamina = 100;
    int maxGold = 100;
    int choice, goldlost;
    bool runGame = true;
    bool plrTurn = true;
    bool didDrawCard = false;
    int tempval;
    board.displayBoard(); 
    Card newCard;
    
    while(runGame){
        if (plrselected == players.size()){
            plrselected = 0;
        }
        string plrName = players.at(plrselected).getPlrName(); 
        //switch player's turn
        /* Initial Candy Store visit

        
        */
        cout << "It is now Player " << plrName << " turn." << endl;
        plrTurn = true;
        if (players.at(plrselected).getSkipValue()==0){
        while (plrTurn){
            allturns++;
            cout << "Please select a Menu Option:" << endl;
            cout << "1. Draw a card (End Turn)" << endl;
            cout << "2. Use Candy" << endl;
            cout << "3. Show player stats" << endl;
            getline(cin,input);
            choice = stoi(input);
            bool match = false;
            int tileplace;
            string cardcolors[] = {"Minty Green", "Bubblegum Blue", "Cotton Candy Magenta"};
            switch(choice){
                case(1):
                    startNewDraw:
                    plrTurn = false;
                    /**
                     * 
                     * MOVE PLAYER ACROSS BOARD
                     * Minty green, bubblegum blue, Cotton Candy Magenta
                     * Need to randomize colors
                    */
                    while (!didDrawCard){
                        cout << "Type 'D' to draw a card" << endl;
                        
                        getline(cin,input);
                        if (input.length()==1&&input[0] == 'D'){
                            didDrawCard = true;
                        } else {
                            cout << "Invalid!" << endl;
                        }
                    }
                    if (players.at(plrselected).getStamina()==0){
                        cout << "This draw left you out of stamina! You lose 2 turns but gain 20 stamina while recovering." << endl;
                        players.at(plrselected).skipTurn(2);
                        players.at(plrselected).setStamina(20);
                    } else{
                        players.at(plrselected).setStamina(players.at(plrselected).getStamina()-1);
                    }
                    didDrawCard = false;
                    srand(time(0));
                    
                    newCard = {cardcolors[rand()%3],rand()%4};
                    moves = getDistanceNeeded(board.getPlayerPosition(plrselected),newCard.color);
                    if (newCard.x2==2){
                        cout << "Lucky! You drew a: DOUBLE " << newCard.color << " card." << endl;
                        moves += 3;
                    } else {
                        cout << "You drew a: " << newCard.color << " card." << endl;
                    }
                    startAtMove:
                    if (board.movePlayer(moves,plrselected)){
                        board.displayBoard(); 
                        
                        position = board.getPlayerPosition(plrselected);
                        cout << "Player " << plrName << " has moved " << moves << " tiles to position: " << position << endl;
                        if(board.isPositionGummy(position)&&board.getGummyAtTile(position).playerSet!=plrselected){

                            cout << "You got stuck by a player's gummy!" << endl;
                            //board.getGummyAtTile(position)
                            players.at(plrselected).skipTurn(board.getGummyAtTile(position).candyEffect);
                            board.removeGummyTile(position);
                        } if (board.isPositionCandyStore(position)){
                            cout << "Position " << position << " is a candy store." << endl;
                            candyStore visited_store = findCandyStoreWithPosition(store_arr, 3, position);
                            cout << "Would you like to enter?(Yes or No)" << endl;
                            getline(cin,input);
                            if (convertToLower(input)=="yes"){
                                //startdiscount
                                cout << "Would you like to try for a 10 percent discount? If fail, you will be overcharged 10 percent." << endl;
                                double discountFactor = 1.0;
                                getline(cin,input);
                                if (convertToLower(input)=="yes"){
                                    if(Unscramble()){
                                        cout << "Congratulations! You earned a 10 percent discount in this store! It will be applied when you buy a candy." << endl;
                                        discountFactor = .9;
                                    } else{
                                        discountFactor = 1.1;
                                    }
                                    
                                }
                                //if (discountFactor!=1.0){cout << "The price of the candy has been affected by a factor of" << discountFactor << endl;}
                                if(visited_store.getName() != ""){
                                    visited_store.displayVector();
                                } 
                                cout << "You have " << players.at(plrselected).getGold() << " gold." << endl;
                                //START THE SHOPPING PROCESS:
                                shopping = true;
                                while(shopping){
                                cout << "Enter the name of Candy to purchase (or EXIT to leave):" << endl;
                                getline(cin,input);
                                    if (convertToLower(input)!="exit"){
                                        bool candyFound = false;
                                        for (int i = 0; i< visited_store.getCandy().size();i++){
                                            if (input==visited_store.getCandy().at(i).name){
                                                candyFound = true;
                                                if(players.at(plrselected).getGold()>=visited_store.getCandy().at(i).price && !players.at(plrselected).isInventoryFull()){
                                                    cout << "Success! Candy has been added to your inventory" << endl;
                                                    if (discountFactor!=1.0){cout << "The price of the candy has been affected by a factor of " << discountFactor << endl;}
                                                    players.at(plrselected).setGold(players.at(plrselected).getGold()-(visited_store.getCandy().at(i).price*discountFactor));
                                                    players.at(plrselected).addCandy(visited_store.getCandy().at(i));
                                                    cout << "You now have " << players.at(plrselected).getGold() << " gold." << endl;
                                                } else {
                                                    cout << "Purchase Failed. Either you don't have enough coins or your inventory is full." << endl;
                                                }
                                            } 
                                        }
                                        if (candyFound==false){
                                          cout << "Candy name not found." << endl;
                                         }
                                    } else{ shopping = false;}
                                }
                            } else{
                                cout << "You have chosen not to enter." << endl;
                            }
                        } if (board.isPositionTreasure(position)){
                            cout << "You found a treasure tile! Would you like to solve a riddle for a reward? (Yes or No)" << endl;
                            getline(cin,input);
                            if (convertToLower(input)=="yes"){
                                Riddle currentRiddle;
                                for (int i = 0;i<sizeof(treasures)/sizeof(treasures[0]);i++){ 
                                    if (treasures[i].getPos()==position){
                                        currentRiddle = treasures[i].getRiddle();
                                    }
                                }
                                cout << currentRiddle.riddle << endl;
                                getline(cin,input);
                                if (input == currentRiddle.answer){
                                    cout << "You answered correctly!" << endl;
                                    board.treasureUsed(position);
                                    //MAKE A FUNCTION FOR THIS IF POSSIBLE
                                    srand(time(0));
                                    int rewardIndex = rand()%10+1;
                                    if (rewardIndex<=3){ //stamina refill
                                        int staminaRefilled = rand()%21+10;
                                        
                                        if (players.at(plrselected).getStamina()+staminaRefilled>maxStamina){
                                            staminaRefilled = 100-players.at(plrselected).getStamina();
                                        }
                                        players.at(plrselected).setStamina(players.at(plrselected).getStamina()+staminaRefilled);
                                        cout << "Your random reward is a Stamina Refill! You have received " << staminaRefilled << " stamina." << endl;
                                    }else if (rewardIndex<=4) {  //gold windfall
                                        int goldBonus = rand()%21+20;
                                        
                                        if (players.at(plrselected).getGold()+goldBonus>maxGold){
                                            goldBonus = 100-players.at(plrselected).getGold();
                                        }
                                        players.at(plrselected).setGold(players.at(plrselected).getGold()+goldBonus);
                                        cout << "Your random reward is a Gold Windfall! You have received " << goldBonus << " gold." << endl;
                                    }else if (rewardIndex<=7) { //robber's repel
                                        cout << "Your random reward is a Robbers' Repel!" << endl;
                                        players.at(plrselected).giveRR();
                                    }else if (rewardIndex<=10) { // candy acquisition
                                        cout << "Your random reward is a Candy Acquisition!" << endl;
                                        if (rand()%9+1<=7){
                                            cout << "You have received a Jellybean of Vigor." << endl;
                                            players.at(plrselected).addCandy(vigorjellybean);
                                        } else {
                                            cout << "You have received a Treasure Hunter's Truffle." << endl;
                                            players.at(plrselected).addCandy(treasureTruffle);
                                        }
                                    }
                                } else{
                                    cout << "Sorry, wrong answer." << endl;
                                }
                            } else {cout << "You have chosen not to solve the riddle." << endl;}
                        } 
                        //SAME TILE CONSTRAINTS
                        int sametileplr = -1;
                        for (int i = 0; i < players.size();i++){
                            if(board.getPlayerPosition(i)==position&&i!=plrselected){
                                sametileplr = i;
                            }
                        } if (sametileplr != -1&&position!=1){ 
                            cout << "You've landed on the same tile as another player!" << endl;
                            srand(time(0));
                            int goldstolen = rand()%26+5;
                            if (!players.at(plrselected).hasRR()){
                                
                                if (players.at(plrselected).getGold()-goldstolen<0){
                                    goldstolen = players.at(plrselected).getGold();
                                }
                                cout << "You've lost " << goldstolen << " gold and will be sent 1 tile back." << endl;
                                if (players.at(sametileplr).getGold()+goldstolen>100){
                                    players.at(sametileplr).setGold(100);
                                } else{
                                    players.at(sametileplr).setGold(players.at(sametileplr).getGold()+goldstolen);
                                }
                                players.at(plrselected).setGold(players.at(plrselected).getGold()-goldstolen);
                            } else {
                                cout << "You were protected by the Robbers' Repel." << endl;
                            }
                            moves = -1;
                            goto startAtMove;
                        }
                        Special_Tile spectile = board.getSpecialTile(position);
                        //cout << "Debug223--" << spectile.tile_num << "--" << spectile.special_type << endl; 
                        if (spectile.tile_num!=-1){
                            //cout << "Is this shit being run?" << endl;
                            switch(spectile.special_type){
                                case(0): //shortcut | Move 4 tiles then go back as if you just landed
                                    
                                    cout << "This tile is a shortcut tile! Would you like to leap forward 4 tiles? (Yes or No)" << endl;
                                    getline(cin,input);
                                    if (convertToLower(input)=="yes"){
                                        cout << "You taken a shortcut!" << endl;
                                        moves=4;
                                        if (moves + position > 83){
                                            moves = 83 - position;
                                        }
                                        goto startAtMove;
                                    } else {cout << "You have chosen not to take the shortcut." << endl;}
                                    break;
                                case(1): //icecream
                                    cout << "This tile is an Ice Cream Stop Tile! You may draw another card." << endl;
                                    board.displayBoard(); 
                                    goto startNewDraw;
                                    break;
                                case(2): //gumdrop
                                    srand(time(0));
                                    goldlost = (rand()%6)+5;
                                    cout << "This tile is a Gumdrop Forest Tile! You fell back 4 tiles and lost " << goldlost << " gold!" << endl;
                                    tempval = players.at(plrselected).getGold()-goldlost;
                                    if (tempval<0){tempval=0;}
                                    players.at(plrselected).setGold(tempval);
                                    moves=-4;
                                    if (moves + position < 1){
                                        moves = -position+1;
                                    }
                                    goto startAtMove;
                                    break;
                                case(3): //gingerbread
                                    cout << "This tile is an Gingerbread House Tile!" << endl;
                                    vector<Candy> foundCandies = players.at(plrselected).findCandyByType("immunity");
                                    if (foundCandies.size()>0){
                                        
                                        int minIndex=0;
                                        for (int i = 0; i < foundCandies.size();i++){ // for each immunity candy
                                            if (foundCandies.at(minIndex).effect_value<foundCandies.at(i).effect_value){ // make sure the effect is enough
                                                minIndex = i;
                                            }
                                            
                                        }
                                        players.at(plrselected).removeCandy(foundCandies.at(minIndex).name);
                                        cout << "You've been sent back to your previous position and lost an immunity candy!" << endl;
                                        moves = -1*moves;
                                        goto startAtMove;
                                        // SEND PLAYER BACK
                                    } else{
                                        cout << "Since you don't have any immunity candies, there is no effect." << endl;
                                    }
                                    
                                    //MY THINKING: IF you hit a gumdrop and go back 4 to hit gingerbread, then this sends u to gumdrop, then send it back one more time and if the player has no more gummies then dont activate this tile.
                                    break;
                            }
                            /**PUT CODE HERE*/
                        } else if (spectile.tile_num==-1){ // GENERATE RANDOM NUMBER FOR CALAMITY CHANCE
                            srand(time(0));
                            if (rand()%5+1<=2){
                                cout << "A Calamity has occured!" << endl;
                                int calamityChance = rand()%99 + 1;
                                if (calamityChance<=30){
                                    cout << "Oh no! Candy Bandits have swiped your gold coins!" << endl;
                                    int goldstolen = rand()%10+1;
                                    if (players.at(plrselected).getGold()-goldstolen<0){
                                            goldstolen = players.at(plrselected).getGold();
                                    }
                                    cout << "You lost " << goldstolen <<" gold." << endl;
                                    players.at(plrselected).setGold(players.at(plrselected).getGold()-goldstolen);

                                } else if (calamityChance<=65){
                                    cout << "Oh dear! You got lost in the lollipop labyrinth!" << endl;
                                    cout << "You may play rock paper scissors to get back your lost turn." << endl;
                                    if(players.at(plrselected).playRockPaperScissors()){
                                        cout << "You recovered your turn." << endl;
                                    } else{
                                        cout << "You next turn remains skipped." << endl;
                                        players.at(plrselected).skipTurn(1);
                                    }

                                } else if (calamityChance<=80) {
                                    int stamlost = rand()%5+5;
                                    if (players.at(plrselected).getStamina()<stamlost){
                                        stamlost = players.at(plrselected).getStamina();
                                    }
                                    cout << "Watch out! A candy avalanche has struck! You lost a turn and " << stamlost << " stamina!" << endl;
                                    cout << "You may play rock paper scissors to get back your stamina." << endl;
                                    if(players.at(plrselected).playRockPaperScissors()){
                                        cout << "You recovered your stamina." << endl;
                                    } else{
                                        cout << "You next stamina remains lost." << endl;
                                        players.at(plrselected).setStamina(players.at(plrselected).getStamina()-stamlost);
                                    }
                                    players.at(plrselected).skipTurn(1);
                                } else if (calamityChance<=100){
                                    cout << "Oops! You are stuck in a sticky taffy trap!" << endl;
                                    vector<Candy> magicalAmount = players.at(plrselected).findCandyByType("magical");
                                    if(magicalAmount.size()>0){
                                        cout << "Would you like to use a magical candy to save your next turn?(Yes or No)" << endl;
                                        getline(cin,input);
                                        
                                        if (convertToLower(input)=="yes"){
                                            int minIndex = 0;
                                            for (int i = 0; i < magicalAmount.size();i++){
                                                if (magicalAmount.at(minIndex).effect_value<magicalAmount.at(i).effect_value){
                                                    minIndex = i;
                                                }
                                            }
                                            cout << "Your weakest magical candy has been used." << endl;
                                            players.at(plrselected).removeCandy(magicalAmount.at(minIndex).name);
                                        } else {
                                            cout << "Your next turn will be skipped." << endl;
                                            players.at(plrselected).skipTurn(1);
                                        }
                                    } else {
                                            cout << "Your next turn will be skipped." << endl;
                                            players.at(plrselected).skipTurn(1);
                                    }
                                }
                            }
                        } 
                        if (rand()%100+1<=5){
                            srand(time(0));
                            cout << "A marshmallow hailstorm activated!" << endl;
                            int moveamount = -(rand()%3+1);
                            for (int i = 0; i<players.size();i++){
                                
                                if(board.getPlayerPosition(i)+moveamount<1){
                                    board.movePlayer(1-board.getPlayerPosition(i),i);
                                } else{
                                board.movePlayer(moveamount,i);
                                }
                            }
                            cout << "All players have been pushed back by " << -moveamount << "."<< endl;
                        }
                    
                        //board.displayBoard(); // PUT HERE TO FIX ISSUE WITH SEEING MARKET AFTER MOVING PAST. MIGHT HAVE ISSUES WITH UPDATING BOARD FROM OTHER THINGS!
                        //check for special tiles, do a calamity chance for regular tiles, same tile constraints
                        //check for gummy candies <-- Done
                    }
                    else {
                        cout << "Player " << plrselected + 1 << " made it to the end!" << endl;
                        cout << "End of Board" << endl;
                        board.displayBoard();
                        runGame = false;
                        writeGameStats(players.at(plrselected).getPlrName(),allturns);
                        break; // CAREFUL, MAY NEED TO BREAK OUT OF BOTH LOOPS
                    }
                    
                    break;
                case(2):
                    /**
                     * 
                     *  USE CANDY
                     * 
                    */
                    match = false;
                    cout << "Here is a list of your candies:" << endl;
                    players.at(plrselected).printInventory();
                    cout << endl;
                    
                    while(!match&&players.at(plrselected).getCandyAmount()>0){
                        cout << "Enter a candy you wish to use:" << endl;
                        getline(cin,input);
                        Candy compare = players.at(plrselected).findCandy(input);
                        if (compare.candy_type=="magical"){
                            match = true;
                            players.at(plrselected).setStamina(players.at(plrselected).getStamina()+compare.effect_value);
                            players.at(plrselected).removeCandy(compare.name);
                            cout << "You have used a " << compare.name << " candy. This has increased your stamina by " << compare.effect_value << " to " << players.at(plrselected).getStamina() << endl;
                        } else if(compare.candy_type=="poison"){
                            match = true;
                            bool validplr = false;
                            int target = 0;
                            Candy usedCandy;
                            while (!validplr){
                                cout << "Which player would you like to use a " << compare.name << " candy on?" << endl;
                                getline(cin,input);
                                for (int i = 0;i<players.size();i++){
                                    if (input == players.at(plrselected).getPlrName()){
                                        validplr = false;
                                        break;
                                    } else if (input == players.at(i).getPlrName()){
                                        target = i;
                                        validplr = true;
                                        break;
                                    } else {
                                        validplr = false;
                                    }
                                }
                                if (validplr){
                                    vector<Candy> foundCandies = players.at(target).findCandyByType("immunity");
                                    if (foundCandies.size()>0){
                                        
                                        int minIndex=-1;
                                        int testnum;
                                        for (int i = 0; i < foundCandies.size();i++){ // for each immunity candy
                                            testnum = foundCandies.at(i).effect_value;
                                            if (((pow(testnum,2))+4)*2 >= abs(compare.effect_value)){ // make sure the effect is enough
                                                if (minIndex == -1) {
                                                    minIndex = i;
                                                } else if (foundCandies.at(i).effect_value<foundCandies.at(minIndex).effect_value) {
                                                    minIndex = i;
                                                }
                                            } 
                                            // 1,2,3 --- 2,3,4 --- 4,6,8
                                            // 1,2,3 -^2- 1,4,9 -+4-- 5,9,13 -*2- 10, 18, 26
                                            
                                        }
                                        if (minIndex==-1){
                                            players.at(target).setStamina(players.at(target).getStamina()+compare.effect_value);
                                            cout << "You have successfully used a " << compare.name << " candy on " << players.at(target).getPlrName() << endl;
                                        } else {
                                            cout << "You have used a " << compare.name << " candy but your opponent has " << foundCandies.at(minIndex).name << " to protect against your poison candy" << endl;
                                            players.at(target).removeCandy(foundCandies.at(minIndex).name);
                                        }
                                        
                                    } else{
                                        players.at(target).setStamina(players.at(target).getStamina()+compare.effect_value);
                                        cout << "You have successfully used a " << compare.name << " candy on " << players.at(target).getPlrName() << endl;
                                    }
                                    players.at(plrselected).removeCandy(compare.name);
                                } else {
                                    cout << "Invalid player!" << endl;
                                }
                            }

                        }else if(compare.candy_type=="immunity"){
                            cout << "This candy is a passive candy." << endl; 
                            match = true;
                        }else if(compare.candy_type=="gummy"){
                            cout << "On which tile would you like to place your " << compare.name << " - gummy candy?" << endl;
                            getline(cin,input);
                            tileplace = stoi(input);
                            //You have successfully placed gummy candy on tile 12. Any player that lands on the gummy tile will be obstructed from advancing past the tile for two moves.
                            if (tileplace > 1 && tileplace < 83){
                                //
                                if(!board.addGummyTile(plrselected,tileplace,compare.effect_value)){
                                    cout << "This tile is occupied by another gummy candy!" << endl;
                                } else {
                                        players.at(plrselected).removeCandy(compare.name);
                                        cout << "You have successfully used a " << compare.name << " candy on tile " << tileplace << endl;
                                }
                            }
                            match = true;
                        } else if(compare.candy_type=="treasure"){
                            match = true;
                            players.at(plrselected).removeCandy(compare.name);
                            cout << "You have activated a Treasure candy! Would you like to solve a riddle?" << endl;
                            getline(cin,input);
                            if (convertToLower(input)=="yes"){
                                Riddle currentRiddle = tempriddle.at(rand()%tempriddle.size());
                                cout << currentRiddle.riddle << endl;
                                getline(cin,input);
                                if (input == currentRiddle.answer){
                                    cout << "You answered correctly!" << endl;
                                    //MAKE A FUNCTION FOR THIS IF POSSIBLE
                                    srand(time(0));
                                    int rewardIndex = rand()%10+1;
                                    if (rewardIndex<=3){ //stamina refill
                                        int staminaRefilled = rand()%21+10;
                                        
                                        if (players.at(plrselected).getStamina()+staminaRefilled>maxStamina){
                                            staminaRefilled = 100-players.at(plrselected).getStamina();
                                        }
                                        players.at(plrselected).setStamina(players.at(plrselected).getStamina()+staminaRefilled);
                                        cout << "Your random reward is a Stamina Refill! You have received " << staminaRefilled << " stamina." << endl;
                                    }else if (rewardIndex<=4) {  //gold windfall
                                        int goldBonus = rand()%21+20;
                                        
                                        if (players.at(plrselected).getGold()+goldBonus>maxGold){
                                            goldBonus = 100-players.at(plrselected).getGold();
                                        }
                                        players.at(plrselected).setGold(players.at(plrselected).getGold()+goldBonus);
                                        cout << "Your random reward is a Gold Windfall! You have received " << goldBonus << " gold." << endl;
                                    }else if (rewardIndex<=7) { //robber's repel
                                        cout << "Your random reward is a Robbers' Repel!" << endl;
                                        players.at(plrselected).giveRR();
                                    }else if (rewardIndex<=10) { // candy acquisition
                                        cout << "Your random reward is a Candy Acquisition!" << endl;
                                        if (rand()%9+1<=7){
                                            cout << "You have received a Jellybean of Vigor." << endl;
                                            players.at(plrselected).addCandy(vigorjellybean);
                                        } else {
                                            cout << "You have received a Treasure Hunter's Truffle." << endl;
                                            players.at(plrselected).addCandy(treasureTruffle);
                                        }
                                    }
                                } else{
                                    cout << "Sorry, wrong answer." << endl;
                                }
                            } else {cout << "You have chosen not to solve the riddle." << endl;}
                            
                        } else {
                            cout << "You do not have this candy!" << endl;
                        }
                        //for (int i = 0; i<playe)//if (input == )
                    } if (players.at(plrselected).getCandyAmount()<=0){
                        cout << "You have no candy in your inventory!" << endl;
                    }
                    break;
                case(3):
                    /**
                     * 
                     *  PRINT PLAYER STATS
                     * 
                    */
                    cout << "Here are your stats:" << endl;
                    cout << "Player name: " << players.at(plrselected).getPlrName() << endl
                    << "Character: " << players.at(plrselected).getCharName() << endl
                    << "Stamina: " << players.at(plrselected).getStamina() << endl
                    << "Gold: " << players.at(plrselected).getGold() << endl
                    << "Candies: " << endl;
                    players.at(plrselected).printInventory(); 
                    break;
                case(4):
                    cout << "Player " << plrselected + 1 << " force won the game!" << endl;
                    cout << "End of Board" << endl;
                    board.displayBoard();
                    plrTurn = false;
                    runGame = false;
                    writeGameStats(players.at(plrselected).getPlrName(),allturns);
                    break; // CAREFUL, MAY NEED TO BREAK OUT OF BOTH LOOPS1

                default:
                    cout << "Invalid Option" << endl;
                    break;
            }
        }
        } else{
            cout << "Your turn was skipped because you got stuck!!!!!" << endl;
            players.at(plrselected).skipTurn(-1);
        }

        plrselected++;
    }
    /*
    
    
    Create candy store 1 => at position 24
    Create candy store 2 => at position 53
    Create candy store 3 => at position 75
    
    Add candy store 1 at 24
    add cstore 2 at 53
    add cstore 3 at 75

    while true
        display board
        ask user how many tiles to move
        move player
        get player position
        Check if player position is a store
        - if player pos is store pos 1
            print all in store 1
        - elif player pos is store pos 2
            print all in store 2
        - elif player pos is store pos 3
            print all in store 3
    
    */
    return 0;
}