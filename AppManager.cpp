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
    mRoot = std::unique_ptr<Ogre::Root>(new Ogre::Root());
    return false;
}

/*
 * Render Loop of the application
 */
void IndieStudio::AppManager::execApp() {
}

/*
 * Destructor, delete mRoot thank to std::unique_ptr
 */
IndieStudio::AppManager::~AppManager() {

}
