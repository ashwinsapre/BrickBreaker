#include "Character.h"
#include <iostream>
using namespace nlohmann;

Character::Character(float size) {
    setRadius(size);
    isAlive = true;
    velocity = sf::Vector2f(0, 0);
}
Character::Character(float size, int length): length(length){
    velocity = sf::Vector2f(0, 0);
    setRadius(size);
}

void Character::setColor(sf::Color c){
    setFillColor(c);
}

void Character::setPos(float x, float y) {
    setPosition(x, y);
}
void Character::parseTarget(std::string s){
    //std::cout<<"received: "<<s<<std::endl;
    if (s=="nothing"){
        return;
    }
    std::vector<float> coords;
    std::istringstream stream(s);
    std::string temp;

    while (std::getline(stream, temp, '-')) {
        coords.push_back(std::stoi(temp));
    }
    std::cout<<coords.size()<<std::endl;
    setPos(coords[0], coords[1]);
    
}

void Character::movement(const float dirx, const float diry) {
    velocity.x = dirx * xvel;
    velocity.y = diry * yvel;
}

void Character::physics(float dt) {
    if (velocity.x < -maxVel){
		velocity.x = -maxVel;
	}
    if (velocity.x > maxVel){
        velocity.x = maxVel;
    }
    if (velocity.y < -maxVel){
		velocity.y = -maxVel;
	}
    if (velocity.y > maxVel){
        velocity.y = maxVel;
    }
    move(velocity);
}

void Character::collisions() {
    
}
