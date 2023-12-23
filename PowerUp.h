// PowerUp.h
#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>

class PowerUp : public sf::CircleShape {
private:
    sf::Clock durationTimer;
    

public:
    bool isActive;
    PowerUp(float size);

    // Function to set the power-up
    void setPowerUp();

    // Function to reset the power-up
    void resetPowerUp();

    // Function to check if the power-up is currently active
    bool isActivePowerUp() const;
};

#endif // POWERUP_H
