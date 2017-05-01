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
    return true;
}

/*
 * Render Loop of the application
 */
void IndieStudio::AppManager::execApp() {
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