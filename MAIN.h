#ifndef MAIN_H
#define MAIN_H

#include "Event.h"
#include "ScriptManager.h"

void init(Game *g, Character *ball, std::vector<StaticPlatform*> *bricks){
    //std::cout<<"making bricks\n";
    //init 2 rows of bricks
    bool stagger=true;
    int aliveBrickCount = 0;
    for(float y=200; y<g->_windowHeight-350; y+=g->brickHeight+5){
        for(float x=0; x<g->_windowLength; x+=g->brickLength+5){
            StaticPlatform *b = new StaticPlatform(g->brickLength, g->brickHeight, stagger?x:x+25, y, sf::Color::White);
            bricks->push_back(b);
            aliveBrickCount++;
        }
        stagger=!stagger;
    }
    //init player
    //init ball
    g->aliveBrickCount = aliveBrickCount;
    ball->setPos(400.f, 450.f);
    ball->velocity = sf::Vector2f(0, g->yvel);
    ball->move(ball->velocity);
}

void send(Game *g){
    std::string s = "--";
    g->sendToServer(s);
}

void receive(Game *g, std::vector<StaticPlatform*> *bricks){
    if (g->receiveFromServer() == "UPDATE"){
        //std::cout<<"MOVE BRICKS DOWN!\n";
        for (int i=(*bricks).size()-1;i>=0;i--){
            (*bricks)[i]->move(0, 10.f);
        }
        g->brickBottom+=10.f;
        g->brickTop+=10.f;
    }
}
void renderService(Game *g, Character *ball, std::vector<StaticPlatform*> *bricks, StaticPlatform *platform){
    g->window.clear();
    if (g->win){
        sf::Font font;
        font.loadFromFile("arial.ttf");
        sf::Text text;
        text.setFont(font);
        text.setString("YOU WIN!!");
        text.setCharacterSize(40);

       // Set the text color
        text.setFillColor(sf::Color::Green);

       // Set the text position
        text.setPosition(400.f, 300.f);
        g->window.draw(text);
    }

    else if(ball->isAlive){
        
        g->window.draw(*ball);
        if (platform->newColor==0){
            platform->setFillColor(sf::Color::Red);
        }
        else{
            platform->setFillColor(sf::Color::Green);
        }
        g->window.draw(*platform);
        for(auto b: *bricks){
            if (b->isVisible){
                g->window.draw(*b);
            }
        }
        if (g->paused){
            sf::RectangleShape overlay(sf::Vector2f(g->window.getSize().x, g->window.getSize().y));
            overlay.setFillColor(sf::Color(0, 0, 0, 150));  // Adjust alpha value for transparency
            g->window.draw(overlay);

            sf::Font font;
            font.loadFromFile("arial.ttf");
            sf::Text text;
            text.setFont(font);
            text.setString("Game Paused");
            text.setCharacterSize(24);

            text.setFillColor(sf::Color::White);
            text.setPosition(400.f, 300.f);
            g->window.draw(text);
        }
    }
    else{
        sf::Font font;
        font.loadFromFile("arial.ttf");
        sf::Text text;
        text.setFont(font);
        text.setString("Game Over!");
        text.setCharacterSize(24);

       // Set the text color
        text.setFillColor(sf::Color::White);

       // Set the text position
        text.setPosition(400.f, 300.f);
        g->window.draw(text);

    }
    g->window.display();
}

void eventService(Game *g, sf::Event event){
    while (g->window.pollEvent(event))
        if (event.type == sf::Event::Closed) {
            //disconnect();
            g->window.close();
        }
}

