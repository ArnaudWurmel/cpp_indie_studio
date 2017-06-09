//
// Created by ballet on 29/05/17.
//

#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include "DataManager.h"
#include "../Entities/EntityManager.hh"
#include "../UserManager/User.hh"

Indie::DataManager::DataManager(const std::string& ip, int port) : _ip(ip), _port(port)  {
    if ((_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        throw std::exception();
    _serv.sin_family = AF_INET;
    _serv.sin_port = htons(_port);
    _serv.sin_addr.s_addr = inet_addr(_ip.c_str());
}

Indie::DataManager::~DataManager() {}

Indie::DataManager *Indie::DataManager::getSingloton(const std::string& ip, int port, bool reset) {
    static Indie::DataManager *data = NULL;

    if (data == NULL)
        data = new Indie::DataManager(ip, port);
    if (reset)
    {
        delete data;
        data = NULL;
    }
    return data;
}

bool                    Indie::DataManager::connect(const std::string& login, const std::string& pass)
{
    std::string         tmp = "/user/connect ";

    tmp = tmp + login + " " + pass;
    std::vector<std::string>    tokenList = sendCommand(tmp);
    if (tokenList.size() == 0 || std::atoi(tokenList[0].c_str()) != 200)
        return false;
    User::getUser(login, pass);
    return true;
}

bool Indie::DataManager::joinRoom(const std::string &userName, unsigned int roomId) {
    std::string         tmp = "/room/joinRoom ";

    tmp = tmp + std::to_string(roomId) + " " + userName;
    std::vector<std::string>    tokenList = sendCommand(tmp);
    if (tokenList.size() == 0 || std::atoi(tokenList[0].c_str()) != 200)
        return false;
    User::getUser()->joinRoomId(roomId);
    return true;
}

bool Indie::DataManager::quitRoom(const std::string &userName) {
    std::string         tmp = "/room/quitRoom ";

    tmp = tmp + userName;
    std::vector<std::string>    tokenList = sendCommand(tmp);
    if (tokenList.size() == 0 || std::atoi(tokenList[0].c_str()) != 200)
        return false;
    return true;
}

bool                            Indie::DataManager::getMap(unsigned int roomId, std::vector<std::string>& map) {
    std::string                 tmp = "/game/getMap ";
    char                        buf[4097];
    std::string                 mapTmp;
    std::stringstream           mapss;
    std::string                 readTmp;
    int                         ret;
    socklen_t                   client_size;
    socklen_t                   server_size;

    tmp = tmp + std::to_string(roomId);
    std::strncpy(buf, tmp.c_str(), 4096);
    client_size = sizeof(_client);
    server_size = sizeof(_serv);
    if (sendto(_sockfd, buf, sizeof(buf), 0, reinterpret_cast<struct sockaddr *>(&_serv), server_size) == -1)
        return false;
    if ((ret = recvfrom(_sockfd, buf, sizeof(buf), 0, reinterpret_cast<struct sockaddr *>(&_client), &client_size)) == -1)
        return false;
    buf[ret] = 0;
    if (std::atoi(buf) != 200)
        return false;
    if (std::strlen(buf) > 4)
        mapTmp = std::string(&buf[4]);
    mapss << mapTmp;
    while (std::getline(mapss, readTmp))
        map.push_back(readTmp);
    return true;
}

Ogre::Vector3 Indie::DataManager::getPlayerStart(std::string pName, bool& success) {
    std::string         tmp = "/game/getPlayerPos ";
    char                buf[4097];
    int                 ret;
    socklen_t           client_size;
    socklen_t           server_size;

    tmp += pName;
    std::strncpy(buf, tmp.c_str(), 4096);
    client_size = sizeof(_client);
    server_size = sizeof(_serv);
    if (sendto(_sockfd, buf, sizeof(buf), 0, reinterpret_cast<struct sockaddr *>(&_serv), server_size) == -1) {
        success = false;
        return Ogre::Vector3();
    }
    if ((ret = recvfrom(_sockfd, buf, sizeof(buf), 0, reinterpret_cast<struct sockaddr *>(&_client), &client_size)) == -1) {
        success = false;
        return Ogre::Vector3();
    }
    buf[ret] = 0;
    if (std::atoi(buf) != 200) {
        success = false;
        return Ogre::Vector3();
    }
    success = true;
    Ogre::Vector3   pos;

    int idx = 0;
    while (buf[idx] && buf[idx] != ' ')
        ++idx;
    if (!buf[idx])
        success = false;
    else
        ++idx;
    pos.z = std::atoi(&buf[idx]);
    while (buf[idx] && buf[idx] != ' ')
        ++idx;
    if (!buf[idx])
        success = false;
    else
        ++idx;
    pos.x = std::atoi(&buf[idx]);
    return pos;
}

void    Indie::DataManager::updatePlayerPos(std::string const &pName, Ogre::Vector3 const& entityPos) {
    std::string route = "/game/updatePlayer ";

    route = route + pName + " " + std::to_string(entityPos.z) + " " + std::to_string(entityPos.x) + " " + std::to_string(EntityManager::getMainPlayer()->getRotation());
    std::vector<std::string>    tokenList = sendCommand(route);
    if (tokenList.size() == 0 || std::atoi(tokenList[0].c_str()) != 200)
        std::cerr << "Update player failed" << std::endl;
}

void Indie::DataManager::updateAllPlayers(unsigned int roomId, Ogre::SceneManager *sceneManager) {
    std::string route = "/game/getPlayersPos ";

    route = route + std::to_string(roomId);
    std::vector<std::string>    tokenList = sendCommand(route);
    if (tokenList.size() == 0 || std::atoi(tokenList[0].c_str()) != 200)
        return ;
    std::vector<std::unique_ptr<APlayer> >::iterator    it = EntityManager::getPlayerList().begin();
    while (it != EntityManager::getPlayerList().end()) {
        (*it)->setUpdate(false);
        ++it;
    }
    if ((tokenList.size() - 1) % 4 != 0 || tokenList.size() - 1 <= 0)
        return ;
    unsigned int i = 1;
    while (i < tokenList.size()) {
        bool    found = false;

        it = EntityManager::getPlayerList().begin();

        while (it != EntityManager::getPlayerList().end()) {
            if (!(*it)->getPlayerId().compare(tokenList[i])) {
                found = true;
                Ogre::Vector3   newPos;
                newPos.x = std::atoi(tokenList[i + 2].c_str()) - (*it)->getPosition().x;
                newPos.y = 0;
                newPos.z = std::atoi(tokenList[i + 1].c_str()) - (*it)->getPosition().z;
                (*it)->move(newPos);
                (*it)->rotate(std::atoi(tokenList[i + 3].c_str()));
                (*it)->setUpdate(true);
            }
            ++it;
        }
        if (!found && EntityManager::getMainPlayer()->getPlayerId().compare(tokenList[i])) {
            APlayer *player = EntityManager::createEnemy(sceneManager, Ogre::Vector3(std::atoi(tokenList[i + 2].c_str()), 30, std::atoi(tokenList[i + 1].c_str())), tokenList[i]);
            player->rotate(std::atoi(tokenList[i + 3].c_str()));
            player->setUpdate(true);
        }
        i += 4;
    }
    it = EntityManager::getPlayerList().begin();
    while (it != EntityManager::getPlayerList().end()) {
        if (!(*it)->isUpdate()) {
            (*it)->explode(NULL);
        }
        ++it;
    }
}

void    Indie::DataManager::addBomb(unsigned int roomId, std::string const& pId, int x, int y, int power) {
    std::string route = "/game/addBomb ";

    route = route + std::to_string(roomId) + " " + pId + " " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(power);
    std::vector<std::string>    tokenList = sendCommand(route);
    if (tokenList.size() == 0 || std::atoi(tokenList[0].c_str()) != 200)
        std::cerr << "add failed" << std::endl;
}

void    Indie::DataManager::listBomb(unsigned int roomId, std::string const& pId) {
    std::string route = "/game/bombList ";

    route = route + std::to_string(roomId) + " " + pId;
    std::vector<std::string>    tokenList = sendCommand(route);
    if (tokenList.size() == 0 || std::atoi(tokenList[0].c_str()) != 200)
        return ;
    if ((tokenList.size() - 1) % 4 != 0 || tokenList.size() - 1 <= 0)
        return ;
    unsigned int i = 1;
    while (i < tokenList.size()) {
        bool    found = false;

        std::vector<std::unique_ptr<Bomb> >::const_iterator it = EntityManager::getBombList().begin();

        while (!found && it != EntityManager::getBombList().end()) {
            if ((*it)->getID() == std::atoi(tokenList[i].c_str())) {
                found = true;
            }
            ++it;
        }
        if (!found) {
            Indie::Bomb *bomb = new Bomb(std::atoi(tokenList[i].c_str()), std::atoi(tokenList[i + 2].c_str()), std::atoi(tokenList[i + 1].c_str()), std::atoi(tokenList[i + 3].c_str()));
            EntityManager::addBomb(bomb);
        }
        i += 4;
    }
}

std::vector<Indie::Room>    Indie::DataManager::listRoom() {
    std::string route = "/room/getRoomList";
    std::vector<Room>   retValue;

    std::vector<std::string>    tokenList = sendCommand(route);
    if (tokenList.size() == 0 || std::atoi(tokenList[0].c_str()) != 200)
        return retValue;

    if ((tokenList.size() - 1) % 2 != 0 || tokenList.size() - 1 <= 0)
        return retValue;
    unsigned int    i = 1;
    while (i < tokenList.size()) {
        int roomId = std::atoi(tokenList[i].c_str());
        int nbPlayers = std::atoi(tokenList[i + 1].c_str());
        if (roomId >= 0 && nbPlayers >= 0)
            retValue.push_back(Room(roomId, nbPlayers));
        i += 2;
    }
    return retValue;
}

bool    Indie::DataManager::createRoom() {
    std::string route = "/room/createRoom ";

    route += User::getUser()->getLogName();

    std::vector<std::string>    tokenList = sendCommand(route);
    if (tokenList.size() == 0 || std::atoi(tokenList[0].c_str()) != 200)
        return false;
    if (tokenList.size() != 2)
        return false;
    User::getUser()->joinRoomId(std::atoi(tokenList[1].c_str()));
    return true;
}

std::vector<std::string>    Indie::DataManager::getPlayerList() {
    std::string route = "/room/getPlayersList ";
    std::vector<std::string>    res;

    route += std::to_string(User::getUser()->getRoomId());

    std::vector<std::string>    tokenList = sendCommand(route);
    if (tokenList.size() == 0 || std::atoi(tokenList[0].c_str()) != 200)
        return res;
    unsigned int    i = 1;
    while (i < tokenList.size()) {
        res.push_back(tokenList[i]);
        ++i;
    }
    return res;
}

bool    Indie::DataManager::gameIsRunning() {
    std::string route = "/room/getState ";

    route += std::to_string(User::getUser()->getRoomId());

    std::vector<std::string>    tokenList = sendCommand(route);
    if (tokenList.size() != 2 || std::atoi(tokenList[0].c_str()) != 200)
        return false;
    return std::atoi(tokenList[1].c_str()) == 1;
}

void    Indie::DataManager::runGame() {
    std::string route = "/room/runGame ";

    route += std::to_string(User::getUser()->getRoomId());
    sendCommand(route);
}

std::vector<std::string>    Indie::DataManager::sendCommand(std::string const& route) {
    char                buf[4097];
    int                 ret;
    socklen_t           client_size;
    socklen_t           server_size;

    std::strncpy(buf, route.c_str(), 4096);
    client_size = sizeof(_client);
    server_size = sizeof(_serv);
    if (sendto(_sockfd, buf, sizeof(buf), 0, reinterpret_cast<struct sockaddr *>(&_serv), server_size) == -1)
        throw std::exception();
    if ((ret = recvfrom(_sockfd, buf, sizeof(buf), 0, reinterpret_cast<struct sockaddr *>(&_client), &client_size)) == -1)
        throw std::exception();
    buf[ret] = 0;
    return getTokenList(buf);
}

std::vector<std::string>    Indie::DataManager::getTokenList(std::string const& line) {
    std::vector<std::string>    tokenList;

    std::string::const_iterator   it;

    it = line.begin();
    while (it != line.end()) {
        std::string token;
        while (it != line.end() && *it != ' ') {
            token += *it;
            ++it;
        }
        if (token.size())
            tokenList.push_back(token);
        while (it != line.end() && *it == ' ')
            ++it;
    }
    return tokenList;
}