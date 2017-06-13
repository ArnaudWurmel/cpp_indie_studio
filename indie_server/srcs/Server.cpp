//
// Created by ballet on 29/05/17.
//

#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <zconf.h>
#include "Server.h"
#include "Router.hh"
#include "../../srcs/Exception/Exception.hh"

Indie::Server::Server(int port) {
    if ((_fd = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
        throw NetworkException();
    _s_in.sin_family = AF_INET;
    _s_in.sin_port = htons(port);
    _s_in.sin_addr.s_addr = INADDR_ANY;
    if (bind(_fd, reinterpret_cast<const struct sockaddr *>(&_s_in), sizeof(_s_in)) == -1)
        throw NetworkException();
}

void    Indie::Server::serverLoop() {
    Router  router;

    try {
        while (true) {
            struct sockaddr    upaddrfrom;
            socklen_t fromLen = sizeof(upaddrfrom);
            char    buffer[4096];
            ssize_t     readSize;

            std::memset(_buffer, 0, 4096);
            readSize = recvfrom(_fd, buffer, sizeof(buffer), 0, &upaddrfrom, &fromLen);
            if (readSize < 0) {
                throw NetworkException();
            }
            buffer[readSize] = '\0';
            std::cout << "Start parsing for " << buffer << std::endl;
            if (!router.parseLine(buffer, *this)) {
                setResponse("500 Error");
            }
            std::cout << "End parsing, result : " << _buffer << std::endl;
            if (sendto(_fd, _buffer, sizeof(_buffer), 0, &upaddrfrom, fromLen) == -1)
                throw NetworkException();
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void    Indie::Server::setResponse(std::string const& res) {
    std::strncpy(_buffer, res.c_str(), 4096);
}

Indie::Server::~Server() {
    if (_fd != -1)
        close(_fd);
}