//
// Created by ballet on 29/05/17.
//

#include <netdb.h>
#include <cstdlib>
#include <exception>
#include "Server.h"
#include "LinuxSocket.h"

Indie::Server::Server(int port) {
    _s_in.sin_family = AF_INET;
    _s_in.sin_port = htons(port);
    _s_in.sin_addr.s_addr = INADDR_ANY;
    _soc = std::unique_ptr<ISocket>(new Indie::LinuxSocket());
    if (bind(_soc->getFd(), reinterpret_cast<const struct sockaddr *>(&_s_in), sizeof(_s_in)) == -1)
        throw std::exception();
    if (listen(_soc->getFd(), 5) == -1)
        throw std::exception();
}

Indie::Server::~Server() {}

int Indie::Server::accept_client() {
    struct sockaddr_in    s_in_client;
    socklen_t             s_in_client_size;
    int                   client_fd;

    if ((client_fd = accept(_soc->getFd(), reinterpret_cast<struct sockaddr *>(&s_in_client), &s_in_client_size)) == -1)
        throw std::exception();
    return client_fd;
}
