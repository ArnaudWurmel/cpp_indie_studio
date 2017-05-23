//
// Created by wurmel on 13/05/17.
//

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
    while (true) {
        Ogre::WindowEventUtilities::messagePump();
        mSceneDisplayer->updateScene();
        if (mRenderWindow->isClosed() || !mRoot->renderOneFrame())
            return ;
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