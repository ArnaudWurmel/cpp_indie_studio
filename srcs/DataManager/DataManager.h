//
// Created by ballet on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_DATAMANAGER_H
#define CPP_INDIE_STUDIO_DATAMANAGER_H

#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <OgreVector3.h>


namespace   Indie {
    class DataManager {
    private:
        const std::string&  _ip;
        int                 _port;
        int                 _sockfd;
        struct sockaddr_in  _serv;
        struct sockaddr_in  _client;

    private:
        DataManager(const std::string&, int);
        ~DataManager();

    public:
        static DataManager  *getSingloton(const std::string&, int, bool reset = false);
        bool                connect(const std::string&, const std::string&);
        bool                joinRoom(const std::string& userName, unsigned int roomId);
        bool                quitRoom(const std::string& userName);
        bool                getMap(unsigned int roomId, std::vector<std::string>&);
        Ogre::Vector3       getPlayerStart(unsigned int roomId, std::string pName);
    };
}

#endif //CPP_INDIE_STUDIO_DATAMANAGER_H
