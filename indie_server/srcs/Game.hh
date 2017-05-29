//
// Created by wurmel_a on 29/05/17.
//

#ifndef INDIE_SERVER_GAME_HH
#define INDIE_SERVER_GAME_HH

# include <string>
# include <vector>
# include <memory>
# include "MapParser/MapParser.hh"

namespace   Indie {

    class Game {
    public:
        struct  Player
        {
            Player(std::string const&);

            std::string     name;
            unsigned int    x;
            unsigned int    y;
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

    private:
        unsigned int    _bombId;
        std::vector<std::unique_ptr<Bomb> > _bombList;
        std::vector<std::unique_ptr<Player> >   _playerList;
        std::vector<std::vector<Indie::MapParser::TileType> >   _map;
    };
}



#endif //INDIE_SERVER_GAME_HH
