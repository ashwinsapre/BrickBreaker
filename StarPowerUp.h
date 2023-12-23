// StarPowerUp.h
#ifndef STARPOWERUP_H
#define STARPOWERUP_H

#include "PowerUp.h"

class StarPowerUp : public PowerUp {
public:
    sf::Texture starTexture;
    StarPowerUp(float size);

    // Add additional functions or properties specific to StarPowerUp
};

#endif // STARPOWERUP_H
