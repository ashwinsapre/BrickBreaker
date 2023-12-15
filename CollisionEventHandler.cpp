#include "CollisionEventHandler.h"
#include "Character.h"
#include <iostream>

void CollisionEventHandler::onEvent(Event *e){
	if (e->x==1.f){
		e->ball->velocity.x = e->ball->velocity.x*-1;
	}
	else{
		e->ball->velocity.y = e->ball->velocity.y*-1;
        e->ball->velocity.x = e->offset*0.005 + e->ball->velocity.x;
	}
	std::cout<<"Collision event!\n";
}