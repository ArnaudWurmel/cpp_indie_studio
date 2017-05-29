#include <iostream>
#include "Router.hh"
#include "Server.h"

int main() {
    Indie::Router   router;
    Indie::Server   server(4242);
    int             fd;

    server.serverLoop();
    return 0;
}