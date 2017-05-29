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

Indie::Router::Router() {}

bool    Indie::Router::userConnect(std::vector<std::string> const& input) {

    if (input.size() == 3) {
        return false;
    }
    return true;
}

bool    Indie::Router::parseLine(std::string const& input) {
    std::vector<std::string>    tokenList;
    std::string::const_iterator   it;

    it = input.begin();
    while (it != input.end()) {
        std::string token;
        while (it != input.end() && *it != ' ') {
            token += *it;
            ++it;
        }
        if (token.size())
            tokenList.push_back(token);
        while (it != input.end() && *it == ' ')
            ++it;
    }
    if (tokenList.size() > 0 && fnc.find(tokenList[0]) != fnc.end()) {
        cmdPtr ptr = (*fnc.find(tokenList[0])).second;
        return (this->*ptr)(tokenList);
    }
    return false;
}

Indie::Router::~Router() {}