//
// Created by hp on 10/23/2024.
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
}

GameRecord::~GameRecord() { // destructor
    std::cout << "\nDestructor called";
}

void GameRecord::display() const{
    for(int i = 0; i < entries.size(); i++)
    {
        std::cout << entries[i].getName() << " " << entries[i].getScore();
        std::cout << std::endl;
    }
}

bool GameRecord::check_remove_duplicate(const GameEntry& e)
{
    for(int i = 0; i < entries.size(); i++)     // 0.5 mk
    {
        if(entries[i].getName() == e.getName() && e.getScore() > entries[i].getScore())     // 0.5 mk
        {
            entries.erase(entries.begin() + i);     // 0.5 mk
            return true;                                     // 0.5 mk
        }
        // 0.5 mk
        if(entries[i].getName() == e.getName() && e.getScore() <= entries[i].getScore())
            return false;
    }

    return true;                                            // 0.5 mk
}

void GameRecord::add(const GameEntry& e)
{
    // 0.5 mk
    if(!check_remove_duplicate(e))
        return;
    int e_score = e.getScore();
    // 0.5 mk
    if(entries.size() == maxEntries && e_score < entries[entries.size() - 1].getScore())
    {
        std::cout << "Nothing to place, the high score of " << e.getName() << " is not high enough" << '\n';
        return;
    }

    bool inserted = false;
    for(int it = 0; it < entries.size(); it++)                      // 0.5 mk
    {
        if(e_score > entries.at(it).getScore())                     // 0.5 mk
        {
            entries.insert(entries.begin() + it, e);       // 0.5 mk
            // 0.5 mk
            inserted = true;
            break;
        }
    }
    if(!inserted)                           // 0.5 mk
        entries.push_back(e);               // 0.5 mk
    // 0.5 mk
    if(entries.size() > maxEntries)
        entries.pop_back();
}