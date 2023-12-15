#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>
#include <vector>
#include "EventHandler.h"
#include "Event.h"

class EventManager {
public:
    std::map<int, std::vector<EventHandler*>> mappings;
    std::vector<Event*> eventsList;

    EventManager();

    void reg(int i, EventHandler* eh);
    void dereg();
    void enqueue(Event *e);
    void raise(Event* e);
};

#endif // EVENTMANAGER_H
