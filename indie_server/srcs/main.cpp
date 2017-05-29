#include <iostream>
#include "Router.hh"

int main() {
    Indie::Router   router;

    std::cout << router.parseLine("/user/connect") << std::endl;
    return 0;
}