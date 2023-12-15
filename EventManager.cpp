#include "EventManager.h"

EventManager::EventManager() {
    // Constructor implementation, if any
}

void EventManager::reg(int i, EventHandler* eh) {
    this->mappings[i].push_back(eh);
}

void EventManager::dereg() {
    // Deregistration implementation, if any
    return;
}

void EventManager::enqueue(Event *e) {
    this->eventsList.push_back(e);
}

void EventManager::raise(Event* e) {
    // Call all event handlers that have registered for this event type
    int event_type = e->type;
    for (int i = 0; i < this->mappings[event_type].size(); i++) {
        this->mappings[event_type][i]->onEvent(e);
    }
}
