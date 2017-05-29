//
// Created by ballet on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_SERVER_H
# define CPP_INDIE_STUDIO_SERVER_H

class server
{
private:
    struct protoent     *pe;
    struct sockaddr_in  s_in;
    int                 fd;
    int                 port;


public:
    server();
    ~server();

public:
    int accept_client();

};

#endif //CPP_INDIE_STUDIO_SERVER_H
