//
// Created by wurmel_a on 10/06/17.
//

#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include "ConfParser.hh"

Indie::ConfParser    *Indie::ConfParser::getSingloton(bool reset) {
    static Indie::ConfParser    *confParser = NULL;

    if (!confParser)
        confParser = new Indie::ConfParser("server.ini");
    if (reset) {
        delete confParser;
        confParser = NULL;
    }
    return confParser;
}

Indie::ConfParser::ConfParser(std::string const& filepath) {
    _port = 4242;
    _filepath = filepath;
    loadServerConf();
}

unsigned int    Indie::ConfParser::getPort() const {
    return _port;
}

std::vector<Indie::Router::User> const& Indie::ConfParser::getUserList() const {
    return _userList;
}

std::string    Indie::ConfParser::getContentForSection(std::string const& section) {
    std::ifstream file(_filepath.c_str());
    std::string res;
    std::string line;
    bool    end = false;
    bool    inSection = false;

    if (file.is_open()) {
        while (!end && std::getline(file, line)) {
            if (inSection && line.compare("[/" + section + "]"))
                res = res + line + "\n";
            if (!inSection && !line.compare("[" + section + "]"))
                inSection = true;
            else if (!line.compare("[" + section + "]"))
                throw std::exception();
            if (inSection && !line.compare("[/" + section + "]"))
                end = true;
            else if (!inSection && !line.compare("[/" + section + "]"))
                throw std::exception();
        }
        file.close();
    }
    if (res.size() == 0)
        throw std::exception();
    return res;
}

std::pair<std::string, std::string> Indie::ConfParser::getKeyValue(std::string const& line) {
    std::pair<std::string, std::string> ret;
    std::string::const_iterator it = line.begin();

    while (it != line.end() && *it != '=') {
        ret.first += *it;
        ++it;
    }
    if (it == line.end())
        throw std::exception();
    ++it;
    if (*it != '\"')
        throw std::exception();
    ++it;
    if (it == line.end())
        throw std::exception();
    while (it != line.end() && *it != '\"') {
        ret.second += *it;
        ++it;
    }
    if (it == line.end())
        throw std::exception();
    return ret;
}

void    Indie::ConfParser::setPort(std::string const& line) {
    int port = std::atoi(line.c_str());

    if (port <= 0)
        throw std::exception();
    _port = port;
}

void    Indie::ConfParser::loadUserList(std::string const& userLine) {
    std::string userName;
    std::string::const_iterator it = userLine.begin();
    std::map<std::string, void (Indie::ConfParser::*)(Router::User&, std::string const&) const > functionPtr;

    functionPtr.insert(std::make_pair("PASS", &Indie::ConfParser::setPasswordForUser));
    functionPtr.insert(std::make_pair("SCORE_FILE", &Indie::ConfParser::setScoreForUser));
    while (it != userLine.end()) {
        if (*it == ';' && userName.size()) {
            try {
                Router::User    user;
                std::stringstream ss(getContentForSection(userName));
                std::string lineParsed;

                user.score = 0;
                user.password = "";
                user.username = userName;
                while (std::getline(ss, lineParsed)) {
                    std::pair<std::string, std::string> keyValue = getKeyValue(lineParsed);

                    if (functionPtr.find(keyValue.first) != functionPtr.end()) {
                        (this->*functionPtr[keyValue.first])(user, keyValue.second);
                    }
                }
                _userList.push_back(user);
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }
            userName.clear();
        }
        else
            userName += *it;
        ++it;
    }

}

void    Indie::ConfParser::loadServerConf() {
    std::string loaded;
    try {
        loaded = getContentForSection("SERVER_CONF");
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return ;
    }
    std::map<std::string, void (Indie::ConfParser::*)(std::string const&) > functionPtr;
    std::stringstream   ss(loaded);
    std::string         line;

    functionPtr.insert(std::make_pair("PORT", &Indie::ConfParser::setPort));
    functionPtr.insert(std::make_pair("USERS", &Indie::ConfParser::loadUserList));
    while (std::getline(ss, line)) {
        std::pair<std::string, std::string> keyValue = getKeyValue(line);

        if (functionPtr.find(keyValue.first) != functionPtr.end()) {
            (this->*functionPtr[keyValue.first])(keyValue.second);
        }
    }
}

void    Indie::ConfParser::setPasswordForUser(Router::User& user, std::string const& value) const {
    user.password = value;
}

void    Indie::ConfParser::setScoreForUser(Router::User& user, std::string const& scoreFile) const {
    std::ifstream    scoreStream(scoreFile);
    ScoreFile       header;

    user.scoreFilePath = scoreFile;
    if (scoreStream.is_open()) {
        scoreStream.read(reinterpret_cast<char *>(&header), sizeof(header));
        if (header.magicNumber != MAGIC_NUMBER || header.scoreValue <= 0)
            throw std::exception();
        user.scoreFilePath = scoreFile;
        user.score = header.scoreValue;
        scoreStream.close();
    }
}

void    Indie::ConfParser::updateUserScoreFile(Router::User const& user) {
    std::ofstream   scoreStream;

    scoreStream.open(user.scoreFilePath, std::ios::trunc);
    if (scoreStream.is_open()) {
        ScoreFile   header;
        header.magicNumber = MAGIC_NUMBER;
        header.scoreValue = user.score;
        scoreStream.write(reinterpret_cast<char *>(&header), sizeof(header));
        scoreStream.close();
    }
}

Indie::ConfParser::~ConfParser() {}