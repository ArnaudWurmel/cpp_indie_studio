//
// Created by wurmel on 01/05/17.
//

#include "AppManager.hh"

/*
 * The implementation of the root
 * This class load and execute ogre function
 */

/*
 * Default Constructor
 */
IndieStudio::AppManager::AppManager() {

}

/*
 * Load resources for Ogre3d
 * Need to be in try catch statement
 * If ogre failed to load, it can throw a exception
 * If ogre failed and didn't throw a exception, this function return false
 */
bool IndieStudio::AppManager::loadApp() {
    mRoot = std::unique_ptr<Ogre::Root>(new Ogre::Root("resources/plugins.cfg", "resources/ogre.cfg"));
    initResources();
    if (mRoot->restoreConfig() == false && mRoot->showConfigDialog() == false)
        return false;
    mWindow = mRoot->initialise(true, "Starfelleh");
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    mSceneMgr = mRoot->createSceneManager("DefaultSceneManager", "Game Scene Manager");
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
    createCamera();
    createViewPort();
    Ogre::Entity *ent = mSceneMgr->createEntity("ninja", "ninja.mesh");
    ent->setCastShadows(true);
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);
    Ogre::Plane	plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane("ground",
						  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
						  plane,
						  1500, 1500, 20, 20,
						  true,
						  1, 5, 5,
						  Ogre::Vector3::UNIT_Z);
    Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("Examples/Rockwall");
    return true;
}

void IndieStudio::AppManager::createViewPort() {
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void IndieStudio::AppManager::createCamera() {
    mCamera = mSceneMgr->createCamera("PlayerCam");
    mCamera->setPosition(Ogre::Vector3(0,300,500));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);
}

/*
 * Render Loop of the application
 */
void IndieStudio::AppManager::execApp() {
    mRoot->startRendering();
    while (true)
    {
        Ogre::WindowEventUtilities::messagePump();
        if (mWindow->isClosed() || mRoot->renderOneFrame() == false)
            return ;
    }
}

/*
 * Load resources.cfg
 * If no resources.cfg will generate by default because config isn't set yet.
 * Can throw if resources.cfg not found
 */
void IndieStudio::AppManager::initResources() {
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
 * Destructor, delete mRoot thank to std::unique_ptr
 */
IndieStudio::AppManager::~AppManager() {}
