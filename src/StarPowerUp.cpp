// StarPowerUp.cpp
#include "StarPowerUp.h"

StarPowerUp::StarPowerUp(float size) : PowerUp(size) {
    if (starTexture.loadFromFile("./Assets/star.png")) {
        setTexture(&starTexture);
    }
}
