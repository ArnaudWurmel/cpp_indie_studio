//
// Created by wurmel on 21/05/17.
//

#include <iostream>
#include <thread>
#include <chrono>
#include "EventListener.hh"

Indie::EventListener::EventListener(Ogre::SceneManager *sceneManager,
                                    Ogre::RenderWindow *renderWindow,
                                    MyGUI::Gui *GUI) {
    mSceneManager = sceneManager;
    mRenderWindow = renderWindow;
    mEventRegister = NULL;
    mGUI = GUI;
    this->initOIS();
}

void    Indie::EventListener::initOIS() {
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS");
    OIS::ParamList  pl;
    size_t windowHnd = 0;
    std::ostringstream    windowHndStr;
    unsigned int	w;
    unsigned int	h;
    unsigned int	d;
    int	left;
    int	top;

    mRenderWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    mInputManager = OIS::InputManager::createInputSystem(pl);
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
    mRenderWindow->getMetrics(w, h, d, left, top);
    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = w;
    ms.height = h;
}

void    Indie::EventListener::setUpEventRegister(AEventRegister *eventRegister) {
    Ogre::LogManager::getSingletonPtr()->logMessage("Event register setted.");
    mEventRegister = eventRegister;
    if (mEventRegister != NULL) {
        mKeyboard->setEventCallback(mEventRegister);
        mMouse->setEventCallback(mEventRegister);
    }
}

/***************************************
 * Event listener from now
 *
 * Handle : resized, closed, keyboard input
 */
void Indie::EventListener::windowResized(Ogre::RenderWindow *renderWindow) {
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    int          left;
    int          top;

    renderWindow->getMetrics(width, height, depth, left, top);
    const OIS::MouseState   &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

void Indie::EventListener::windowClosed(Ogre::RenderWindow *renderWindow) {
    if (renderWindow == mRenderWindow) {
        if (mInputManager) {
            mInputManager->destroyInputObject(mMouse);
            mInputManager->destroyInputObject(mKeyboard);

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = NULL;
        }
    }
}

bool Indie::EventListener::frameRenderingQueued(const Ogre::FrameEvent &evt) {

    if(mRenderWindow->isClosed())
        return false;
    if (mEventRegister) {
        mKeyboard->capture();
        mMouse->capture();
    }
    return true;
}

OIS::Keyboard   *Indie::EventListener::getKeyboard() const {
    return mKeyboard;
}

Indie::EventListener::~EventListener() {}