#ifndef EVENT_H
#define EVENT_H

#include "json.hpp"
class Character;
using namespace nlohmann;

class Event {
public:
    int type;
    float x;
    float y;
    float offset;
    Character *ball;

    //1: COLLISION
    //2: EXIT
    Event(int i, float newX, float newY);
    Event(int i, float newX, float newY, float offset, Character *s);
    json serialize();
};

#endif // EVENT_H
