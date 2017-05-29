//
// Created by ballet on 29/05/17.
//

#include <sys/socket.h>
#include <exception>
#include "LinuxSocket.h"

Indie::LinuxSocket::LinuxSocket() {
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw std::exception();
}
