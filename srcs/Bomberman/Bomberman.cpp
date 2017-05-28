//
// Created by wurmel on 13/05/17.
//

#include <iostream>
#include <chrono>
#include "Bomberman.hh"

Indie::Bomberman::Bomberman() {

}

/*
 *  Load the engine
 */
bool Indie::Bomberman::loadApp() {
    mRoot = std::unique_ptr<Ogre::Root>(new Ogre::Root("resources/plugins.cfg", "resources/ogre.cfg", "resources/ogre.log"));
    this->loadResources();
    if (!(mRoot->restoreConfig() || mRoot->showConfigDialog())) {
        return false;
    }
    mRenderWindow = mRoot->initialise(true, "Bomberman");
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    mSceneManager = mRoot->createSceneManager("DefaultSceneManager", "Game Scene Manager");
    mSceneManager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
    this->createCamera();
    mSceneDisplayer = std::shared_ptr<Indie::SceneDisplayer>(new Indie::SceneDisplayer(mSceneManager));
    mSceneDisplayer->initScene();
    mEventListener = std::unique_ptr<Indie::EventListener>(new Indie::EventListener(mSceneManager, mRenderWindow));
    Ogre::WindowEventUtilities::addWindowEventListener(mRenderWindow, mEventListener.get());
    mRoot->addFrameListener(mEventListener.get());
    mEventListener->setUpEventRegister(mSceneDisplayer.get());
    return true;
}

void    Indie::Bomberman::createCamera() {
    Ogre::Viewport  *vp;

    mCamera = mSceneManager->createCamera("MainCam");
    mCamera->setPosition(Ogre::Vector3(-10, 500, 0));
    mCamera->lookAt(Ogre::Vector3(0, 0, 0));
    mCamera->setNearClipDistance(5);
    vp = mRenderWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

/*
 * Run ogre3d app
 */
void Indie::Bomberman::runApp() {
    Ogre::Real  timeSinceLastFrame = 0.0;
    float   timeStep = 1 / 60.0f;
    float   timeStepAccumulator = 0.0f;

    while (true) {
        Ogre::WindowEventUtilities::messagePump();
        timeStepAccumulator += timeSinceLastFrame;
        while (timeStepAccumulator >= timeStep) {
            if (!mSceneDisplayer->updateScene())
                return ;
            mSceneDisplayer->registerKeyboardEvent(mEventListener->getKeyboard());
            timeStepAccumulator -= timeStep;
        }
        std::chrono::time_point<std::chrono::system_clock> started = std::chrono::system_clock::now();

        if (mRenderWindow->isClosed() || !mRoot->renderOneFrame(timeSinceLastFrame))
            return ;
        std::chrono::time_point<std::chrono::system_clock> ended = std::chrono::system_clock::now();
        timeSinceLastFrame = (std::chrono::duration_cast<std::chrono::milliseconds>(ended - started).count());
        timeSinceLastFrame = timeSinceLastFrame / 1000.0f;
        if (timeSinceLastFrame > 1.0f)
            timeSinceLastFrame = 1.0f;
    }
}

/*
 * Load the necessary resources.
 */
void    Indie::Bomberman::loadResources() {
    Ogre::ConfigFile configFile;
    Ogre::String secName;
    Ogre::String typeName;
    Ogre::String archName;

    configFile.load("resources/resources.cfg");
    Ogre::ConfigFile::SectionIterator section = configFile.getSectionIterator();
    while (section.hasMoreElements())
    {
        secName = section.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = section.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
}

/*
 * Dtor
 */
Indie::Bomberman::~Bomberman() {
    Ogre::WindowEventUtilities::removeWindowEventListener(mRenderWindow, mEventListener.get());
    mEventListener->windowClosed(mRenderWindow);
    mRoot.reset();
    mEventListener.reset();
}