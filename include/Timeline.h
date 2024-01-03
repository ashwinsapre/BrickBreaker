#ifndef TIMELINE_H
#define TIMELINE_H

#include <SFML/System.hpp>

class Timeline{
public:
    bool isPaused = false;
    bool isFrozen = false;
    float start_time;
    float current_time;
    float tic;
    float paused_time_total = 0.f;
    float last_paused_time = 0.f;
    float last_frozen_time = 0.f;
    float freeze_time = 0.f;
    sf::Clock clock;

    Timeline(sf::Clock c, float ticSize);

    float getCurrentTime();

    void changeTicSize(float t);

    void pause();

    void unpause();

    void reset();

    void freeze();

    void unfreeze();
};

#endif // TIMELINE_H
