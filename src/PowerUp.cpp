// PowerUp.cpp
#include "PowerUp.h"
#include <iostream>

PowerUp::PowerUp(float size) : sf::CircleShape(size) {
    // Initialize the power-up properties
    isActive = false;
}
PowerUp::~PowerUp(){
    std::cout<<"Destructor\n";
}

void PowerUp::setPowerUp() {
    if (!isActive) {
        isActive = true;
        durationTimer.restart();
        // Set appearance or perform other actions when the power-up is activated
    }
}

void PowerUp::resetPowerUp() {
    if (isActive && durationTimer.getElapsedTime().asSeconds() > 10.f) {
        isActive = false;
        // Reset appearance or perform other actions when the power-up is deactivated
    }
}

bool PowerUp::isActivePowerUp() const {
    return isActive;
}
