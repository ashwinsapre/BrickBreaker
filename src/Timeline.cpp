#include "Timeline.h"

Timeline::Timeline(sf::Clock c, float ticSize) {
    this->clock = c;
    this->isPaused = false;
    this->tic = ticSize;
    this->start_time = 0;
    freeze_time = 0.f;
    paused_time_total = 0.f;
    // Set to start of anchor later
}

float Timeline::getCurrentTime() {
    if (isPaused) {
        return last_paused_time;
    } else {
        return clock.getElapsedTime().asSeconds() - paused_time_total;
    }
}


void Timeline::changeTicSize(float t) {
    this->tic = t;
}

void Timeline::pause() {
    if (!isPaused) {
        last_paused_time = clock.getElapsedTime().asSeconds();
        isPaused = true;
    }
}

void Timeline::unpause() {
    if (isPaused) {
        float now = clock.getElapsedTime().asSeconds();
        paused_time_total += now - last_paused_time;
        isPaused = false;
    }
}

void Timeline::reset(){
    clock.restart();
    last_paused_time = 0.f;
    paused_time_total = 0.f;
    start_time = 0;
    isPaused = false;
}

void Timeline::freeze(){
    freeze_time = getCurrentTime();
}

void Timeline::unfreeze(){

}


