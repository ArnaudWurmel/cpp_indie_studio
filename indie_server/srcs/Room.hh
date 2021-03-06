//
// Created by wurmel_a on 29/05/17.
//

#ifndef INDIE_SERVER_ROOM_HH
#define INDIE_SERVER_ROOM_HH

# include <vector>
# include <string>
# include "Game.hh"
# include "Server.h"

namespace Indie
{
    class Room {
    public:
        Room();
        ~Room();

    public:
        bool    addPlayerToRoom(std::string const&);
        unsigned int const&   getRoomId() const;
        std::vector<std::string> const& getPlayerList();
        unsigned int    removePlayerFromRoom(std::string const&);
        bool    runGame();
        bool    getMap(Server&);
        bool    getPlayerPos(std::string const&, Server&);
        bool    updatePlayerPosition(std::vector<std::string> const&);
        bool    getPlayersPos(Server&) const;
        bool    addBomb(std::string const&, int, int, int);
        bool    listBomb(std::string const&, Server&) const;
        void    getPlayerList(Server&) const;
        bool    isRunning() const;
        bool    getKilledBy(std::string const&);
        bool    getPowerUpList(Server&) const;
        bool    takePowerUp(int powerUpId);
    public:
        std::string const&  getCurrentMap() const;
        void    setNextMap();

    public:
        static unsigned int roomId;

    private:
        std::vector<std::string>::iterator  _currentMap;
        std::vector<std::string>    _mapList;
        std::vector<std::string>   _playerList;
        unsigned int                _roomId;
        bool    _running;
        std::unique_ptr<Game>   _game;
    };
}

#endif //INDIE_SERVER_ROOM_HH
