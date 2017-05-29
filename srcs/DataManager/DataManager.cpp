//
// Created by ballet on 29/05/17.
//

#include <cstring>
#include <sstream>
#include <vector>
#include "DataManager.h"

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
    char                buf[4097];
    int                 ret;
    socklen_t           client_size;
    socklen_t           server_size;

    tmp = tmp + login + " " + pass;
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
    return true;
}

bool Indie::DataManager::joinRoom(const std::string &userName, unsigned int roomId) {
    std::string         tmp = "/game/joinRoom ";
    char                buf[4097];
    int                 ret;
    socklen_t           client_size;
    socklen_t           server_size;

    tmp = tmp + std::to_string(roomId) + " " + userName;
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
    return true;
}

bool Indie::DataManager::quitRoom(const std::string &userName) {
    std::string         tmp = "/game/quitRoom ";
    char                buf[4097];
    int                 ret;
    socklen_t           client_size;
    socklen_t           server_size;

    tmp = tmp + userName;
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
    return true;
}

#include <iostream>

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
    std::cout << buf << std::endl;
    if (std::atoi(buf) != 200)
        return false;
    if (std::strlen(buf) > 4)
        mapTmp = std::string(&buf[4]);
    mapss << mapTmp;
    while (std::getline(mapss, readTmp))
        map.push_back(readTmp);
    return true;
}

Ogre::Vector3 Indie::DataManager::getPlayerStart(unsigned int roomId, std::string pName) {

}


