//
// Created by wurmel_a on 29/05/17.
//

#include <iostream>
#include <sstream>
#include <algorithm>
#include "Game.hh"
#include "../../srcs/Exception/Exception.hh"

unsigned int    Indie::Game::Bomb::bombId = 0;
unsigned int    Indie::Game::PowerUp::powerUpId = 0;

Indie::Game::Player::Player(std::string const& pName) {
    name = pName;
    x = -1;
    y = -1;
    this->gameScore = 0;
}

Indie::Game::Bomb::Bomb(std::string const& pId, int x_pos, int y_pos, int power) {
    this->pId = pId;
    x = x_pos;
    y = y_pos;
    this->power = power;
    id = Indie::Game::Bomb::bombId;
    Indie::Game::Bomb::bombId = Indie::Game::Bomb::bombId + 1;
}

Indie::Game::PowerUp::PowerUp(std::pair<int, int> const& powerPos) {
    std::vector<PowerUp::PowerUpType>   powerList;

    powerList.push_back(PowerUpType::BOMB_BOOST);
    powerList.push_back(PowerUpType::BOMB_RANGE);
    powerList.push_back(PowerUpType::SPEED);
    type = powerList[std::rand() % powerList.size()];
    id = powerUpId;
    pos.first = powerPos.first;
    pos.second = powerPos.second;
    powerUpId += 1;
}

Indie::Game::Game(std::vector<std::string> const& playerList, std::string const& mapFile) {
    std::vector<std::string>::const_iterator  it;

    MapParser   mapParser(mapFile);
    _map = mapParser.getMap();
    if (_map.size() == 0)
        throw GameException();
    it = playerList.begin();
    while (it != playerList.end()) {
        _playerList.push_back(std::unique_ptr<Player>(new Player(*it)));
        findPosForPlayer(_playerList.back());
        ++it;
    }
    getAllPowerUpAvailablePos();
    std::random_shuffle(_powerUpPos.begin(), _powerUpPos.end());
    createPowerUp(20);
}

void    Indie::Game::createPowerUp(unsigned int nbPower) {
    unsigned int    i = 0;

    while (i < nbPower && _powerUpPos.size() > 0) {
        std::pair<int, int> pos(_powerUpPos.back());

        _powerUpList.push_back(std::unique_ptr<PowerUp>(new PowerUp(pos)));
        _powerUpPos.pop_back();
        ++i;
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
                player->y = ((_map.size() * 100 / 2) - (y * 100));
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

unsigned int    Indie::Game::exitPlayer(std::string const& pName) {
    std::vector<std::unique_ptr<Player> >::iterator it = _playerList.begin();

    while (it != _playerList.end()) {
        if (!(*it)->name.compare(pName)) {
            unsigned int score = (*it)->gameScore;
            _playerList.erase(it);
            return score;
        }
        ++it;
    }
    return 0;
}

bool    Indie::Game::addPlayerToGame(std::string const& pName) {
    _playerList.push_back(std::unique_ptr<Player>(new Player(pName)));
    if (!findPosForPlayer(_playerList.back())) {
        _playerList.erase(_playerList.end() - 1);
        return false;
    }
    return true;
}

bool    Indie::Game::updatePlayerPosition(std::vector<std::string> const& input) {
    std::vector<std::unique_ptr<Player> >::iterator it = _playerList.begin();

    while (it != _playerList.end()) {
        if (!(*it)->name.compare(input[1])) {
            (*it)->x = std::atoi(input[2].c_str());
            (*it)->y = std::atoi(input[3].c_str());
            (*it)->rotate = std::atoi(input[4].c_str());
            return true;
        }
        ++it;
    }
    return false;
}

void    Indie::Game::getPlayersPos(Server& server) const {
    std::stringstream   ss;
    std::vector<std::unique_ptr<Player> >::const_iterator it = _playerList.begin();

    ss << "200";
    while (it != _playerList.end()) {
        ss << " " << (*it)->name << " " << (*it)->x << " " << (*it)->y << " " << (*it)->rotate << " " << (*it)->gameScore;
        ++it;
    }
    ss << std::endl;
    server.setResponse(ss.str());
}

void    Indie::Game::addBomb(std::string const& pId, int x, int y, int power) {
    _bombList.push_back(std::unique_ptr<Bomb>(new Bomb(pId, x, y, power)));
}

void    Indie::Game::listBomb(std::string const& pId, Server& server) const {
    std::stringstream   ss;
    std::vector<std::unique_ptr<Bomb> >::const_iterator it = _bombList.begin();

    ss << "200";
    while (it != _bombList.end()) {
        if ((*it)->pId.compare(pId)) {
            ss << " " << (*it)->pId << " " << (*it)->id << " " << (*it)->x << " " << (*it)->y << " " << (*it)->power;
        }
        ++it;
    }
    ss << std::endl;
    server.setResponse(ss.str());
}

void    Indie::Game::getAllPowerUpAvailablePos() {
    std::vector<std::string>::iterator  it = _map.begin();
    long   x;
    long   y;

    y = 0;
    _powerUpPos.clear();
    while (it != _map.end()) {
        x = 0;
        std::string::iterator itString = (*it).begin();

        while (itString != (*it).end()) {
            if ((*itString) == '0') {
                long gamePos_x = ((*it).size() * 100 / 2) - (x * 100);
                long gamePos_y = (_map.size() * 100 / 2) - (y * 100);
                _powerUpPos.push_back(std::make_pair(gamePos_y, gamePos_x));
            }
            ++itString;
            ++x;
        }
        ++y;
        ++it;
    }
}

bool    Indie::Game::getKilledBy(std::string const& pId) {
    std::vector<std::unique_ptr<Player> >::iterator it = _playerList.begin();

    while (it != _playerList.end()) {
        std::cout << (*it)->name << " " << pId << std::endl;
        if ((*it)->name.compare(pId) == 0) {
            (*it)->gameScore += 10;
            return true;
        }
        ++it;
    }
    return false;
}

void    Indie::Game::getPowerUpList(Server& server) const {
    std::stringstream   ss;
    std::vector<std::unique_ptr<PowerUp> >::const_iterator  it = _powerUpList.begin();

    ss << "200";
    while (it != _powerUpList.end()) {
        ss << " " << (*it)->id << " " << (*it)->pos.first << " " << (*it)->pos.second << " " << (*it)->type;
        ++it;
    }
    server.setResponse(ss.str());
}

bool    Indie::Game::takePowerUp(int powerUpId) {
    std::vector<std::unique_ptr<PowerUp> >::iterator    it = _powerUpList.begin();

    while (it != _powerUpList.end()) {
        std::cout << powerUpId << " " << (*it)->id << std::endl;
        if ((*it)->id == powerUpId) {
            _powerUpList.erase(it);
            return true;
        }
        ++it;
    }
    return false;
}

Indie::Game::~Game() {}