void inputService(Game *g, StaticPlatform *platform, ScriptManager *sm){
    if (g->window.hasFocus()){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !g->paused){
                platform->move(2.0f*g->dt*g->mul, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !g->paused){
                platform->move(-2.0f*g->dt*g->mul, 0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && !g->paused){
                sm->runOne("change_size", true, "object_context");
                sf::Vector2f newsize(platform->xsize, platform->ysize);
                platform->setSize(newsize);
                platform->setPosition(0,500.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && (g->globalTimeline->getCurrentTime() - g->lastKeyPressed)>0.1){
                g->lastKeyPressed = g->globalTimeline->getCurrentTime();
                g->paused = !g->paused;
            }
                
        }
}

void physicsService(Game *g, Character *ball){
    ball->physics(g->dt);
}

void collisionService(Game *g, StaticPlatform *platform, Character *ball, std::vector<StaticPlatform*> *bricks, ScriptManager *sm){
    if (g->brickTop < ball->getPosition().y < g->brickBottom){
        //collisions of ball with bricks

        for (int i = (*bricks).size() - 1; i >= 0; i--){

            if ((*bricks)[i]->isVisible){
                sf::FloatRect brickBounds = (*bricks)[i]->getGlobalBounds();
                if (ball->getGlobalBounds().intersects(brickBounds)) {
                    (*bricks)[i]->isVisible = false;
                    g->aliveBrickCount-=1;
                    // Calculate intersection depth
                    float intersectDepthX = std::min(ball->getGlobalBounds().left + ball->getGlobalBounds().width, brickBounds.left + brickBounds.width) - 
                                            std::max(ball->getGlobalBounds().left, brickBounds.left);

                    float intersectDepthY = std::min(ball->getGlobalBounds().top + ball->getGlobalBounds().height, brickBounds.top + brickBounds.height) - 
                                            std::max(ball->getGlobalBounds().top, brickBounds.top);

                    // Determine the collision direction
                    if (intersectDepthX < intersectDepthY) {
                        // Collision from left or right
                        if (ball->getGlobalBounds().left + ball->getGlobalBounds().width > brickBounds.left &&
                            ball->getGlobalBounds().left < brickBounds.left + brickBounds.width) {
                            // Adjust the ball's position
                            if (ball->getGlobalBounds().left < brickBounds.left) {
                                ball->setPosition(brickBounds.left - ball->getGlobalBounds().width, ball->getPosition().y);
                            } else {
                                ball->setPosition(brickBounds.left + brickBounds.width, ball->getPosition().y);
                            }
                            //Event *e = new Event(1, this, )
                            Event *e = new Event(1, 1.0, 0, 0, ball);
                            g->eventManager->enqueue(e);
                            g->eventManager->raise(e);
                            //ball->velocity.x = -ball->velocity.x;
                        }
                    } else {
                        // Collision from top or bottom
                        if (ball->getGlobalBounds().top + ball->getGlobalBounds().height > brickBounds.top &&
                            ball->getGlobalBounds().top < brickBounds.top + brickBounds.height) {
                            // Adjust the ball's position
                            if (ball->getGlobalBounds().top < brickBounds.top) {
                                ball->setPosition(ball->getPosition().x, brickBounds.top - ball->getGlobalBounds().height);
                            } else {
                                ball->setPosition(ball->getPosition().x, brickBounds.top + brickBounds.height);
                            }
                            Event *e = new Event(1, 0, 1.0, 0, ball);
                            g->eventManager->enqueue(e);
                            g->eventManager->raise(e);
                            //ball->velocity.y = -ball->velocity.y;
                        }
                    }
                }
            }
        }
    }

    if (ball->getGlobalBounds().intersects(platform->getGlobalBounds())){
        float offsetFromCenter = ball->getPosition().x - (platform->getGlobalBounds().left + platform->getGlobalBounds().width/2);
        sm->runOne("handle_event", true, "object_context");
        Event *e = new Event(1, 0, 1.0, offsetFromCenter, ball);
        g->eventManager->enqueue(e);
        g->eventManager->raise(e);
        // ball->velocity.y = -ball->velocity.y;
        // ball->velocity.x = offsetFromCenter*0.005 + ball->velocity.x;
    }

    //collision with top boundary
    if (ball->getGlobalBounds().top < 5.f){
        Event *e = new Event(1, 0, 1.0, 0, ball);
        g->eventManager->enqueue(e);
        g->eventManager->raise(e);
        //ball->velocity.y = -ball->velocity.y;
    }
    //collision with left boundary
    if (ball->getGlobalBounds().left < 5.f){
        Event *e = new Event(1, 1.0, 0, 0, ball);
        g->eventManager->enqueue(e);
        g->eventManager->raise(e);
        // ball->velocity.x = -ball->velocity.x;
    }
    //collision with right boundary
    if (ball->getGlobalBounds().left > 750.f){
        Event *e = new Event(1, 1.0, 0, 0, ball);
        g->eventManager->enqueue(e);
        g->eventManager->raise(e);
        // ball->velocity.x = -ball->velocity.x;
    }

    if (ball->getPosition().y > 600 ){
        ball->isAlive = false;
    }
    for (int i=(*bricks).size()-1;i>=0;i--){
        if ((*bricks)[i]->getPosition().y >= platform->getPosition().y - 20.f){
            ball->isAlive = false;
        }
    }
    if (g->aliveBrickCount==0){
        g->win = true;
    }

}

#endif