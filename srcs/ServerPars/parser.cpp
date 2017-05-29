//
// Created by ballet on 24/05/17.
//

#include <string>
#include <map>
#include <iostream>
#include "parser.hpp"

const std::map<std::string, Indie::Parser::cmdPtr> Parser::fnc = {
        { "/user/connect", &Indie::Parser::userConnect}
};

void Indie::Parser::userConnect(std::string) {
    std::cout << "coucou" << std::endl;
}
