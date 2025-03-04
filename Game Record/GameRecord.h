//
// Created by hp on 10/23/2024.
//

#ifndef GAMERECORD_H
#define GAMERECORD_H
#include <string>
#include <vector>
using namespace std;

class GameEntry { // a game score entry
public:
    GameEntry(const std::string& n="", int s=0); // constructor
    std::string getName() const; // get player name
    int getScore() const; // get score
private:
    std::string name; // player’s name
    int score; // player’s score
};

class GameRecord { // stores game high scores
public:
    GameRecord(int maxEnt = 10); // constructor
    ~GameRecord(); // destructor
    void add(const GameEntry& e); // add a game entry
    void display() const;
private:
    int maxEntries; // maximum number of entries
    bool check_remove_duplicate(const GameEntry& e); // remove duplicate
    vector<GameEntry> entries; // array of game entries
};

#endif //GAMERECORD_H
