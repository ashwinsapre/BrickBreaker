// ScoreManager.cpp
#include "ScoreManager.h"
#include <iostream>

void ScoreManager::loadScores() {
    std::cout<<"Loading scores\n";
}

void ScoreManager::saveScore(const std::string& playerName, int score) {
    std::cout<<"Saved score "<<score<<" for player "<<playerName<<std::endl;
}

void ScoreManager::displayScores() {
    // Display scores on the start screen
}
