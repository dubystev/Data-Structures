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
    for(int i = 0; i < entries.size(); i++)
    {
        if(entries[i].getName() == e.getName() && e.getScore() > entries[i].getScore())
        {
            entries.erase(entries.begin() + i);
            return true;                       
        }
        
        if(entries[i].getName() == e.getName() && e.getScore() <= entries[i].getScore())
            return false;
    }

    return true;                                       
}

void GameRecord::add(const GameEntry& e)
{
    if(!check_remove_duplicate(e))
        return;
    int e_score = e.getScore();
    if(entries.size() == maxEntries && e_score < entries[entries.size() - 1].getScore())
    {
        std::cout << "Nothing to place, the high score of " << e.getName() << " is not high enough" << '\n';
        return;
    }

    bool inserted = false;
    for(int it = 0; it < entries.size(); it++)                      
    {
        if(e_score > entries.at(it).getScore())                     
        {
            entries.insert(entries.begin() + it, e);       
            inserted = true;
            break;
        }
    }
    if(!inserted) 
        entries.push_back(e);       
    if(entries.size() > maxEntries)
        entries.pop_back();
}
