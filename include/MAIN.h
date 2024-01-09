#ifndef MAIN_H
#define MAIN_H

#include <random>
#include "Event.h"
#include "ScriptManager.h"
#include "StarPowerUp.h"
#include "FreezePowerUp.h"
float elapsedTimeInSeconds;

int getRandom(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, 1);
    int randomValue = distribution(gen);
    return randomValue;
}

void init(Game* g, Character* ball, std::vector<StaticPlatform*>* bricks) {
    bool stagger = true;
    int aliveBrickCount = 0;

    // Adjust starting position to be 1/5th from the top
    float startY = g->_windowHeight / 7.0f;
    g->brickTop = startY;

    for (float y = startY; y < startY + 4 * (g->brickHeight + 5); y += g->brickHeight + 5) {
        for (float x = 0; x < g->_windowLength - 20.f; x += g->brickLength + 5) {
            StaticPlatform* b = new StaticPlatform(g->brickLength, g->brickHeight, stagger ? x : x + 25, y, sf::Color::White);
            if (g->brickTexture.loadFromFile("../assets/brick.png")) {
                b->setTexture(&g->brickTexture);
                // backgroundSprite.setScale(0.25, 0.25);
            }
            bricks->push_back(b);
            aliveBrickCount++;
        }
        stagger = !stagger;
        g->brickBottom = y;
    }

    // Initialize player and ball
    g->aliveBrickCount = aliveBrickCount;
    ball->setPos(0.5f * (g->_windowLength), 4.0f * g->_windowHeight / 5.0f);
    ball->velocity = sf::Vector2f(0, g->yvel);
    ball->move(ball->velocity);

    g->power = new StarPowerUp(20);
    g->startMusic.play();
}


void reset(Game* g, Character* ball, StaticPlatform* platform, std::vector<StaticPlatform*>* bricks) {
    // Reset brick positions
    g->reset();
    bool stagger = true;
    int aliveBrickCount = 0;
    auto brickIt = bricks->begin();
    ball->resetPower();

    float startY = g->_windowHeight / 5.0f;

    for (float y = startY; y < startY + 3 * (g->brickHeight + 5); y += g->brickHeight + 5) {
        for (float x = 0; x < g->_windowLength; x += g->brickLength + 5) {
            if (brickIt != bricks->end()) {
                // Update the brick position to its initial position
                (*brickIt)->setPosition(stagger ? x : x + 25, y);
                (*brickIt)->isVisible = 1;
                ++brickIt;
                aliveBrickCount++;
            }
        }
        stagger = !stagger;
    }

    // Reset platform position
    platform->setPosition(0.5f * (g->_windowLength - platform->getSize().x), g->_windowHeight - 100.f);

    // Reset ball position
    ball->setPos(0.5f * (g->_windowLength), 3.0f * g->_windowHeight / 5.0f);
    ball->velocity = sf::Vector2f(0, g->yvel);
    ball->move(ball->velocity);

    g->aliveBrickCount = aliveBrickCount;
}


void send(Game *g){
    std::string s = "--";
    g->sendToServer(s);
}

void receive(Game *g, std::vector<StaticPlatform*> *bricks){
    if (g->receiveFromServer() == "UPDATE"){
        //std::cout<<"MOVE BRICKS DOWN!\n";
        for (int i=(*bricks).size()-1;i>=0;i--){
            (*bricks)[i]->move(0, g->_windowHeight/30.f);
        }
        g->brickBottom+=g->_windowHeight/20.f;
        g->brickTop+=g->_windowHeight/20.f;
    }
}

