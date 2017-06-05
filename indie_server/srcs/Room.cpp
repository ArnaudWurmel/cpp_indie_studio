//
// Created by wurmel_a on 29/05/17.
//

#include <iostream>
#include "Room.hh"
#include "Server.h"

unsigned int Indie::Room::roomId = 0;

Indie::Room::Room() {
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

bool    Indie::Room::removePlayerFromRoom(std::string const& pName) {
    std::vector<std::string>::iterator  it = _playerList.begin();

    while (it != _playerList.end()) {
        if (!(*it).compare(pName)) {
            _playerList.erase(it);
            if (_running)
                _game->exitPlayer(pName);
            return true;
        }
        ++it;
    }
    return false;
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
    _running = true;
    _game = std::unique_ptr<Indie::Game>(new Indie::Game(_playerList));
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

bool    Indie::Room::addBomb(int x, int y) {
    if (_running) {
        _game->addBomb(x, y);
        return true;
    }
    return false;
}

Indie::Room::~Room() {}