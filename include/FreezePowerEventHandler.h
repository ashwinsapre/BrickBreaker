#ifndef FREEZE_POWER_EVENT_HANDLER_H
#define FREEZE_POWER_EVENT_HANDLER_H

#include "EventHandler.h"
#include "Event.h"

class FreezePowerEventHandler : public EventHandler {
public:
    void onEvent(Event* e) override;
};

#endif // FREEZE_POWER_EVENT_HANDLER_H
