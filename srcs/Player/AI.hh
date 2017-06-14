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
            STATIC_BLOCK = 1,
            DYNAMIC_BLOCK = 2,
            ENEMY_PLAYER = 3,
            AI_PLAYER = 4,
            BOMB = 5,
            ALREADY_PASS = 6
        };
        enum dir
        {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT
        };

    private:
		typedef bool (Indie::AI::*fncPtr)();
		typedef bool (Indie::AI::*posPtr)(std::pair<unsigned int, unsigned int> &, Indie::AI::dir);

    private:
        std::vector<fncPtr> fncTab;
        std::vector<posPtr> posFncTab;
        std::vector<std::vector<map>>     _map;
        std::pair<unsigned int, unsigned int>   _myPos;
        std::pair<unsigned int, unsigned int>   _enemyPos;
        std::vector<std::pair<unsigned int, unsigned int>>  _path;
        dir     _heuristic[4];

    public:
        AI(Ogre::Vector3 const& entityPos, Ogre::SceneManager *sceneManager, std::string const& pId, bool mainP = false);
        ~AI();

    public:
        bool    updateFromLoop(Ogre::SceneManager *);

    private:
        bool    isForward();
        bool    isBackward();
        bool    isRight();
        bool    isLeft();

    private:
        bool    addForward(std::pair<unsigned int, unsigned int>&, dir);
        bool    addBackward(std::pair<unsigned int, unsigned int>&, dir);
        bool    addLeft(std::pair<unsigned int, unsigned int>&, dir);
        bool    addRight(std::pair<unsigned int, unsigned int>&, dir);

    private:
        void    createMap();
        void    addPlayers(std::vector<std::unique_ptr<Indie::APlayer>>&, std::unique_ptr<Indie::APlayer>&);
        void    addBlock(std::vector<std::shared_ptr<Indie::AEntity>>& blockList);
        void    initMap(unsigned long, unsigned long);
        void    resetMap();
        void    drawMap();
        bool    findEnemy();
        void    findPath();
        void    findHeuristic();
        void    addDir(dir, std::pair<unsigned int, unsigned int>&);
        bool    findNextPos(std::pair<unsigned int, unsigned int>&);
        bool    isANode(const std::pair<unsigned int, unsigned int>&);
        void    escapeBomb();
    };
}

#endif //CPP_INDIE_STUDIO_AI_HH
