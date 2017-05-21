//
// Created by wurmel on 21/05/17.
//

#include "EventListener.hh"

Indie::EventListener::EventListener(Ogre::SceneManager *sceneManager,
                                    Ogre::RenderWindow *renderWindow) {
    mSceneManager = sceneManager;
    mRenderWindow = renderWindow;
    this->initOIS();
}

void    Indie::EventListener::initOIS() {
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS");
    OIS::ParamList  pl;
    size_t windowHnd = 0;
    std::ostringstream    windowHndStr;

    mRenderWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    mInputManager = OIS::InputManager::createInputSystem(pl);
    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, false ));
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
    mKeyboard->capture();
    mMouse->capture();
    if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
        return false;
    handleKeyboard();
    return true;
}

void Indie::EventListener::handleKeyboard() {
    Ogre::Vector3   move(mSceneManager->getCamera("MainCam")->getPositionForViewUpdate());

    if (mKeyboard->isKeyDown(OIS::KC_Z))
        move = Ogre::Vector3(move.x - 1, move.y, move.z);
    if (mKeyboard->isKeyDown(OIS::KC_S))
        move = Ogre::Vector3(move.x + 1, move.y, move.z);
    if (mKeyboard->isKeyDown(OIS::KC_Q))
        move = Ogre::Vector3(move.x, move.y, move.z + 1);
    if (mKeyboard->isKeyDown(OIS::KC_D))
        move = Ogre::Vector3(move.x, move.y, move.z - 1);
    if (mKeyboard->isKeyDown(OIS::KC_UP))
        move = Ogre::Vector3(move.x, move.y + 1, move.z);
    if (mKeyboard->isKeyDown(OIS::KC_DOWN))
        move = Ogre::Vector3(move.x, move.y - 1, move.z);
    mSceneManager->getCamera("MainCam")->setPosition(move);
    mSceneManager->getCamera("MainCam")->lookAt(Ogre::Vector3(0, 0, 0));
}

Indie::EventListener::~EventListener() {}
