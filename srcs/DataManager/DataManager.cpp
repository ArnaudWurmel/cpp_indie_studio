//
// Created by ballet on 29/05/17.
//

#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "DataManager.h"

Indie::DataManager::DataManager(const std::string& ip, int port) : _ip(ip), _port(port)  {
    if ((_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        throw std::exception();
    _serv.sin_family = AF_INET;
    _serv.sin_port = htons(_port);
    _serv.sin_addr.s_addr = inet_addr(_ip);
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
    char                buf[4096];

    tmp = tmp + login + " " + pass;
    std::strncpy(buf, tmp.c_str(), 4096);
    if (sendto(_sockfd, buf, sizeof(buf), 0, dynamic_cast<struct sockaddr *>(&_serv), sizeof(_serv)) == -1)
        return false;
    return true;
}

bool Indie::DataManager::joinRoom(const std::string &userName, unsigned int roomId) {
    std::string         tmp = "/game/joinRoom ";
    char                buf[4096];

    tmp = tmp + std::to_string(roomId) + " " + userName;
    std::strncpy(buf, tmp.c_str(), 4096);
    if (sendto(_sockfd, buf, sizeof(buf), 0, dynamic_cast<struct sockaddr *>(&_serv), sizeof(_serv)) == -1)
        return false;
    return true;
}

bool Indie::DataManager::quitRoom(const std::string &userName) {
    std::string         tmp = "/game/quitRoom ";
    char                buf[4096];

    tmp = tmp + userName;
    std::strncpy(buf, tmp.c_str(), 4096);
    if (sendto(_sockfd, buf, sizeof(buf), 0, dynamic_cast<struct sockaddr *>(&_serv), sizeof(_serv)) == -1)
        return false;
    return true;
}

bool Indie::DataManager::getMap(unsigned int roomId) {
    std::string         tmp = "/game/quitRoom ";
    char                buf[4096];

    tmp = tmp + std::to_string(roomId);
    std::strncpy(buf, tmp.c_str(), 4096);
    if (sendto(_sockfd, buf, sizeof(buf), 0, dynamic_cast<struct sockaddr *>(&_serv), sizeof(_serv)) == -1)
        return false;
    return true;
}


