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
#include "../Map/Map.h"

namespace   Indie
{
    class   AIPlayer : public APlayer {
    public:
        enum dir
        {
            FORWARD = 0,
            BACKWARD,
            LEFT,
            RIGHT,
            NOTHING
        };

    private:
        using fncPtr = bool (AIPlayer::*)(std::pair<int, int>, std::pair<int, int>);
        using posPtr = bool (AIPlayer::*)(std::pair<int, int>&, dir);
        using dirPtr = bool (AIPlayer::*)(std::pair<int, int>&, std::pair<int, int>&);


    private:
        dir     _heuristic[4];
        static const std::vector<fncPtr> fncTab;
        static const std::vector<dirPtr> dirTab;
        std::vector<std::pair<int, int>> _path;
        static const std::vector<posPtr> posFncTab;

    private:
        bool    isForward(std::pair<int, int>, std::pair<int, int>);
        bool    isBackward(std::pair<int, int>, std::pair<int, int>);
        bool    isRight(std::pair<int, int>, std::pair<int, int>);
        bool    isLeft(std::pair<int, int>, std::pair<int, int>);
        bool    addForward(std::pair<int, int>&, dir);
        bool    addBackward(std::pair<int, int>&, dir);
        bool    addLeft(std::pair<int, int>&, dir);
        bool    addRight(std::pair<int, int>&, dir);
        bool    onTop(std::pair<int, int>&, std::pair<int, int>&);
        bool    onBot(std::pair<int, int>&, std::pair<int, int>&);
        bool    onLeft(std::pair<int, int>&, std::pair<int, int>&);
        bool    onRight(std::pair<int, int>&, std::pair<int, int>&);


    public:
        dir     getDir();

    private:
        void    findHeuristic(std::pair<int, int>, std::pair<int, int>);
        void    findPath(Indie::Map);
        void    addDir(dir, std::pair<int, int>&);
        bool    findNextPos(std::pair<int, int>&, std::vector<std::vector<Indie::Map::map>>);
        bool    isANode(const std::pair<int, int>&);
        std::pair<int, int>     getMyPos(int, int);
        std::pair<int, int>     getClosestEnemy(int, int);
        bool    updateFromLoop(Ogre::SceneManager *);

    public:
        AIPlayer(Ogre::Vector3 const& entityPos, Ogre::SceneManager *sceneManager, std::string const& pId, bool mainP = false);
        ~AIPlayer();
    };
}

#endif //CPP_INDIE_STUDIO_AI_HH
