//
// Created by ballet on 29/05/17.
//

#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "DataManager.h"

Indie::DataManager::DataManager(const std::string& ip, int port) : _ip(ip), _port(port)  {}

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
    int                 sockfd;
    struct sockaddr_in  serv;
    std::string         tmp = "/user/connect ";
    char                buf[4096];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
        return false;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(_port);
    serv.sin_addr.s_addr = inet_addr(_ip);
    tmp = tmp + login + " " + pass;
    std::strncpy(buf, tmp.c_str(), 4096);
    if (sendto(sockfd, buf, sizeof(buf), 0, dynamic_cast<struct sockaddr *>(&serv), sizeof(serv)) == -1)
        return false;
    return true;
}