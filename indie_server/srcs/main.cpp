#include <iostream>
#include "Router.hh"
#include "Server.h"

int main() {
    Indie::Router   router;
    Indie::Server   server(4242);
    int             fd;

    if (!router.parseLine("/user/connect Arnaud 123"))
        std::cout << "500 Error" << std::endl;
    if (!router.parseLine("/game/createRoom Arnaud"))
        std::cout << "500 Error" << std::endl;
    if (!router.parseLine("/game/getRoomList"))
        std::cout << "500 Error" << std::endl;
    if (!router.parseLine("/user/connect Erwan 123"))
        std::cout << "500 Error" << std::endl;
    if (!router.parseLine("/game/createRoom Erwan"))
        std::cout << "500 Error" << std::endl;
    if (!router.parseLine("/game/quitRoom Erwan"))
        std::cout << "500 Error" << std::endl;
    if (!router.parseLine("/game/getRoomList"))
        std::cout << "500 Error" << std::endl;
    if (!router.parseLine("/game/joinRoom 0 Erwan"))
        std::cout << "500 Error" << std::endl;
    if (!router.parseLine("/game/quitRoom Erwan"))
        std::cout << "500 Error" << std::endl;
    if (!router.parseLine("/game/quitRoom Arnaud"))
        std::cout << "500 Error" << std::endl;
    if (!router.parseLine("/game/getRoomList"))
        std::cout << "500 Error" << std::endl;
    return 0;
}