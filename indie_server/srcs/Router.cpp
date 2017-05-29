//
// Created by ballet on 24/05/17.
//

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "Router.hh"

const std::map<std::string, Indie::Router::cmdPtr> Indie::Router::fnc = {
        { "/user/connect", &Indie::Router::userConnect}
};

const std::vector<Indie::Router::User> Indie::Router::userList = {
        { "Arnaud", "123" },
        { "Erwan", "123" },
        { "Thibaud", "123" }
};

Indie::Router::Router() {

}

void Indie::Router::userConnect(std::string const& input) {
}

Indie::Router::~Router() {}