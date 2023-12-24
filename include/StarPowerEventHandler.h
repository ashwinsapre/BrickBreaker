#ifndef STARPOWER_EVENT_HANDLER_H
#define STARPOWER_EVENT_HANDLER_H

#include "EventHandler.h"
#include "Event.h"

class StarPowerEventHandler : public EventHandler {
public:
    // Override the onEvent function from the base class
    void onEvent(Event* e) override;

    // Add any additional member functions or variables if needed
};

#endif // STARPOWER_EVENT_HANDLER_H
