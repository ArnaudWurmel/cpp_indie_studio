//
// Created by wurmel_a on 29/05/17.
//

#include <unistd.h>
#include <iostream>
#include <sstream>
#include "Room.hh"
#include "Server.h"
#include "ConfParser.hh"
#include "../../srcs/Exception/Exception.hh"

unsigned int Indie::Room::roomId = 0;

Indie::Room::Room() {
    _mapList = ConfParser::getSingloton()->getMapList();
    if (_mapList.size() <= 0)
        throw GameException();
    _currentMap = _mapList.begin();
    _roomId = roomId;
    Indie::Room::roomId += 1;
    _running = false;
}

bool    Indie::Room::addPlayerToRoom(std::string const& pName) {
    if (_running && !_game->addPlayerToGame(pName)) {
        return false;
    }
    if (_playerList.size() < 4) {
        _playerList.push_back(pName);
        return true;
    }
    return false;
}

unsigned int    Indie::Room::removePlayerFromRoom(std::string const& pName) {
    std::vector<std::string>::iterator  it = _playerList.begin();

    while (it != _playerList.end()) {
        if (!(*it).compare(pName)) {
            _playerList.erase(it);
            if (_running)
                return _game->exitPlayer(pName);
            return 0;
        }
        ++it;
    }
    return 0;
}

bool    Indie::Room::getMap(Server& server) {
    if (!_running)
        return false;
    if (_game->getMap().size()) {
        std::string res = "200 ";

        std::vector<std::string>::const_iterator    it = _game->getMap().begin();
        while (it != _game->getMap().end()) {
            std::string::const_iterator itString = (*it).begin();

            while (itString != (*it).end()) {
                res += *itString;
                ++itString;
            }
            res += "\n";
            ++it;
        }
        server.setResponse(res);
        return true;
    }
    return false;
}

bool    Indie::Room::runGame() {
    if (_running)
        return false;
    try {
        Indie::Game *game = new Indie::Game(_playerList, *_currentMap);
        _game = std::unique_ptr<Indie::Game>(game);
        _running = true;
    } catch (std::exception& e) {
        std::cout << e.what();
        _running = false;
    }
    return true;
}

unsigned int const& Indie::Room::getRoomId() const {
    return _roomId;
}

bool    Indie::Room::getPlayerPos(std::string const& pName, Server& server) {
    if (!_running)
        return false;
    return _game->getPlayerPos(pName, server);
}

std::vector<std::string> const& Indie::Room::getPlayerList() {
    return _playerList;
}

bool    Indie::Room::updatePlayerPosition(std::vector<std::string> const& input) {
    if (_running)
        return _game->updatePlayerPosition(input);
    return false;
}

bool    Indie::Room::getPlayersPos(Server& server) const {
    if (_running) {
        _game->getPlayersPos(server);
        return true;
    }
    return false;
}

bool    Indie::Room::addBomb(std::string const& pId, int x, int y, int power) {
    if (_running) {
        _game->addBomb(pId, x, y, power);
        return true;
    }
    return false;
}

bool    Indie::Room::listBomb(std::string const& pId, Server& server) const {
    if (_running) {
        _game->listBomb(pId, server);
        return true;
    }
    return false;
}

void    Indie::Room::getPlayerList(Server& server) const {
    std::vector<std::string>::const_iterator    it = _playerList.begin();
    std::stringstream   ss;

    ss << "200";
    while (it != _playerList.end()) {
        ss << " " << *it;
        ++it;
    }
    server.setResponse(ss.str());
}

bool    Indie::Room::getKilledBy(std::string const& pId) {
    if (_running)
        return _game->getKilledBy(pId);
    return false;
}

bool    Indie::Room::getPowerUpList(Server& server) const {
    if (_running) {
        _game->getPowerUpList(server);
        return true;
    }
    return false;
}

bool    Indie::Room::takePowerUp(int powerUpId) {
    if (_running) {
        return _game->takePowerUp(powerUpId);
    }
    return false;
}

bool    Indie::Room::isRunning() const {
    return _running;
}

Indie::Room::~Room() {}