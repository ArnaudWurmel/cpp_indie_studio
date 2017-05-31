#include <iostream>
#include "Server.h"
#include "GameManager.hh"

int main() {
    Indie::Server   server(4242);

    server.serverLoop();
    Indie::GameManager::getSingleton(true);
    return 0;
}