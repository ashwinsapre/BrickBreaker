#include "../include/zmq.hpp"
#include "../include/GameServer.h"
#include "../include/Timeline.h"
#include <iostream>
#include <random>
#include <ctime>

GameServer::GameServer() : context(1), init_connect(context, ZMQ_REP) {
        this->init_connect.bind("tcp://127.0.0.1:5555");
}

float getRandom(){
    // Define a distribution for floats in the specified range
    std::uniform_real_distribution<float> dist(0.f, 500.f);
    std::mt19937 rng(static_cast<unsigned>(std::time(0)));

    // Generate a random float
    float randomFloat = dist(rng);

    return randomFloat;
}


int main(){
    GameServer g;
    sf::Clock globalClock;
    Timeline *globalTime = new Timeline(globalClock, 1.f);

    while(true){
        //std::this_thread::sleep_for(0.5s);
        zmq::message_t request;
        g.init_connect.recv(request, zmq::recv_flags::none);

        //if new client is detected
        if (request.to_string() == "Hello"){
            std::cout << "Client has joined" << std::endl;
            globalTime->clock.restart();
            std::string msg = "no update";
            g.init_connect.send(zmq::buffer(msg));
        }
        else{
            if (globalTime->clock.getElapsedTime().asSeconds()>5){
                std::cout<<"told client to update screen\n";
                std::string msg="UPDATE";
                g.init_connect.send(zmq::buffer(msg));
                globalTime->clock.restart();
            }
            else{
                std::string msg="no update";
                g.init_connect.send(zmq::buffer(msg));
            }
            
        }
    }
}