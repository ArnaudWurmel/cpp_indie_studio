//
// Created by ballet on 24/05/17.
//

#ifndef PARSER_H_
# define PARSER_H_

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
        using cmdPtr = void (Router::*)(std::string const&);

    private:
        static const std::map<std::string, cmdPtr> fnc;
        static const std::vector<User> userList;

    private:
        void userConnect(std::string const&);
    };
}

#endif /* !PARSER_H_ */