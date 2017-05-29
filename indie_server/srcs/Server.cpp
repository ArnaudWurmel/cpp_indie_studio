//
// Created by ballet on 29/05/17.
//

#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Router.hh"
#include "Server.h"
#include "LinuxSocket.h"

Indie::Server::Server(int port) {
    _s_in.sin_family = AF_INET;
    _s_in.sin_port = htons(port);
    _s_in.sin_addr.s_addr = INADDR_ANY;
    _soc = std::unique_ptr<ISocket>(new Indie::LinuxSocket());
    if (bind(_soc->getFd(), reinterpret_cast<const struct sockaddr *>(&_s_in), sizeof(_s_in)) == -1)
        throw std::exception();
}

void    Indie::Server::serverLoop() {
    Router  router;

    try {
        while (true) {
            struct sockaddr    upaddrfrom;
            socklen_t fromLen = sizeof(upaddrfrom);
            char    buffer[4096];
            int     readSize;

            std::memset(_buffer, 0, 4096);
            readSize = recvfrom(_soc->getFd(), buffer, sizeof(buffer), 0, &upaddrfrom, &fromLen);
            if (readSize < 0) {
                throw std::exception();
            }
            buffer[readSize] = '\0';
            if (!router.parseLine(buffer)) {
                setResponse("500 Error");
            }
            if (sendto(_soc->getFd(), _buffer, sizeof(_buffer), 0, &upaddrfrom, fromLen) == -1)
                throw std::exception();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void    Indie::Server::setResponse(std::string const& res) {
    std::strncpy(_buffer, res.c_str(), 4096);
}

Indie::Server::~Server() {}