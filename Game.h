#ifndef GAME_H
#define GAME_H

#include "json.hpp"
#include "Timeline.h"
#include "Event.h"
#include "EventManager.h"
#include "CollisionEventHandler.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <zmq.hpp>

using json = nlohmann::json;

class Game {
public:
    bool gameStarted = false;
    bool needNewTarget = false;
    bool win = false;
    bool paused = false;
    bool gameEnded = false;

    int aliveBrickCount = 0;

    float targetX=300;
    float targetY=300;
    float brickLength = 70.f;
    float brickHeight = 50.f;
    float brickTop = 195.f;
    float brickBottom = 305.f;

    float xvel = 1;
    float yvel = 1;

    float dt = 0;
    float mul = 80;
    float lastKeyPressed = 0;
    float lastPowerUpTime = 0.f;
    Timeline *globalTimeline;
    
    CollisionEventHandler *ceh;

    sf::RenderWindow window;
    float _windowLength = 800;
    float _windowHeight = 600;

    zmq::context_t context;
    zmq::socket_t sock;

    sf::SoundBuffer hitBuffer, brickHitBuffer;
    sf::Sound hitSound;
    sf::Sound brickHitSound;

    zmq::socket_t main_sock;

    EventManager *eventManager;

    //Character *mainCharacter;

    //Spawn *newCharSpawn = new Spawn(50.f, 100.f);
    sf::View view;

    Game() : context(1), sock(context, ZMQ_REQ) {}

    void init();

    void initObjects();

    void sendToServer(std::string data);

    std::string receiveFromServer();

    void parseCharacterInfo(std::string j);

    void parseMovingPlatformInfo(std::string j);

    void parseEventsInfo(std::string j);

    void updateTic(float t);

    void disconnect();

    void eventService(sf::Event event);

    void inputService(float dt, float mul);

    void physicsService();

    void collisionService();

    void renderService();

    void shutdown();
};

#endif // GAME_H
