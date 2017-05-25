//
// Created by wurmel on 13/05/17.
//

#ifndef CPP_INDIE_STUDIO_SCENEMANAGER_HH
#define CPP_INDIE_STUDIO_SCENEMANAGER_HH

# include <memory>
# include <map>
# include <Ogre.h>
# include <OIS/OIS.h>
# include "../MapParser/MapParser.hh"
# include "../Entities/AEntity.hh"
# include "../Player/APlayer.hh"
# include "../EventListener/AEventRegister.hh"

namespace   Indie
{
    class SceneDisplayer : public Indie::AEventRegister {
    public:
        SceneDisplayer(Ogre::SceneManager *);
        ~SceneDisplayer();

    public:
        void    initScene();
        void    updateScene();

    private:
        void    createGround();
        void    createMap();

    private:
        bool    makeCollide(std::unique_ptr<AEntity>&, OIS::KeyCode const&);

        bool    checkUp(std::unique_ptr<AEntity> const&, std::unique_ptr<AEntity> const&) const;
        bool    checkDown(std::unique_ptr<AEntity> const&, std::unique_ptr<AEntity> const&) const;
        bool    checkLeft(std::unique_ptr<AEntity> const&, std::unique_ptr<AEntity> const&) const;
        bool    checkRight(std::unique_ptr<AEntity> const&, std::unique_ptr<AEntity> const&) const;
        /*
         * Callback for 'AEventRegister'
        */
    public:
        void    initEventRegister();
        void    registerKeyboardEvent(OIS::Keyboard *keyboard);
        void    registerMouseEvent(OIS::Mouse *mouse);

    private:
        void    movePlayerUp(OIS::Keyboard *);
        void    movePlayerDown(OIS::Keyboard *);
        void    movePlayerLeft(OIS::Keyboard *);
        void    movePlayerRight(OIS::Keyboard *);
        void    moveCameraUp(OIS::Keyboard *);
        void    moveCameraDown(OIS::Keyboard *);

    private:
        std::map<OIS::KeyCode, void (Indie::SceneDisplayer::*)(OIS::Keyboard *)> _functionPtr;
        std::map<OIS::KeyCode, bool (Indie::SceneDisplayer::*)(std::unique_ptr<AEntity> const&, std::unique_ptr<AEntity> const&) const>  _collideGetter;

    private:
        Ogre::SceneManager  *mSceneManager;
        std::vector<std::vector<Indie::MapParser::TileType> >   _map;
        std::vector<std::unique_ptr<AEntity>>    _entityList;
        std::unique_ptr<AEntity>  _player;
    };
}

#endif //CPP_INDIE_STUDIO_SCENEMANAGER_HH
