//
// Created by ballet on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_SERVER_H
# define CPP_INDIE_STUDIO_SERVER_H

#include <bits/unique_ptr.h>
#include <netdb.h>
#include "ISocket.h"

namespace   Indie {
    class   Server {
    private:
        std::unique_ptr<ISocket>    _soc;
        struct sockaddr_in          _s_in;
        char                        _buffer[4096];

    public:
        Server(int port);
        ~Server();

    public:
        void    serverLoop();

    public:
        void    setResponse(std::string const&);
    };
}

#endif //CPP_INDIE_STUDIO_SERVER_H
