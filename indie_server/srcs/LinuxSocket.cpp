//
// Created by ballet on 29/05/17.
//

#include <zconf.h>
#include <sys/socket.h>
#include <exception>
#include "LinuxSocket.h"

Indie::LinuxSocket::LinuxSocket() {
    if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::exception();
}

Indie::LinuxSocket::~LinuxSocket() {
    close(_fd);
}

int Indie::LinuxSocket::getFd() {
    return _fd;
}
