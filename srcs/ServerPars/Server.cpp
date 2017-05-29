//
// Created by ballet on 29/05/17.
//

#include <netdb.h>
#include <zconf.h>
#include <cstdlib>
#include <exception>
#include "Server.h"

server::server() {
    if ((pe = getprotobyname("TCP")) == NULL)
        throw std::exception();
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(port);
    s_in.sin_addr.s_addr = INADDR_ANY;
    if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
        throw std::exception();
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

server::~server() {
    close(fd);
}

int server::accept_client() {
    struct sockaddr_in    s_in_client;
    socklen_t             s_in_client_size;
    int                   client_fd;
    pid_t                 pid;

    if ((client_fd = accept(fd, (struct sockaddr *)&s_in_client, &s_in_client_size)) == -1)
    {
        close(fd);
        throw std::exception();
    }
    return client_fd;
}
