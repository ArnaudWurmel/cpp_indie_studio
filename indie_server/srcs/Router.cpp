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
        { "/game/runGame", &Indie::Router::runGame },
        { "/game/getMap", &Indie::Router::getMap },
        { "/game/getPlayerPos", &Indie::Router::getPlayerPosition }
};

const std::vector<Indie::Router::User> Indie::Router::userList = {
        { "Arnaud", "123" },
        { "Erwan", "123" },
        { "Thibaud", "123" }
};

Indie::Router::Router() {}

bool    Indie::Router::parseLine(std::string const& input, Server& server) {
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
    std::cout << tokenList[0] << std::endl;
    if (tokenList.size() > 0 && fnc.find(tokenList[0]) != fnc.end()) {
        cmdPtr ptr = (*fnc.find(tokenList[0])).second;
        return (this->*ptr)(tokenList, server);
    }
    return false;
}

bool Indie::Router::createRoom(std::vector<std::string> const& tokenList, Server& server) const {
    if (tokenList.size() != 2)
        return false;

    GameManager *gameManager = GameManager::getSingleton();

    unsigned int    roomId = gameManager->createRoom();
    bool state = gameManager->joinRoom(roomId, tokenList[1]);
    gameManager->release();
    if (state) {
        std::string res = "200 ";

        res += std::to_string(roomId);
        server.setResponse(res);
    }
    return state;
}

bool    Indie::Router::userConnect(std::vector<std::string> const& input, Server& server) const {

    std::vector<Indie::Router::User>::const_iterator    it;

    if (input.size() != 3) {
        return false;
    }
    it = userList.begin();
    while (it != userList.end()) {
        if (!(*it).username.compare(input[1]) && !(*it).password.compare(input[2])) {
            server.setResponse("200 Connected.");
            return true;
        }
        ++it;
    }
    return false;
}

bool    Indie::Router::getRoomList(std::vector<std::string> const& input, Server& server) const {
    if (input.size() != 1)
        return false;
    GameManager *gameManager = GameManager::getSingleton();

    std::vector<std::unique_ptr<Indie::Room> >::const_iterator it = gameManager->getRoomList().begin();
    std::string res = "200";

    while (it != gameManager->getRoomList().end()) {
        res += " ";
        res += std::to_string((*it)->getRoomId());
        ++it;
    }
    server.setResponse(res);
    gameManager->release();
    return true;
}

bool    Indie::Router::joinRoom(std::vector<std::string> const& input, Server& server) const {
    if (input.size() != 3)
        return false;
    GameManager *gameManager = GameManager::getSingleton();

    int roomId = std::atoi(input[1].c_str());
    bool state = false;
    if (roomId >= 0) {
        state = gameManager->joinRoom(roomId, input[2]);
        if (state)
            server.setResponse("200 OK");
    }
    gameManager->release();
    return state;
}

bool    Indie::Router::exitRoom(std::vector<std::string> const& input, Server& server) const {
    if (input.size() != 2)
        return false;
    GameManager *gameManager = GameManager::getSingleton();

    gameManager->exitRoom(input[1]);
    gameManager->release();
    server.setResponse("200 OK");
    return true;
}

bool    Indie::Router::runGame(std::vector<std::string> const& input, Server& server) const {
    if (input.size() != 2)
        return false;
    GameManager *gameManager = GameManager::getSingleton();

    int roomId = std::atoi(input[1].c_str());
    bool    state = false;
    if (roomId >= 0) {
        state = gameManager->runGame(roomId);
        if (state)
            server.setResponse("200 OK");
    }
    gameManager->release();
    return state;
}

bool    Indie::Router::getMap(std::vector<std::string> const& input, Server& server) const {
    if (input.size() != 2) {
        return false;
    }

    GameManager *gameManager = GameManager::getSingleton();

    int roomId = std::atoi(input[1].c_str());
    bool state = false;
    if (roomId >= 0) {
        std::cout << roomId << std::endl;
        state = gameManager->getMap(roomId, server);
    }
    gameManager->release();
    return state;
}

bool Indie::Router::getPlayerPosition(std::vector<std::string> const& input, Indie::Server& server) const {
    if (input.size() != 2)
        return false;
    GameManager *gameManager = GameManager::getSingleton();

    bool    state  = gameManager->getPlayerPosition(input[1], server);
    gameManager->release();
    return state;
}

Indie::Router::~Router() {}