void renderService(Game *g, Character *ball, std::vector<StaticPlatform*> *bricks, StaticPlatform *platform){
    sf::Font font;
    font.loadFromFile("../assets/valorax.otf");
    g->window.clear();
    if (g->gameStarted){
        //if it has been 5 seconds since the last power up ended, make a new power up
        if (!g->power->isActive && (g->globalTimeline->getCurrentTime() - g->endPowerUpTime)>5.f){
            g->power->isActive = true;
            g->startPowerUpTime = g->globalTimeline->getCurrentTime();
            g->power->setPosition(ball->getPosition().x, 500.f);
        }
        //if it has been 20 seconds since the power up started, stop displaying
        if (g->power->isActive && (g->globalTimeline->getCurrentTime() - g->startPowerUpTime)>20.f){
            g->starMusic.stop();
            g->themeMusic.setPlayingOffset(sf::seconds(g->themeMusicPausedTime));
            g->themeMusic.play();
            std::cout<<"Power up ended\n";
            g->power->isActive = false;
            g->isPowerActive = false;
            g->endPowerUpTime = g->globalTimeline->getCurrentTime();
            if (dynamic_cast<StarPowerUp*>(g->power)) {
                Event *e = new Event(2, 0, 0, 0, ball);
                g->eventManager->enqueue(e);
                g->eventManager->raise(e);
            }
            else {
                Event *e = new Event(3, 0, 0, 0, ball);
                g->eventManager->enqueue(e);
                g->eventManager->raise(e);
            }

            g->power = new StarPowerUp(20);
        }

        //WIN SCREEN
        if (g->win){
            if (!g->scoreSaved){
                g->themeMusic.stop();
                g->gameWinMusic.play();
                float score = g->globalTimeline->getCurrentTime();
                g->globalTimeline->pause();
                Score s("ashwin", score);
                std::cout<<"saving score\n";
                g->scoreManager->saveScore(s);
                g->scoreSaved = true;
            }
            g->gameWinScreen->draw(g->window);
            
        }

        //GAME SCREEN
        else if(!g->gameEnded){
            g->window.draw(g->backgroundSprite);
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
            //render timer
            sf::Text text;
            text.setFont(font);
            
            if (!g->paused){
                elapsedTimeInSeconds = g->globalTimeline->getCurrentTime();
            }
            // if (dynamic_cast<FreezePowerUp*>(g->power) && g->isPowerActive){
            //     elapsedTimeInSeconds = g->startPowerUpTime;
            // }
            
            text.setString(std::to_string(elapsedTimeInSeconds));
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::White);
            text.setPosition(0.f, 0.f);
            g->window.draw(text);
            if (g->power && g->power->isActive && !g->isPowerActive){
                g->window.draw(*g->power);
            }

            //PAUSE OVERLAY
            if (g->paused){
                sf::RectangleShape overlay(sf::Vector2f(g->window.getSize().x, g->window.getSize().y));
                overlay.setFillColor(sf::Color(0, 0, 0, 150));  // Adjust alpha value for transparency
                g->window.draw(overlay);
                sf::Text text;
                text.setFont(font);
                text.setString("Game Paused");
                text.setCharacterSize(24);

                text.setFillColor(sf::Color::White);
                text.setPosition((g->_windowLength - text.getGlobalBounds().width)/2, (g->_windowHeight-text.getGlobalBounds().width)/2);
                g->window.draw(text);
            }
        }
        //GAME OVER SCREEN
        else if (g->gameEnded){
            g->gameOverScreen->draw(g->window);
            g->themeMusic.stop();
            g->gameOverMusic.play();
        }
    }
    else{
        if (!g->showScores){
            //START SCREEN
            g->startScreen->draw(g->window);
        }
        else{
            g->scoresScreen->draw(g->window);
        }
        
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

void inputService(Game *g, Character *ball, std::vector<StaticPlatform*> *bricks, StaticPlatform *platform,  ScriptManager *sm){
    if (g->window.hasFocus()){
            //START GAME
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !g->gameStarted && !g->showScores){
                g->startMusic.stop();
                g->themeMusic.play();
                g->gameStarted=true;
                g->globalTimeline->clock.restart();
            }

            //SHOW LEADERBOARD
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && !g->gameStarted){
                g->allScores = g->scoreManager->getTopScores(5);
                std::string scoreString = "";
                for (auto s: *(g->allScores)){
                    scoreString = scoreString + s.playerName + "\t" + std::to_string(s.scoreValue) + "\n";
                }
                g->scoresScreen->setSecondaryText(scoreString);
                g->showScores = true;
            }

            //REMOVE LEADERBOARD
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && g->showScores){
                g->showScores = false;
            }

            //RESTART GAME
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && g->gameEnded){
                g->gameStarted = false;
                g->gameEnded = false;
                g->needNewTarget = false;
                g->win = false;
                g->paused = false;
                g->gameEnded = false;
                g->scoreSaved = false;
                reset(g, ball, platform, bricks);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !g->paused && g->gameStarted){
                std::cout<<"manually won\n";
                g->win = true;
                g->gameEnded = true;
            }

            //MOVE PLATFORM RIGHT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !g->paused && g->gameStarted){
                platform->move(2.0f*g->dt*g->mul, 0);
            }
            //MOVE PLATFORM LEFT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !g->paused && g->gameStarted){
                platform->move(-2.0f*g->dt*g->mul, 0);
            }
            //TRIGGER EXTERNAL SCRIPT
            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && !g->paused && g->gameStarted){
            //     sm->runOne("change_size", true, "object_context");
            //     sf::Vector2f newsize(platform->xsize, platform->ysize);
            //     platform->setSize(newsize);
            //     platform->setPosition(0,500.f);
            // }
            //PAUSE
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && g->gameStarted && (g->globalTimeline->clock.getElapsedTime().asSeconds() - g->lastKeyPressed)>0.1){
                g->lastKeyPressed = g->globalTimeline->clock.getElapsedTime().asSeconds();
                g->paused = !g->paused;
                //if the game becomes unpaused
                if (!g->paused){
                    g->globalTimeline->unpause();
                    std::cout<<"restarted at"<<g->globalTimeline->getCurrentTime()<<std::endl;
                }
                //if the game becomes paused
                else{
                    g->globalTimeline->pause();
                    std::cout<<"paused at"<<g->globalTimeline->last_paused_time<<std::endl;
                }
            }
                
        }
}

