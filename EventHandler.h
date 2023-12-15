#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Event.h"

class EventHandler {
public:
    virtual void onEvent(Event* e) = 0;
};

#endif // EVENT_HANDLER_H
