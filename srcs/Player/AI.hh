//
// Created by ballet_e on 6/7/17.
//

#ifndef CPP_INDIE_STUDIO_AI_HH
# define CPP_INDIE_STUDIO_AI_HH

# include <Ogre.h>
# include <vector>
# include <utility>
# include "APlayer.hh"
# include "../Entities/ExplosableEntity.hh"

namespace   Indie
{
    class   AI : public APlayer
    {
    private:
        enum map
        {
            EMPTY = 0,
            STATIC_BLOCK,
            DYNAMIC_BLOCK,
            ENEMY_PLAYER,
            AI_PLAYER,
            BOMB,
        };

    private:
        std::vector<std::vector<map>>     _map;
        std::pair<unsigned int, unsigned int>   _myPos;
        std::pair<unsigned int, unsigned int>   _enemyPos;
        std::vector<std::pair<unsigned int, unsigned int>>  _path;

    public:
        AI(Ogre::Vector3 const& entityPos, Ogre::SceneManager *sceneManager, std::string const& pId, bool mainP = false);
        ~AI();

    private:
        void    createMap();
        void    addPlayers(std::vector<std::unique_ptr<Indie::APlayer>>&, std::unique_ptr<Indie::APlayer>&);
        void    addBlock(std::vector<std::shared_ptr<Indie::AEntity>>& blockList);
        void    initMap(unsigned long, unsigned long);
        void    drawMap();
        void    findEnemy();
        void    findPath();
    };
}

#endif //CPP_INDIE_STUDIO_AI_HH
