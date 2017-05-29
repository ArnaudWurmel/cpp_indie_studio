//
// Created by ballet on 24/05/17.
//

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "Router.hh"
#include "GameManager.hh"

const std::map<std::string, Indie::Router::cmdPtr> Indie::Router::fnc = {
        { "/user/connect", &Indie::Router::userConnect},
        { "/game/createRoom", &Indie::Router::createRoom },
        { "/game/joinRoom", &Indie::Router::joinRoom },
        { "/game/quitRoom", &Indie::Router::exitRoom },
        { "/game/getRoomList", &Indie::Router::getRoomList },
        { "/game/runGame", &Indie::Router::runGame }
};

const std::vector<Indie::Router::User> Indie::Router::userList = {
        { "Arnaud", "123" },
        { "Erwan", "123" },
        { "Thibaud", "123" }
};

Indie::Router::Router() {}

bool    Indie::Router::parseLine(std::string const& input) {
    std::vector<std::string>    tokenList;
    std::string::const_iterator   it;

    it = input.begin();
    while (it != input.end()) {
        std::string token;
        while (it != input.end() && *it != ' ') {
            token += *it;
            ++it;
        }
        if (token.size())
            tokenList.push_back(token);
        while (it != input.end() && *it == ' ')
            ++it;
    }
    if (tokenList.size() > 0 && fnc.find(tokenList[0]) != fnc.end()) {
        cmdPtr ptr = (*fnc.find(tokenList[0])).second;
        return (this->*ptr)(tokenList);
    }
    return false;
}

bool Indie::Router::createRoom(std::vector<std::string> const& tokenList) {
    if (tokenList.size() != 2)
        return false;

    GameManager *gameManager = GameManager::getSingleton();

    unsigned int    roomId = gameManager->createRoom();
    bool state = gameManager->joinRoom(roomId, tokenList[1]);
    gameManager->release();
    if (state)
        std::cout << "200 " << roomId << std::endl;
    return state;
}

bool    Indie::Router::userConnect(std::vector<std::string> const& input) {

    std::vector<Indie::Router::User>::const_iterator    it;

    if (input.size() != 3) {
        return false;
    }
    it = userList.begin();
    while (it != userList.end()) {
        if (!(*it).username.compare(input[1]) && !(*it).password.compare(input[2])) {
            std::cout << "200 Connected." << std::endl;
            return true;
        }
        ++it;
    }
    return false;
}

bool    Indie::Router::getRoomList(std::vector<std::string> const& input) {
    if (input.size() != 1)
        return false;
    GameManager *gameManager = GameManager::getSingleton();

    std::vector<std::unique_ptr<Indie::Room> >::const_iterator it = gameManager->getRoomList().begin();

    std::cout << "200";
    while (it != gameManager->getRoomList().end()) {
        std::cout << " " << (*it)->getRoomId();
        ++it;
    }
    std::cout << std::endl;
    gameManager->release();
    return true;
}

bool    Indie::Router::joinRoom(std::vector<std::string> const& input) {
    if (input.size() != 3)
        return false;
    GameManager *gameManager = GameManager::getSingleton();

    int roomId = std::atoi(input[1].c_str());
    bool state = false;
    if (roomId >= 0) {
        state = gameManager->joinRoom(roomId, input[2]);
        if (state)
            std::cout << "200 OK" << std::endl;
    }
    gameManager->release();
    if (!state)
        std::cout << "500 Error" << std::endl;
    return state;
}

bool    Indie::Router::exitRoom(std::vector<std::string> const& input) {
    if (input.size() != 2)
        return false;
    GameManager *gameManager = GameManager::getSingleton();

    gameManager->exitRoom(input[1]);
    gameManager->release();
    std::cout << "200 OK" << std::endl;
    return true;
}

bool    Indie::Router::runGame(std::vector<std::string> const& input) {
    if (input.size() != 2)
        return false;
    GameManager *gameManager = GameManager::getSingleton();

    int roomId = std::atoi(input[1].c_str());
    bool    state = false;
    if (roomId >= 0) {
        state = gameManager->runGame(roomId);
        if (state)
            std::cout << "200 OK" << std::endl;
    }
    if (!state)
        std::cout << "500 Error" << std::endl;
    gameManager->release();
}

Indie::Router::~Router() {}