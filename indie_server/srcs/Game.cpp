//
// Created by wurmel_a on 29/05/17.
//

#include <iostream>
#include <string>
#include "Game.hh"

Indie::Game::Player::Player(std::string const& pName) {
    name = pName;
    x = -1;
    y = -1;
}

Indie::Game::Game(std::vector<std::string> const& playerList) {
    _bombId = 0;
    std::vector<std::string>::const_iterator  it;

    MapParser   mapParser("maps/level0");
    _map = mapParser.getMap();
    it = playerList.begin();
    while (it != playerList.end()) {
        std::cout << *it << std::endl;
        _playerList.push_back(std::unique_ptr<Player>(new Player(*it)));
        findPosForPlayer(_playerList.back());
        ++it;
    }
}

std::vector<std::string> const& Indie::Game::getMap() const {
    return _map;
}

bool    Indie::Game::getPlayerPos(std::string const& pName, Server& server) const {
    std::vector<std::unique_ptr<Player> >::const_iterator   it = _playerList.begin();

    while (it != _playerList.end()) {
        if (!(*it)->name.compare(pName)) {
            std::string res = "200 ";
            res += std::to_string((*it)->x);
            res += " ";
            res += std::to_string((*it)->y);
            server.setResponse(res);
            return true;
        }
        ++it;
    }
    return false;
}

bool    Indie::Game::findPosForPlayer(std::unique_ptr<Player>& player) {
    std::vector<std::string>::iterator  it = _map.begin();
    unsigned int    y = 0;

    while (it != _map.end()) {
        std::string::iterator   cell = (*it).begin();
        unsigned int    x = 0;

        while (cell != (*it).end()) {
            if (*cell == 'P') {
                player->y = (_map.size() * 100 / 2) - (y * 100);
                player->x = ((*it).size() * 100 / 2) - (x * 100);
                *cell = ' ';
                return true;
            }
            ++x;
            ++cell;
        }
        ++y;
        ++it;
    }
    return false;
}

void    Indie::Game::exitPlayer(std::string const& pName) {
    std::vector<std::unique_ptr<Player> >::iterator it = _playerList.begin();

    while (it != _playerList.end()) {
        if (!(*it)->name.compare(pName)) {
            _playerList.erase(it);
            return ;
        }
        ++it;
    }
}

bool    Indie::Game::addPlayerToGame(std::string const& pName) {
    _playerList.push_back(std::unique_ptr<Player>(new Player(pName)));
    if (!findPosForPlayer(_playerList.back())) {
        _playerList.erase(_playerList.end() - 1);
        return false;
    }
    return true;
}

Indie::Game::~Game() {}