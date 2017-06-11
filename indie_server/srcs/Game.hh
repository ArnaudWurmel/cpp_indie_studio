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
            int     rotate;
            int     gameScore;
        };
        struct  Bomb
        {
            static unsigned int bombId;

        public:
            Bomb(std::string const&, int, int, int);

            unsigned int    id;
            int    x;
            int    y;
            std::string pId;
            int     power;
        };

    public:
        struct  PowerUp {
        public:
            enum    PowerUpType {
                BOMB_BOOST = 0,
                BOMB_RANGE = 1,
                SPEED
            };
        public:
            static unsigned int powerUpId;

        public:
            PowerUp(std::pair<int, int> const&);

            unsigned int    id;
            PowerUpType     type;
            std::pair<int, int> pos;
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
        unsigned int    exitPlayer(std::string const&);
        void    getPlayersPos(Server&) const;
        void    addBomb(std::string const&, int, int, int);
        void    listBomb(std::string const&, Server&) const;
        bool    getKilledBy(std::string const&);
        void    getPowerUpList(Server&) const;

    private:
        void    getAllPowerUpAvailablePos();
        void    createPowerUp(unsigned int);

    private:
        std::vector<std::unique_ptr<Bomb> > _bombList;
        std::vector<std::unique_ptr<Player> >   _playerList;
        std::vector<std::string>   _map;
        std::vector<std::unique_ptr<PowerUp> >  _powerUpList;
        std::vector<std::pair<long, long> >   _powerUpPos;
    };
}



#endif //INDIE_SERVER_GAME_HH
