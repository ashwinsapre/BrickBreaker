#ifndef COLLISION_EVENT_HANDLER_H
#define COLLISION_EVENT_HANDLER_H

#include "EventHandler.h"
#include "Event.h"

class CollisionEventHandler : public EventHandler{
public:
	void onEvent(Event *e);
};

#endif