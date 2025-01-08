//
// Created by hp on 23/Oct./2024.
//

#ifndef GAMERECORD_H
#define GAMERECORD_H
#include <string>

class GameEntry { // a game score entry
public:
    GameEntry(const std::string& n="", int s=0); // constructor
    std::string getName() const; // get player name
    int getScore() const; // get score
    //void setName(std::string n); // set player name
    //void setScore(int s); // set score
private:
    std::string name; // player’s name
    int score; // player’s score
};

class GameRecord { // stores game high scores
public:
    GameRecord(int maxEnt = 10); // constructor
    ~GameRecord(); // destructor
    void add(const GameEntry& e); // add a game entry
    GameEntry remove(int i); // remove the ith entry
    void display() const;
private:
    int maxEntries; // maximum number of entries
    int numEntries; // actual number of entries
    GameEntry* entries; // array of game entries
};

#endif //GAMERECORD_H
