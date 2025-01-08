//
// Created by hp on 23/Oct./2024.
//
#include <iostream>
#include "GameRecord.h"

GameEntry::GameEntry(const std::string& n, int s) { name = n; score = s;}
std::string GameEntry::getName() const { return name; }
int GameEntry::getScore() const { return score; }
//void GameEntry::setName(std::string n) { name = n; }
//void GameEntry::setScore(int s) { score = s; }

GameRecord::GameRecord(int maxEnt) { // constructor
    maxEntries = maxEnt; // save the max size
    entries = new GameEntry[maxEntries]; // allocate array storage
    numEntries = 0; // initially no elements
}

GameRecord::~GameRecord() { // destructor
    delete[] entries;
}

void GameRecord::display() const{
    for(int i = 0; i < numEntries; i++)
    {
        std::cout << entries[i].getName() << " " << entries[i].getScore();
        std::cout << std::endl;
    }
}

void GameRecord::add(const GameEntry& e)
{
    int e_score = e.getScore();
    if(numEntries == maxEntries && e_score < entries[numEntries - 1].getScore())
    {
        std::cout << "Nothing to place, the high score of the player is not high enough" << std::endl;
        return;
    }
    int it = 0; // iterator
    while(e_score < entries[it].getScore())
        it++;
    int pos_to_place_record = it;
    for(int i = numEntries; i >= pos_to_place_record + 1; i--) // shift previous entries
    {
        if(i == maxEntries) continue; // avoid access of an 'out of bounds' index
        entries[i] = entries[i-1];
    }
    entries[pos_to_place_record] = e; // place the new entry into the game record.
    if(numEntries + 1 <= maxEntries) // check if we have reached maximum capacity.
        numEntries++;
}
