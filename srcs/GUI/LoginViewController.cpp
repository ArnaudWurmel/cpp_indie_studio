//
// Created by wurmel_a on 06/06/17.
//

#include "LoginViewController.hh"
#include "../DataManager/DataManager.h"
#include "../Bomberman/Bomberman.hh"

Indie::LoginViewController::LoginViewController(Indie::RootViewController& delegate) : AViewController(delegate) {}

void    Indie::LoginViewController::initView() {
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    int          left;
    int          top;

    _delegate.getRenderWindow()->getMetrics(width, height, depth, left, top);
    mQuitButton = _delegate.getGUI()->createWidget<MyGUI::Button>("Button", (width - 200) / 2, height - 100, 200, 26, MyGUI::Align::Default, "Main");
    mQuitButton->setCaption("Quit");
    mQuitButton->eventMouseButtonClick += MyGUI::newDelegate(this, &Indie::LoginViewController::exitAsked);
    mTextBox = _delegate.getGUI()->createWidget<MyGUI::TextBox>("TextBox", (width - 200) / 2, (height - 20) / 2 - 70, 200, 20, MyGUI::Align::Default, "Main");
    mTextBox->setCaption("Coucou les amis");
    mLoginEditBox = _delegate.getGUI()->createWidget<MyGUI::EditBox>("EditBox", (width - 200) / 2, (height - 26) / 2 - 20, 200, 26, MyGUI::Align::Default, "Main");
    mPasswdEditBox = _delegate.getGUI()->createWidget<MyGUI::EditBox>("EditBox", (width - 200) / 2, (height - 26) / 2 + 20, 200, 26, MyGUI::Align::Default, "Main");
    mPasswdEditBox->setEditPassword(true);
    mConnectButton = _delegate.getGUI()->createWidget<MyGUI::Button>("Button", (width  - 200) / 2, (height - 26) / 2 + 70, 200, 26, MyGUI::Align::Default, "Main");
    mConnectButton->setCaption("Sign in");
    mConnectButton->eventMouseButtonClick += MyGUI::newDelegate(this, &Indie::LoginViewController::logMyUser);
}

void    Indie::LoginViewController::viewShouldDisapear() {
    mQuitButton->setVisible(false);
    mTextBox->setVisible(false);
    mLoginEditBox->setVisible(false);
    mPasswdEditBox->setVisible(false);
    mConnectButton->setVisible(false);
    _delegate.getGUI()->hidePointer();
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
        _delegate.addViewController(new Indie::Bomberman(_delegate));
    }
}

Indie::LoginViewController::~LoginViewController() {}