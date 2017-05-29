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

    public:
        Server(int port);
        ~Server();

    public:
        int accept_client();
    };
}

#endif //CPP_INDIE_STUDIO_SERVER_H
