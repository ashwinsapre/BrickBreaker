#include "FreezePowerUp.h"

FreezePowerUp::FreezePowerUp(float size) : PowerUp(size) {
    if (freezeTexture.loadFromFile("./Assets/clock.png")) {
        setTexture(&freezeTexture);
    }
}
