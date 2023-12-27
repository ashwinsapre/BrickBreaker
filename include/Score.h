// Score.h
#ifndef SCORE_H
#define SCORE_H

#include <string>

class Score {
public:
    std::string playerName;
    float scoreValue;

    Score(const std::string& name, float score) : playerName(name), scoreValue(score) {}
};

#endif
