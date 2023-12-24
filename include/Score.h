// Score.h
#ifndef SCORE_H
#define SCORE_H

#include <string>

class Score {
public:
    std::string playerName;
    int scoreValue;

    Score(const std::string& name, int score) : playerName(name), scoreValue(score) {}
};

#endif
