//
// Created by wurmel_a on 08/06/17.
//

#include "Room.hh"

Indie::Room::Room(unsigned int roomId, unsigned int nbPlayers) {
    _roomId = roomId;
    _nbPlayers = nbPlayers;
}

unsigned int const &Indie::Room::getRoomID() const {
    return _roomId;
}

unsigned int const &Indie::Room::getNbPlayers() const {
    return _nbPlayers;
}

Indie::Room::~Room() {}