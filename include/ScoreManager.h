// ScoreManager.h
#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <vector>
#include <fstream>
#include "Score.h"

class ScoreManager {
public:
    std::vector<Score> scores;

    std::vector<Score>* loadScores();
    void saveScore(const Score& score);
    void displayScores();
};

#endif
