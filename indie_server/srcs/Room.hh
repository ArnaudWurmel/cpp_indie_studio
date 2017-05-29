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
        bool    removePlayerFromRoom(std::string const&);
        bool    runGame();
        bool    getMap(Server&);

    public:
        static unsigned int roomId;

    private:
        std::vector<std::string>   _playerList;
        unsigned int                _roomId;
        bool    _running;
        std::unique_ptr<Game>   _game;
    };
}

#endif //INDIE_SERVER_ROOM_HH
