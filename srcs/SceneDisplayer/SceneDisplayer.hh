//
// Created by wurmel on 13/05/17.
//

#ifndef CPP_INDIE_STUDIO_SCENEMANAGER_HH
#define CPP_INDIE_STUDIO_SCENEMANAGER_HH

# include <memory>
# include <Ogre.h>
# include "../MapParser/MapParser.hh"
# include "../Entities/AEntity.hh"

namespace   Indie
{
    class SceneDisplayer {
    public:
        SceneDisplayer(Ogre::SceneManager *);
        ~SceneDisplayer();

    public:
        void    initScene();

    private:
        void    createGround();
        void    createMap();

    private:
        Ogre::SceneManager  *mSceneManager;
        std::vector<std::vector<Indie::MapParser::TileType> >   _map;
        std::vector<std::unique_ptr<AEntity>>    _entityList;
    };
}

#endif //CPP_INDIE_STUDIO_SCENEMANAGER_HH