void physicsService(Game *g, Character *ball){
    ball->physics(g->dt);
}

void collisionService(Game *g, StaticPlatform *platform, Character *ball, std::vector<StaticPlatform*> *bricks, ScriptManager *sm){
    if (g->brickTop < ball->getPosition().y < g->brickBottom){
        //collisions of ball with bricks
        int count = 0;

        for (int i = (*bricks).size() - 1; i >= 0; i--){
            if ((*bricks)[i]->isVisible){
                sf::FloatRect brickBounds = (*bricks)[i]->getGlobalBounds();
                if (ball->getGlobalBounds().intersects(brickBounds)) {
                    (*bricks)[i]->isVisible = false;
                    g->aliveBrickCount-=1;
                    if (!g->isPowerActive){
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
                                g->brickHitSound.play();
                                g->eventManager->enqueue(e);
                                g->eventManager->raise(e);
                                //ball->velocity.x = -ball->velocity.x;
                            }
                        } 
                        else {
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
                                g->brickHitSound.play();
                                g->eventManager->enqueue(e);
                                g->eventManager->raise(e);
                                //ball->velocity.y = -ball->velocity.y;
                            }
                        }
                    }
                    
                }
            }
        }
    }

    if (g->power->isActive && !g->isPowerActive && ball->getGlobalBounds().intersects(g->power->getGlobalBounds())){
        g->startPowerUpTime = g->globalTimeline->getCurrentTime();
        g->power->isActive = false;
        
        //PowerUp->isActive controls visibility
        //Game->isPowerActive controls power
        g->isPowerActive = true;
        g->themeMusicPausedTime = g->themeMusic.getPlayingOffset().asSeconds();
        g->themeMusic.pause();
        g->starMusic.play();
        std::cout << "It's a StarPowerUp!" << std::endl;
        Event *e = new Event(2, 0, 0, 1, ball);
        g->eventManager->enqueue(e);
        g->eventManager->raise(e);
        
    }

    if (ball->getGlobalBounds().intersects(platform->getGlobalBounds())){
	    g->hitSound.play();
        float offsetFromCenter = ball->getPosition().x - (platform->getGlobalBounds().left + platform->getGlobalBounds().width/2);
        float normalizedOffset = offsetFromCenter / (platform->getGlobalBounds().width / 2);

        //sm->runOne("handle_event", true, "object_context");
        Event *e = new Event(1, 0, 1.0, normalizedOffset, ball);
        g->eventManager->enqueue(e);
        g->eventManager->raise(e);
    }

    //collision with top boundary
    if (ball->getGlobalBounds().top < 5.f){
        Event *e = new Event(1, 0, 1.0, 0, ball);
        g->eventManager->enqueue(e);
        g->eventManager->raise(e);
        //ball->velocity.y = -ball->velocity.y;
    }
    //collision with left boundary
    if (ball->getGlobalBounds().left < 15.f){
        Event *e = new Event(1, 1.0, 0, 0, ball);
        g->eventManager->enqueue(e);
        g->eventManager->raise(e);
        // ball->velocity.x = -ball->velocity.x;
    }
    //collision with right boundary
    if (ball->getGlobalBounds().left > g->_windowLength - 15.f){
        Event *e = new Event(1, 1.0, 0, 0, ball);
        g->eventManager->enqueue(e);
        g->eventManager->raise(e);
        // ball->velocity.x = -ball->velocity.x;
    }

    if (ball->getPosition().y > g->_windowHeight ){
        ball->isAlive = false;
        g->gameEnded = true;
    }
    for (int i=(*bricks).size()-1;i>=0;i--){
        if ((*bricks)[i]->getPosition().y >= platform->getPosition().y - 20.f){
            ball->isAlive = false;
            g->gameEnded = true;
        }
    }
    if (g->aliveBrickCount==0){
        std::cout<<"no more alive bricks\n";
        g->win = true;
        g->gameEnded = true;
    }

}

#endif