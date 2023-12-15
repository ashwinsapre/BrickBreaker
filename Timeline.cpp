#include "Timeline.h"

Timeline::Timeline(sf::Clock c, float ticSize) {
    this->isPaused = false;
    this->clock = c;
    this->tic = ticSize;
    this->start_time = 0;
    // Set to start of anchor later
}

float Timeline::getCurrentTime() {
    return (clock.getElapsedTime().asSeconds() - this->start_time) / this->tic;
}

void Timeline::changeTicSize(float t) {
    this->tic = t;
}

void Timeline::pause() {
    this->isPaused = true;
    last_paused_time = this->getCurrentTime();
}

void Timeline::unpause() {
    this->isPaused = false;
}
