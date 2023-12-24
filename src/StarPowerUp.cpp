// StarPowerUp.cpp
#include "StarPowerUp.h"

StarPowerUp::StarPowerUp(float size) : PowerUp(size) {
    if (starTexture.loadFromFile("../assets/star.png")) {
        setTexture(&starTexture);
    }
}
