#include "FreezePowerUp.h"

FreezePowerUp::FreezePowerUp(float size) : PowerUp(size) {
    if (freezeTexture.loadFromFile("../assets/clock.png")) {
        setTexture(&freezeTexture);
    }
}
