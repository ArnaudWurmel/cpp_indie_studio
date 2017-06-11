//
// Created by wurmel_a on 10/06/17.
//

#ifndef INDIE_SERVER_CONFPARSER_HH
#define INDIE_SERVER_CONFPARSER_HH

# include <string>
# include <utility>
# include "Router.hh"

# ifndef MAGIC_NUMBER
#  define MAGIC_NUMBER 0x4D42
# endif /* !MAGIC_NUMBER */

namespace Indie {
    class ConfParser {

    private:
        struct  ScoreFile {
            short   magicNumber;
            int     scoreValue;
        };


    public:
        static ConfParser  *getSingloton(bool reset = false);
    public:
        ConfParser(std::string const&);
        ~ConfParser();

    public:
        unsigned int    getPort() const;
        std::vector<Router::User> const&    getUserList() const;
        void            updateUserScoreFile(Router::User const&);

    private:
        void    loadServerConf();
        std::string getContentForSection(std::string const&);
        std::pair<std::string, std::string> getKeyValue(std::string const& line);

    private:
        void    setPort(std::string const&);
        void    loadUserList(std::string const&);

    private:
        void    setPasswordForUser(Router::User&, std::string const&) const;
        void    setScoreForUser(Router::User&, std::string const&) const;

    private:


    private:
        unsigned int    _port;

    private:
        std::string     _filepath;
        std::vector<Router::User>   _userList;
    };
}

#endif //INDIE_SERVER_CONFPARSER_HH
