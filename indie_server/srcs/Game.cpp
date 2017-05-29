//
// Created by wurmel_a on 29/05/17.
//

#include <iostream>
#include "Game.hh"

Indie::Game::Player::Player(std::string const& pName) {
    name = pName;
}

Indie::Game::Game(std::vector<std::string> const& playerList) {
    _bombId = 0;
    std::vector<std::string>::const_iterator  it;

    MapParser   mapParser("maps/level0");
    _map = mapParser.getMap();
    it = playerList.begin();
    while (it != playerList.end()) {
        _playerList.push_back(std::unique_ptr<Player>(new Player(*it)));
        ++it;
    }
}

std::vector<std::string> const& Indie::Game::getMap() const {
    return _map;
}

Indie::Game::~Game() {}