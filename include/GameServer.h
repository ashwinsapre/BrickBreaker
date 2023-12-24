#ifndef GAMESERVER_H
#define GAMESERVER_H


#include <vector>
#include <map>

class GameServer {
public:
    zmq::context_t context;
    zmq::socket_t init_connect;

    GameServer();

    float getRandom();
    void thread_worker(int newport);
    void parseUpdate(std::string update, int port);
    void parsePositions(std::string update);
    void parseEvents(std::string update, int port);
    void movingPlatformInit();
    void movingPlatformUpdate();
    int registerNewClient(std::string request);
    void disconnectClient(std::string request);
    std::string constructGlobalUpdate(int port);
    void checkTimeout();
};

#endif  // GAMESERVER_H
