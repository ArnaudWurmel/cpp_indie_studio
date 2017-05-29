//
// Created by wurmel_a on 29/05/17.
//

#include "Room.hh"

unsigned int Indie::Room::roomId = 0;

Indie::Room::Room() {
    _roomId = roomId;
    Indie::Room::roomId += 1;
}

bool    Indie::Room::addPlayerToRoom(std::string const& pName) {
    if (_playerList.size() < 4 && !_running) {
        _playerList.push_back(pName);
        return true;
    }
    return false;
}

bool    Indie::Room::removePlayerFromRoom(std::string const& pName) {
    std::vector<std::string>::iterator  it = _playerList.begin();

    if (!_running)
        return false;
    while (it != _playerList.end()) {
        if (!(*it).compare(pName)) {
            _playerList.erase(it);
            return true;
        }
        ++it;
    }
    return false;
}

/*
 * TODO Init game ressources (pList, etc..)
 */
bool    Indie::Room::runGame() {
    if (_running)
        return false;
    _running = true;
    _game = std::unique_ptr<Indie::Game>(new Indie::Game(_playerList));
    return _running;
}

unsigned int const& Indie::Room::getRoomId() const {
    return _roomId;
}

std::vector<std::string> const& Indie::Room::getPlayerList() {
    return _playerList;
}

Indie::Room::~Room() {

}
