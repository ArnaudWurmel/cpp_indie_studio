//
// Created by wurmel_a on 06/06/17.
//

#include <iostream>
#include "RootViewController.hh"
#include "../Bomberman/Bomberman.hh"
#include "LoginViewController.hh"

Indie::RootViewController::RootViewController() {

}

bool    Indie::RootViewController::loadApp() {
    mRoot = std::unique_ptr<Ogre::Root>(new Ogre::Root("resources/plugins.cfg", "resources/ogre.cfg", "resources/ogre.log"));
    this->loadResources();
    std::cout << "Done" << std::endl;
    if (!(mRoot->restoreConfig() || mRoot->showConfigDialog())) {
        return false;
    }
    mRenderWindow = mRoot->initialise(true, "Bomberman");
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    mSceneManager = mRoot->createSceneManager("DefaultSceneManager", "Game Scene Manager");
    mSceneManager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
    this->createCamera();
    mPlatform = new MyGUI::OgrePlatform();
    mPlatform->initialise(mRenderWindow, mSceneManager);
    mGUI = new MyGUI::Gui();
    mGUI->initialise();
    mEventListener = std::unique_ptr<Indie::EventListener>(new Indie::EventListener(mSceneManager, mRenderWindow, mGUI));
    Ogre::WindowEventUtilities::addWindowEventListener(mRenderWindow, mEventListener.get());
    mRoot->addFrameListener(mEventListener.get());
    addViewController(new Indie::LoginViewController(*this));
    return true;
}

void Indie::RootViewController::runApp() {
    Ogre::Real  timeSinceLastFrame = 0.0;
    float   timeStep = 1 / 60.0f;
    float   timeStepAccumulator = 0.0f;
    AViewController::ExitStatus status;

    while (true) {
        Ogre::WindowEventUtilities::messagePump();
        timeStepAccumulator += timeSinceLastFrame;
        while (!mRenderWindow->isClosed() && timeStepAccumulator >= timeStep) {
            if ((status = mControllerList.back()->updateView()) != AViewController::ExitStatus::GO_ON) {
                if (status == AViewController::ExitStatus::GO_BACK) {
                    mControllerList.back()->viewShouldDisapear();
                    mControllerList.pop_back();
                    mEventListener->setUpEventRegister(mControllerList.back().get());
                    mControllerList.back()->viewShouldReapear();
                }
                else {
                    return ;
                }
            }
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


void    Indie::RootViewController::createCamera() {
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
 * Load the necessary resources.
 */
void    Indie::RootViewController::loadResources() {
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

Indie::RootViewController::~RootViewController() {
    mEventListener->setUpEventRegister(NULL);
    while (mControllerList.size() > 0) {
        mControllerList.back()->viewShouldDisapear();
        mControllerList.pop_back();
        if (mControllerList.size() > 0) {
            mControllerList.back()->viewShouldReapear();
        }
    }
    mControllerList.clear();
    mGUI->shutdown();
    delete mGUI;
    mGUI = 0;
    mPlatform->shutdown();
    delete mPlatform;
    mPlatform = 0;
    Ogre::WindowEventUtilities::removeWindowEventListener(mRenderWindow, mEventListener.get());
    mEventListener->windowClosed(mRenderWindow);
    mRoot.reset();
    mEventListener.reset();
}

/**
 * Push new ViewController in tab and set eventListener
 */
void    Indie::RootViewController::addViewController(AViewController *viewController) {
    if (mControllerList.size() > 0) {
        mControllerList.back()->viewShouldDisapear();
    }
    mControllerList.push_back(std::unique_ptr<AViewController>(viewController));
    std::cout << "View Controller setted" << std::endl;
    mControllerList.back()->initView();
    mEventListener->setUpEventRegister(mControllerList.back().get());
}

/**
 * Getter for Ogre instance
 * @return
 */
std::unique_ptr<Ogre::Root>&    Indie::RootViewController::getOgreRoot() {
    return mRoot;
}

std::unique_ptr<Indie::EventListener>&  Indie::RootViewController::getEventListener() {
    return mEventListener;
}

Ogre::RenderWindow  *Indie::RootViewController::getRenderWindow() {
    return mRenderWindow;
}

Ogre::SceneManager  *Indie::RootViewController::getSceneManager() {
    return mSceneManager;
}

MyGUI::Gui  *Indie::RootViewController::getGUI() {
    return mGUI;
}

MyGUI::OgrePlatform  *Indie::RootViewController::getOgrePlatform() {
    return mPlatform;
}

/**
 * Callbacks for event
 *
 */
bool Indie::RootViewController::mouseMoved( const OIS::MouseEvent &arg )
{
    MyGUI::InputManager::getInstance().injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);
    return true;
}

bool Indie::RootViewController::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
    return true;
}

bool Indie::RootViewController::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    MyGUI::InputManager::getInstance().injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
    return true;
}

bool Indie::RootViewController::keyPressed( const OIS::KeyEvent &arg )
{
    MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
    return true;
}

bool Indie::RootViewController::keyReleased( const OIS::KeyEvent &arg )
{
    MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));
    return true;
}

void    Indie::RootViewController::registerKeyboardEvent(OIS::Keyboard* keyboard) {
    static_cast<void>(keyboard);
}

void    Indie::RootViewController::registerMouseEvent(OIS::Mouse *mouse) {
    static_cast<void>(mouse);
}