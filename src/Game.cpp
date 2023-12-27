#include "Game.h"
#include "Event.h"

void Game::init() {
    window.create(sf::VideoMode(_windowLength, _windowHeight), "BRICK BREAKER", sf::Style::Default);
    view.reset(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
    eventManager = new EventManager();
    ceh = new CollisionEventHandler();
    stareh = new StarPowerEventHandler();
    freezeeh = new FreezePowerEventHandler();
    hitBuffer.loadFromFile("../assets/hit.wav");
    hitSound.setBuffer(hitBuffer);
    brickHitBuffer.loadFromFile("../assets/brick_hit.wav");
    brickHitSound.setBuffer(brickHitBuffer);

    startScreen = new Screen(std::string("BRICKBREAKER"), std::string("Press SPACE to begin..."), 40, 20, sf::Color::Green, sf::Color::White, sf::Vector2f(400.f, 300.f), sf::Vector2f(400.f, 350.f));
    gameWinScreen = new Screen(std::string("YOU WIN!"), std::string("Press RETURN/ENTER to continue..."), 40, 20, sf::Color::Green, sf::Color::White, sf::Vector2f(400.f, 300.f), sf::Vector2f(400.f, 350.f));
    gameOverScreen = new Screen(std::string("GAME OVER!"), std::string("Press RETURN/ENTER to continue..."), 24, 20, sf::Color::Red, sf::Color::White, sf::Vector2f(400.f, 300.f), sf::Vector2f(400.f, 350.f));

    scoreManager = new ScoreManager();
    allScores = new std::vector<Score>();

    sf::Clock c;
    globalTimeline = new Timeline(c,1.f);
    eventManager->reg(1, ceh);
    eventManager->reg(2, stareh);
    eventManager->reg(3, freezeeh);
    // eventManager->reg(2, taeh);
    // eventManager->reg(3, oobeh);
    //globalTimeline = t;
    sock.connect("tcp://127.0.0.1:5555");

    //new client connecting to server always starts with Hello
    std::string data = "Hello";
    std::cout << "Connecting to server..." << std::endl;
    sock.send(zmq::buffer(data), zmq::send_flags::none);

    zmq::message_t id_reply;
    sock.recv(id_reply, zmq::recv_flags::none);
    std::string message(static_cast<char*>(id_reply.data()), id_reply.size());
    // id = message;
    std::cout<<message<<std::endl;
    std::cout<<"init done\n";

    allScores = scoreManager->loadScores();
    std::cout<<"number of saved scores="<<allScores->size()<<std::endl;
    for (int i=0;i<allScores->size(); i++){
        std::cout << (*allScores)[i].playerName << (*allScores)[i].scoreValue << std::endl;
    }
}
void Game::inputService(float dt, float mul){
    if (window.hasFocus()){
        if (gameStarted==false && sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            gameStarted=true;
            //generate Game Start event
            Event *e = new Event(1,0.f, 0.f);
            eventManager->enqueue(e);
            eventManager->raise(e);
        }
    }
    }
void Game::sendToServer(std::string data) {
    sock.send(zmq::buffer(data), zmq::send_flags::none);
}
std::string Game::receiveFromServer() {
    zmq::message_t rep;
    sock.recv(rep, zmq::recv_flags::none);
    return rep.to_string();
}
void Game::disconnect() {
    std::string upd = "Bye";
    sock.send(zmq::buffer(upd), zmq::send_flags::none);
    std::cout << "DISCONNECTING!" << "sending message:" << upd << std::endl;

    zmq::message_t rep;
    sock.recv(rep, zmq::recv_flags::none);
    std::cout << "Received message: " + rep.to_string() << std::endl;
}

void Game::reset(){
    gameStarted = false;
    needNewTarget = false;
    win = false;
    paused = false;
    gameEnded = false;
    isPowerActive = false;
    scoreSaved = false;

    globalTimeline->reset();
    power->isActive = false;
    endPowerUpTime = 0.f;
    startPowerUpTime = 0.f;
    lastKeyPressed = 0.f;

}