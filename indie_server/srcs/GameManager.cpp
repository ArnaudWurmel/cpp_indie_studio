//
// Created by wurmel_a on 29/05/17.
//

#include <iostream>
#include <string>
#include "GameManager.hh"

Indie::GameManager *Indie::GameManager::getSingleton(bool reset) {
    static Indie::GameManager   *singleton = NULL;

    if (singleton == NULL) {
        singleton = new Indie::GameManager();
    }
    if (reset) {
        delete singleton;
        singleton = NULL;
    }
    singleton->lock();
    return singleton;
}

Indie::GameManager::GameManager() {

}

unsigned int const& Indie::GameManager::createRoom() {
    Indie::Room *room = new Indie::Room();

    _roomList.push_back(std::unique_ptr<Indie::Room>(room));
    return room->getRoomId();
}

bool Indie::GameManager::joinRoom(unsigned int const& roomId, std::string const& pName) {
    std::vector<std::unique_ptr<Indie::Room> >::iterator  it = _roomList.begin();

    while (it != _roomList.end()) {
        std::vector<std::string>::const_iterator  itPlayer = (*it)->getPlayerList().begin();

        while (itPlayer != (*it)->getPlayerList().end()) {
            if (!(*itPlayer).compare(pName))
                return false;
            ++itPlayer;
        }
        ++it;
    }
    it = _roomList.begin();
    while (it != _roomList.end()) {
        if ((*it)->getRoomId() == roomId) {
            return (*it)->addPlayerToRoom(pName);
        }
        ++it;
    }
    return false;
}

std::vector<std::unique_ptr<Indie::Room> > const&   Indie::GameManager::getRoomList() {
    return _roomList;
}

void    Indie::GameManager::exitRoom(std::string const& pName) {
    std::vector<std::unique_ptr<Indie::Room> >::iterator  it = _roomList.begin();

    while (it != _roomList.end()) {
        (*it)->removePlayerFromRoom(pName);
        if (!(*it)->getPlayerList().size()) {
            _roomList.erase(it);
        }
        else {
            ++it;
        }
    }
}

bool    Indie::GameManager::runGame(unsigned int const& roomId) {
    std::vector<std::unique_ptr<Indie::Room> >::iterator    it = _roomList.begin();

    while (it != _roomList.end()) {
        if ((*it)->getRoomId() == roomId) {
            return (*it)->runGame();
        }
        ++it;
    }
    return false;
}

bool    Indie::GameManager::getMap(unsigned int const& roomId, Server& server) const {
    std::vector<std::unique_ptr<Indie::Room> >::const_iterator    it = _roomList.begin();

    while (it != _roomList.end()) {
        if ((*it)->getRoomId() == roomId) {
            return (*it)->getMap(server);
        }
        ++it;
    }
    return false;
}

bool    Indie::GameManager::getPlayerPosition(std::string const& pName, Server& server) const {
    std::vector<std::unique_ptr<Room> >::const_iterator it;

    it = _roomList.begin();
    while (it != _roomList.end()) {
        if ((*it)->getPlayerPos(pName, server))
            return true;
        ++it;
    }
    return false;
}

bool Indie::GameManager::updatePlayerPosition(std::vector<std::string> const& input) {
    std::vector<std::unique_ptr<Room> >::iterator   it;

    it = _roomList.begin();
    while (it != _roomList.end()) {
        if ((*it)->updatePlayerPosition(input))
            return true;
        ++it;
    }
    return false;
}

bool    Indie::GameManager::getPlayersPosition(int roomId, Server& server) const {
    std::vector<std::unique_ptr<Room> >::const_iterator   it;

    it = _roomList.begin();
    while (it != _roomList.end()) {
        if ((*it)->getRoomId() == roomId) {
            return (*it)->getPlayersPos(server);
        }
        ++it;
    }
    return false;
}

bool    Indie::GameManager::addBomb(int roomId, std::string const& pId, int x, int y, int power) {
    std::vector<std::unique_ptr<Room> >::iterator   it;

    it = _roomList.begin();
    while (it != _roomList.end()) {
        if ((*it)->getRoomId() == roomId)
            return (*it)->addBomb(pId, x, y, power);
        ++it;
    }
    return false;
}

bool    Indie::GameManager::listBomb(int roomId, std::string const& pId, Server& server) const {
    std::vector<std::unique_ptr<Room> >::const_iterator   it;

    it = _roomList.begin();
    while (it != _roomList.end()) {
        if ((*it)->getRoomId() == roomId) {
            return (*it)->listBomb(pId, server);
        }
    }
}

void Indie::GameManager::lock() {
    _mutexLock->lock();
}

void Indie::GameManager::release() {
    _mutexLock->unlock();
}

Indie::GameManager::~GameManager() {}
