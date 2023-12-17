#include "Timeline.h"

Timeline::Timeline(sf::Clock c, float ticSize) {
    this->clock = c;
    this->isPaused = false;
    this->tic = ticSize;
    this->start_time = 0;
    // Set to start of anchor later
}

float Timeline::getCurrentTime() {
    if (isPaused) {
        return last_paused_time;
    } else {
        return (clock.getElapsedTime().asSeconds() - paused_time_total);
    }
}

void Timeline::changeTicSize(float t) {
    this->tic = t;
}

void Timeline::pause() {
    if (!isPaused) {
        last_paused_time = getCurrentTime();
        isPaused = true;
    }
}

void Timeline::unpause() {
    if (isPaused) {
        float now = clock.getElapsedTime().asSeconds();
        paused_time_total += now - last_paused_time;
        last_paused_time = now;  // Update last_paused_time to the current time
        isPaused = false;
    }
}

