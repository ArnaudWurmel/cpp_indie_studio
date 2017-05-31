//
// Created by ballet on 24/05/17.
//

#ifndef PARSER_H_
# define PARSER_H_

# include <vector>
# include <string>
# include <map>
# include "Server.h"

namespace   Indie {
    class   Router {
    public:
        struct  User
        {
            std::string username;
            std::string password;
        };

    public:
        Router();
        ~Router();

    public:
        bool    parseLine(std::string const&, Server&);

    private:
        using cmdPtr = bool (Router::*)(std::vector<std::string> const&, Server&) const;

    private:
        static const std::map<std::string, cmdPtr> fnc;
        static const std::vector<User> userList;

    private:
        bool userConnect(std::vector<std::string> const&, Server&) const;
        bool createRoom(std::vector<std::string> const&, Server&) const;
        bool getRoomList(std::vector<std::string> const&, Server&) const;
        bool joinRoom(std::vector<std::string> const&, Server&) const;
        bool exitRoom(std::vector<std::string> const&, Server&) const;
        bool runGame(std::vector<std::string> const&, Server&) const;
        bool getMap(std::vector<std::string> const&, Server&) const;
        bool getPlayerPosition(std::vector<std::string> const&, Server&) const;
    };
}

#endif /* !PARSER_H_ */