//
// Created by ballet on 24/05/17.
//

#ifndef PARSER_H_
# define PARSER_H_

# include <vector>
# include <string>
# include <map>

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
        bool    parseLine(std::string const&);

    private:
        using cmdPtr = bool (Router::*)(std::vector<std::string> const&);

    private:
        static const std::map<std::string, cmdPtr> fnc;
        static const std::vector<User> userList;

    private:
        bool userConnect(std::vector<std::string> const&);
    };
}

#endif /* !PARSER_H_ */