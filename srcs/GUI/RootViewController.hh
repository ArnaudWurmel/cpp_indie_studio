//
// Created by wurmel_a on 06/06/17.
//

#ifndef CPP_INDIE_STUDIO_ROOTVIEWCONTROLLER_HH
#define CPP_INDIE_STUDIO_ROOTVIEWCONTROLLER_HH

# include <Ogre.h>
# include <memory>
# include <MYGUI/MyGUI.h>
# include <MYGUI/MyGUI_OgrePlatform.h>
# include "../EventListener/EventListener.hh"
# include "AViewController.hh"

namespace   Indie {
    class RootViewController : public Indie::AEventRegister {
    public:
        RootViewController();
        ~RootViewController();

    public:
        bool    loadApp();
        void    runApp();

    public:
        void    addViewController(AViewController *);

    public:
        std::unique_ptr<Ogre::Root>&    getOgreRoot();
        std::unique_ptr<Indie::EventListener>&  getEventListener();
        Ogre::RenderWindow  *getRenderWindow();
        Ogre::SceneManager  *getSceneManager();
        MyGUI::Gui  *getGUI();
        MyGUI::OgrePlatform *getOgrePlatform();

    private:
        void loadResources();
        void createCamera();

    public:
        bool    mouseMoved(const OIS::MouseEvent&);
        bool    mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
        bool    mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);
        bool    keyPressed(const OIS::KeyEvent&);
        bool    keyReleased(const OIS::KeyEvent&);
        void    registerKeyboardEvent(OIS::Keyboard *);
        void    registerMouseEvent(OIS::Mouse *);

    private:
        std::unique_ptr<Ogre::Root> mRoot;
        std::unique_ptr<Indie::EventListener>   mEventListener;
        std::vector<std::unique_ptr<Indie::AViewController> >   mControllerList;
        Ogre::RenderWindow          *mRenderWindow;
        Ogre::SceneManager          *mSceneManager;
        Ogre::Camera                *mCamera;
        MyGUI::OgrePlatform *mPlatform;
        MyGUI::Gui  *mGUI;
    };
}

#endif //CPP_INDIE_STUDIO_ROOTVIEWCONTROLLER_HH
