//
// Created by wurmel_a on 07/06/17.
//

#include "User.hh"

Indie::User *Indie::User::getUser(std::string const& logName, std::string const& passwd) {
    static User *user = NULL;

    if (user == NULL)
        user = new User(logName, passwd);
    return user;
}

Indie::User::User(std::string const& logName, std::string const& passwd) {
    _logName = logName;
    _passwd = passwd;
    _roomId = -1;
}

std::string const&  Indie::User::getLogName() const {
    return _logName;
}

int Indie::User::getRoomId() const {
    return _roomId;
}

void    Indie::User::joinRoomId(int roomId) {
    _roomId = roomId;
}

Indie::User::~User() {}
