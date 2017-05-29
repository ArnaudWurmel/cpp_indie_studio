//
// Created by ballet on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_SERVER_H
# define CPP_INDIE_STUDIO_SERVER_H

namespace   Indie {
    class   Server {
    private:
        struct sockaddr_in s_in;
        int fd;
        int port;


    public:
        Server();
        ~Server();

    public:
        int accept_client();
    };
}

#endif //CPP_INDIE_STUDIO_SERVER_H
