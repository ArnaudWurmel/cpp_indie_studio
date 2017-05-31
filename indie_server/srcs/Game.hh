//
// Created by wurmel_a on 29/05/17.
//

#ifndef INDIE_SERVER_GAME_HH
#define INDIE_SERVER_GAME_HH

# include <string>
# include <vector>
# include <memory>
# include "MapParser/MapParser.hh"
# include "Server.h"

namespace   Indie {

    class Game {
    public:
        struct  Player
        {
            Player(std::string const&);

            std::string     name;
            int             x;
            int             y;
            int    rotate;
        };
        struct  Bomb
        {
            unsigned int    id;
            unsigned int    x;
            unsigned int    y;
        };
    public:
        Game(std::vector<std::string> const&);
        ~Game();

    public:
        std::vector<std::string> const& getMap() const;
        bool    getPlayerPos(std::string const&, Server&) const;
        bool    findPosForPlayer(std::unique_ptr<Player>&);
        bool    addPlayerToGame(std::string const&);
        bool    updatePlayerPosition(std::vector<std::string> const&);
        void    exitPlayer(std::string const&);
        void    getPlayersPos(Server&);

    private:
        unsigned int    _bombId;
        std::vector<std::unique_ptr<Bomb> > _bombList;
        std::vector<std::unique_ptr<Player> >   _playerList;
        std::vector<std::string>   _map;
    };
}



#endif //INDIE_SERVER_GAME_HH
