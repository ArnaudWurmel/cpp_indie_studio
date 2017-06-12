//
// Created by wurmel on 13/05/17.
//

#ifndef CPP_INDIE_STUDIO_SCENEMANAGER_HH
#define CPP_INDIE_STUDIO_SCENEMANAGER_HH

# include <memory>
# include <map>
# include <Ogre.h>
# include <OIS/OIS.h>
# include <thread>
# include <mutex>
# include <MYGUI/MyGUI.h>
# include "../MapParser/MapParser.hh"
# include "../Entities/AEntity.hh"
# include "../Player/APlayer.hh"
# include "../EventListener/AEventRegister.hh"
# include "../GUI/RootViewController.hh"

#ifdef WIN32
# define KEY_UP (OIS::KC_W)
# define KEY_DOWN (OIS::KC_S)
# define KEY_LEFT (OIS::KC_A)
# define KEY_RIGHT (OIS::KC_D)
#else
# define KEY_UP (OIS::KC_Z)
# define KEY_DOWN (OIS::KC_S)
# define KEY_LEFT (OIS::KC_Q)
# define KEY_RIGHT (OIS::KC_D)
#endif


namespace   Indie
{
    class SceneDisplayer : public Indie::AEventRegister {
    public:
        SceneDisplayer(Ogre::SceneManager *);
        ~SceneDisplayer();

    public:
        void    initScene(RootViewController&);
        bool    updateScene();
        void    viewShouldDisapear();

    private:
        void    createGround();
        void    createMap();
        void    updaterThread();

    private:
        bool    makeCollide(std::unique_ptr<APlayer>&, OIS::KeyCode const&);

        bool    checkUp(std::unique_ptr<APlayer>&, std::shared_ptr<AEntity> const&) const;
        bool    checkDown(std::unique_ptr<APlayer>&, std::shared_ptr<AEntity> const&) const;
        bool    checkLeft(std::unique_ptr<APlayer>&, std::shared_ptr<AEntity> const&) const;
        bool    checkRight(std::unique_ptr<APlayer>&, std::shared_ptr<AEntity> const&) const;
        /*
         * Callback for 'AEventRegister'
         */
    public:
        void    initEventRegister();
        void    registerKeyboardEvent(OIS::Keyboard *keyboard);
        void    registerMouseEvent(OIS::Mouse *mouse);
        bool    keyPressed(const OIS::KeyEvent& ke);
        bool    keyReleased(const OIS::KeyEvent& ke);
        virtual bool    mouseMoved(const OIS::MouseEvent&);
        virtual bool    mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
        virtual bool    mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);

    private:
        void    toggleScoreboard();
        void    initScoreboard(RootViewController&);

    private:
        void    setFPSCameraPosition();

    private:
        void    movePlayerUp(OIS::Keyboard *);
        void    movePlayerDown(OIS::Keyboard *);
        void    movePlayerLeft(OIS::Keyboard *);
        void    movePlayerRight(OIS::Keyboard *);
        void    moveCameraUp(OIS::Keyboard *);
        void    moveCameraDown(OIS::Keyboard *);

    private:
        std::map<OIS::KeyCode, void (Indie::SceneDisplayer::*)(OIS::Keyboard *)> _functionPtr;
        std::map<OIS::KeyCode, bool (Indie::SceneDisplayer::*)(std::unique_ptr<APlayer>&, std::shared_ptr<AEntity> const&) const>  _collideGetter;

    private:
        Ogre::SceneManager  *mSceneManager;
        std::vector<std::vector<Indie::MapParser::TileType> >   _map;
        std::unique_ptr<std::thread>    _thread;
        std::mutex  _locker;
        Ogre::Entity    *mGroundEntity;
        bool    mFPSmode;

        /*
         * Scoreboard usefull variables
         */
    private:
        bool    mToggleScoreboard;
        MyGUI::MultiListBox  *mScoreboard;

    private:
        std::vector<std::unique_ptr<AEntity> >  _groundEntityList;
    };
}

#endif //CPP_INDIE_STUDIO_SCENEMANAGER_HH
