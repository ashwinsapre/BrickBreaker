// ScoreManager.h
#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <vector>
#include <fstream>
#include "Score.h"

class ScoreManager {
public:
    std::vector<Score> scores;

    void loadScores();
    void saveScore(const std::string& playerName, int score);
    void displayScores();
};

#endif
