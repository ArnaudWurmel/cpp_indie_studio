//
// Created by wurmel on 21/05/17.
//

#ifndef CPP_INDIE_STUDIO_EVENTLISTENER_HH
#define CPP_INDIE_STUDIO_EVENTLISTENER_HH

# include <map>
# include "AEventRegister.hh"
# include <OgreWindowEventUtilities.h>
# include <Ogre.h>
# include <OIS/OIS.h>

namespace Indie {
    class EventListener : public Ogre::WindowEventListener, public Ogre::FrameListener {
    public:
        EventListener(Ogre::SceneManager *, Ogre::RenderWindow *);
        ~EventListener();

    public:
        /*
         * Start registering event if mEventRegister is set
         */
        void    setUpEventRegister(AEventRegister *);

    public:
        /*
         * Ogre::WindowEventListener
         */
        virtual void windowResized(Ogre::RenderWindow *);
        virtual void windowClosed(Ogre::RenderWindow *);
        /*
         * Ogre::FrameListener
         */
        virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    private:
        void    handleKeyboard();

    private:
        void    initOIS();

    private:
        AEventRegister  *mEventRegister;

    private:
        Ogre::SceneManager  *mSceneManager;
        Ogre::RenderWindow  *mRenderWindow;

    private:
        OIS::InputManager   *mInputManager;
        OIS::Mouse          *mMouse;
        OIS::Keyboard       *mKeyboard;
    };
}


#endif //CPP_INDIE_STUDIO_EVENTLISTENER_HH
