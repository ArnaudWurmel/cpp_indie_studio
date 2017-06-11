//
// Created by wurmel_a on 11/06/17.
//

#ifndef CPP_INDIE_STUDIO_EXCEPTION_HH
#define CPP_INDIE_STUDIO_EXCEPTION_HH

# include <exception>
# include <string>

namespace Indie {
    class Exception : public std::exception {
    public:
        Exception(std::string const&);
        ~Exception();

    public:
        virtual char const* what() const throw();

    private:
        std::string _what;
    };

    class NetworkException : public Exception {
    public:
        NetworkException();
        ~NetworkException();
    };

    class EntityManagerException : public Exception {
    public:
        EntityManagerException();
        ~EntityManagerException();
    };

    class GameException : public Exception {
    public:
        GameException();
        ~GameException();
    };

    class FileParsingError : public Exception {
    public:
        FileParsingError();
        ~FileParsingError();
    };
}

#endif //CPP_INDIE_STUDIO_EXCEPTION_HH
