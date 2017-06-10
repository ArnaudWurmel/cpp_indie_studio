#include <iostream>
#include "Server.h"
#include "GameManager.hh"
#include "ConfParser.hh"

int main() {
    try {
        Indie::ConfParser   *confParser = Indie::ConfParser::getSingloton();
        Indie::Server   server(confParser->getPort());

        server.serverLoop();
        Indie::GameManager::getSingleton(true);
        Indie::ConfParser::getSingloton(true);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}