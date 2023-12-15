#include "Event.h"
#include "json.hpp"
using namespace nlohmann;

Event::Event(int i, float newX, float newY) {\
    this->type = i;
    this->x = newX;
    this->y = newY;
    ball = NULL;
}

Event::Event(int i, float newX, float newY, float offset, Character *s) {
    this->type = i;
    this->x = newX;
    this->y = newY;
    this->offset = offset;
    ball = s;
}