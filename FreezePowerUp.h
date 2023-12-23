#ifndef FREEZE_POWER_UP_H
#define FREEZE_POWER_UP_H

#include "PowerUp.h"
#include "Event.h"

class FreezePowerUp : public PowerUp {
public:
    sf::Texture freezeTexture;
    FreezePowerUp(float size);
};

#endif // FREEZE_POWER_UP_H
