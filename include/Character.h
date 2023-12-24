#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "json.hpp"
// class Game;
#include "Game.h"
using namespace nlohmann;

class Character : public Game, public sf::CircleShape {
public:
    sf::Vector2f velocity;
    Character *next;
    sf::Vector2f addPosition;
    sf::Vector2f addSpeed;
    bool isAlive = true;

    float x;
    float y;
    float xvel=1;
    float yvel=1;
    int length;
    float maxVel = 0.2f;

    sf::Color color;
    sf::Texture power;

    Character(float size);
    Character(float size, int length);

    void parseTarget(std::string s);
    
    json serialize();
    void deserialize();

    void setPower();
    void resetPower();

    void setPos(float x, float y);
    void setColor(sf::Color c);

    void resetYVelocity();
    void resetXVelocity();

    void movement(const float dirx, const float diry);

    void physics(float dt);
    void propagate(float x, float y);

    void collisions();
    void grow();
};

#endif // CHARACTER_H
