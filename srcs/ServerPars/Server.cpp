//
// Created by ballet on 29/05/17.
//

#include <netdb.h>
#include <zconf.h>
#include <cstdlib>
#include <exception>
#include "Server.h"

Indie::server::server() {
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(port);
    s_in.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
        close(fd);
        throw std::exception();
    }
    if (listen(fd, 5) == -1)
    {
        close(fd);
        throw std::exception();
    }
}

Indie::server::~server() {
    close(fd);
}

int Indie::server::accept_client() {
    struct sockaddr_in    s_in_client;
    socklen_t             s_in_client_size;
    int                   client_fd;

    if ((client_fd = accept(fd, (struct sockaddr *)&s_in_client, &s_in_client_size)) == -1)
    {
        close(fd);
        throw std::exception();
    }
    return client_fd;
}
