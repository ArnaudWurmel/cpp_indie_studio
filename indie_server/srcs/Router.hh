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
            User();
            ~User();

            std::string username;
            std::string password;
            size_t      score;
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

    private:
        bool userConnect(std::vector<std::string> const&, Server&) const;
        bool createRoom(std::vector<std::string> const&, Server&) const;
        bool getRoomList(std::vector<std::string> const&, Server&) const;
        bool joinRoom(std::vector<std::string> const&, Server&) const;
        bool exitRoom(std::vector<std::string> const&, Server&);
        bool runGame(std::vector<std::string> const&, Server&) const;
        bool getMap(std::vector<std::string> const&, Server&) const;
        bool getPlayerPosition(std::vector<std::string> const&, Server&) const;
        bool updatePlayerPosition(std::vector<std::string> const&, Server&) const;
        bool getPlayerList(std::vector<std::string> const&, Server&) const;
        bool addBomb(std::vector<std::string> const&, Server&) const;
        bool listBomb(std::vector<std::string> const&, Server&) const;
        bool getWaitingPlayerList(std::vector<std::string> const&, Server&) const;
        bool getRoomState(std::vector<std::string> const&, Server&) const;

    private:
        std::vector<User> userList;
    };
}

#endif /* !PARSER_H_ */