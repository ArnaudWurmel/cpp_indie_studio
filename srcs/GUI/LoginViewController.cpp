//
// Created by wurmel_a on 06/06/17.
//

#include <Ogre.h>
#include <OgreRectangle2D.h>
#include "LoginViewController.hh"
#include "../DataManager/DataManager.h"
#include "RoomListViewController.hh"
#include "../Config/Config.hh"

Indie::LoginViewController::LoginViewController(Indie::RootViewController& delegate) : AViewController(delegate) {
    mSplashscreenTime = 0;
}

void    Indie::LoginViewController::initView() {
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    int          left;
    int          top;

    _delegate.getGUI()->showPointer();
    _delegate.getRenderWindow()->getMetrics(width, height, depth, left, top);
    mQuitButton = _delegate.getGUI()->createWidget<MyGUI::Button>("Button", (width - 200) / 2, height - 100, 200, 26, MyGUI::Align::Default, "Main");
    mQuitButton->setCaption("Quit");
    mQuitButton->eventMouseButtonClick += MyGUI::newDelegate(this, &Indie::LoginViewController::exitAsked);
    mTextBox = _delegate.getGUI()->createWidget<MyGUI::TextBox>("TextBox", 0, 50, width, 50, MyGUI::Align::Default, "Main");
    mTextBox->setFontName("TitleFont");
    mTextBox->setCaption(Config::getGameName());
    mTextBox->setTextAlign(MyGUI::Align::Center);
    mTextBox->setTextColour(MyGUI::Colour(1.0, 1.0, 1.0));
    mTextBox->setFontHeight(30);
    mLoginEditBox = _delegate.getGUI()->createWidget<MyGUI::EditBox>("EditBox", (width - 200) / 2, (height - 26) / 2 - 20, 200, 26, MyGUI::Align::Default, "Main");
    mPasswdEditBox = _delegate.getGUI()->createWidget<MyGUI::EditBox>("EditBox", (width - 200) / 2, (height - 26) / 2 + 20, 200, 26, MyGUI::Align::Default, "Main");
    mPasswdEditBox->setEditPassword(true);
    mConnectButton = _delegate.getGUI()->createWidget<MyGUI::Button>("Button", (width  - 200) / 2, (height - 26) / 2 + 70, 200, 26, MyGUI::Align::Default, "Main");
    mConnectButton->setCaption("Sign in");
    mConnectButton->eventMouseButtonClick += MyGUI::newDelegate(this, &Indie::LoginViewController::logMyUser);
    mMaterial = Ogre::MaterialManager::getSingleton().create("Background", "General");
    mMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("splashscreen.png");
    Ogre::TextureUnitState *FadeTextureLayer = mMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);
    mMaterial->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    FadeTextureLayer->setAlphaOperation(Ogre::LBX_SOURCE1, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, 0);
    mBackgroundRect = std::unique_ptr<Ogre::Rectangle2D>(new Ogre::Rectangle2D(true));
    mBackgroundRect->setCorners(-1.0, 1.0, 1.0, -1.0);
    mBackgroundRect->setMaterial("Background");
    mBackgroundRect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);
    Ogre::AxisAlignedBox aabInf;
    aabInf.setInfinite();
    mBackgroundRect->setBoundingBox(aabInf);
    Ogre::SceneNode* node = _delegate.getSceneManager()->getRootSceneNode()->createChildSceneNode("Background");
    node->attachObject(mBackgroundRect.get());
    viewShouldDisapear();
}

void    Indie::LoginViewController::viewShouldDisapear() {
    mQuitButton->setVisible(false);
    mTextBox->setVisible(false);
    mLoginEditBox->setVisible(false);
    mPasswdEditBox->setVisible(false);
    mConnectButton->setVisible(false);
}

void    Indie::LoginViewController::viewShouldReapear() {
    mQuitButton->setVisible(true);
    mTextBox->setVisible(true);
    mLoginEditBox->setVisible(true);
    mPasswdEditBox->setVisible(true);
    mConnectButton->setVisible(true);
    _delegate.getGUI()->showPointer();
}

Indie::LoginViewController::ExitStatus    Indie::LoginViewController::updateView() {
    if (mSplashscreenTime < 240) {
        if (mSplashscreenTime <= 90) {
            Ogre::TextureUnitState *FadeTextureLayer = mMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);
            mMaterial->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
            FadeTextureLayer->setAlphaOperation(Ogre::LBX_SOURCE1, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, (mSplashscreenTime / 90.0));
        }
        else if (mSplashscreenTime >= 150) {
            Ogre::TextureUnitState *FadeTextureLayer = mMaterial->getTechnique(0)->getPass(0)->getTextureUnitState(0);
            mMaterial->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
            FadeTextureLayer->setAlphaOperation(Ogre::LBX_SOURCE1, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, 1.0 - ((mSplashscreenTime - 150) / 90.0));
        }
        mSplashscreenTime += 1;
    }
    else if (mSplashscreenTime == 240) {
        Ogre::MaterialManager::getSingleton().remove("Background", "General");
        mMaterial = Ogre::MaterialManager::getSingleton().create("Background", "General");
        mMaterial->getTechnique(0)->getPass(0)->createTextureUnitState("background.jpeg");
        mMaterial->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
        mMaterial->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
        mMaterial->getTechnique(0)->getPass(0)->setLightingEnabled(false);
        mBackgroundRect->setMaterial("Background");
        ++mSplashscreenTime;
        viewShouldReapear();
    }
    return _state;
}

void    Indie::LoginViewController::exitAsked(MyGUI::WidgetPtr _sender) {
    static_cast<void>(_sender);
    _state = EXIT;
}

void    Indie::LoginViewController::logMyUser(MyGUI::WidgetPtr _sender) {
    static_cast<void>(_sender);
    DataManager *dataManager = DataManager::getSingloton();

    if (dataManager->connect(mLoginEditBox->getOnlyText(), mPasswdEditBox->getOnlyText())) {
        _delegate.addViewController(new Indie::RoomListViewController(_delegate));
    }
}

Indie::LoginViewController::~LoginViewController() {}