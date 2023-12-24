#include "StarPowerEventHandler.h"
#include "Character.h"
#include <iostream>

// Implement the onEvent function
void StarPowerEventHandler::onEvent(Event* e) {
    if (e->offset==1){
        e->ball->setFillColor(sf::Color::Yellow);
        std::cout<<"Star power!\n";
    }
    else{
        e->ball->setFillColor(sf::Color::White);
        std::cout<<"Star power reset!\n";
    }
   
}

// Implement additional member functions if needed
