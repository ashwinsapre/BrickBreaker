#include "FreezePowerEventHandler.h"
#include "Character.h"
#include <iostream> // Example: Include necessary headers


void FreezePowerEventHandler::onEvent(Event* e) {
    // Check the type of the event and handle accordingly
   std::cout<<"Freeze power!\n";
   if (e->offset==1){
        e->ball->setFillColor(sf::Color::Blue);
        std::cout<<"Freeze power!\n";
    }
    else{
        e->ball->setFillColor(sf::Color::White);
        std::cout<<"Freeze power reset!\n";
    }
}

// Implement additional member functions if needed
