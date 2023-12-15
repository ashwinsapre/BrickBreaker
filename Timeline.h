#ifndef TIMELINE_H
#define TIMELINE_H

#include <SFML/System.hpp>

class Timeline{
public:
    float start_time;
    float current_time;
    float tic;
    float elapsed_paused_time;
    float last_paused_time;
    bool isPaused;
    sf::Clock clock;

    Timeline(sf::Clock c, float ticSize);

    float getCurrentTime();

    void changeTicSize(float t);

    void pause();

    void unpause();
};

#endif // TIMELINE_H
