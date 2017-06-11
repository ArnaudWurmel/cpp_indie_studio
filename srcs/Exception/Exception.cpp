//
// Created by wurmel_a on 11/06/17.
//

#include "Exception.hh"

Indie::Exception::Exception(std::string const& what) {
    _what = what;
}

const char* Indie::Exception::what() const throw() {
    return _what.c_str();
}

Indie::Exception::~Exception() {}

Indie::NetworkException::NetworkException() : Exception("Network Error, connexion reset by peer") {}
Indie::NetworkException::~NetworkException() {}

Indie::EntityManagerException::EntityManagerException() : Exception("EntityManager exception") {}
Indie::EntityManagerException::~EntityManagerException() {}

Indie::GameException::GameException() : Exception("A game exception occured, check your program version") {}
Indie::GameException::~GameException() {}

Indie::FileParsingError::FileParsingError() : Exception("File may have modified by user, can't load") {}
Indie::FileParsingError::~FileParsingError() {}