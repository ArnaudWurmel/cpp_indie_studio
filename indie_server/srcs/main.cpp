#include <iostream>
#include "Router.hh"
#include "Server.h"

int main() {
    Indie::Router   router;
    Indie::Server   server(4242);
    int             fd;

    std::cout << router.parseLine("/user/connect") << std::endl;
    fd = server.accept_client();
    std::cout << "client fd: " << fd << std::endl;
    return 0;
}