//
// Created by ballet on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_DATAMANAGER_H
#define CPP_INDIE_STUDIO_DATAMANAGER_H

#ifdef WIN32

#include <winsock2.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

# define closesocket(s) close(s)

#endif

#include <string>
#include <OgreVector3.h>
#include <OgreSceneManager.h>
#include "../Models/Room.hh"


namespace   Indie {
    class DataManager {
    private:
        const std::string&  _ip;
        int                 _port;
        SOCKET              _sockfd;
        SOCKADDR_IN  _serv;
        SOCKADDR_IN  _client;

    private:
        DataManager(const std::string&, int);

    public:
        ~DataManager();

    public:
        static DataManager  *getSingloton(const std::string& ip = "192.168.1.1", int port = 4242, bool reset = false);
        bool                connect(const std::string&, const std::string&);
        bool                joinRoom(const std::string& userName, unsigned int roomId);
        bool                quitRoom(const std::string& userName);
        bool                getMap(unsigned int roomId, std::vector<std::string>&);
        Ogre::Vector3       getPlayerStart(std::string pName, bool&);
        void                updatePlayerPos(std::string const& pName, Ogre::Vector3 const&);
        void                updateAllPlayers(unsigned int roomId, Ogre::SceneManager *);
        void                addBomb(unsigned int, std::string const&, int, int, int);
        void                listBomb(unsigned int, std::string const&);
        bool                createRoom();
        std::vector<Room>   listRoom();
        std::vector<std::string>    getPlayerList();
        bool                gameIsRunning();
        void                runGame();
        void                getKilledBy(std::string const&);

    private:
        std::vector<std::string>    sendCommand(std::string const&);

    private:
        std::vector<std::string>    getTokenList(std::string const& line);
    };
}

#endif //CPP_INDIE_STUDIO_DATAMANAGER_H
