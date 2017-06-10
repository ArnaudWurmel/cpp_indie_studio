//
// Created by wurmel on 13/05/17.
//

#include <iostream>
#include <chrono>
#include "Bomberman.hh"

Indie::Bomberman::Bomberman(RootViewController& delegate) : AViewController(delegate) {
    mToggleMenu = false;
}

/*
 *  Load the engine
 */
void Indie::Bomberman::initView() {
    _delegate.getGUI()->hidePointer();
    mSceneDisplayer = std::unique_ptr<Indie::SceneDisplayer>(new Indie::SceneDisplayer(_delegate.getSceneManager()));
    mSceneDisplayer->initScene(_delegate);
    createMenu();
}

Indie::AViewController::ExitStatus   Indie::Bomberman::updateView() {
    if (!mSceneDisplayer->updateScene())
        return Indie::AViewController::ExitStatus::GO_BACK;
    mSceneDisplayer->registerKeyboardEvent(_delegate.getEventListener()->getKeyboard());
    return _state;
}

void    Indie::Bomberman::createMenu() {
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    int          left;
    int          top;

    _delegate.getRenderWindow()->getMetrics(width, height, depth, left, top);
    _menuControl = _delegate.getGUI()->createWidget<MyGUI::Window>("Window", (width - (width / 3)) / 2, (height - (height / 3)) / 2, width / 3, height / 3, MyGUI::Align::Center, "Main");
    _listBox = _menuControl->createWidget<MyGUI::ListBox>("ListBox", 0, 0, width / 3, height / 3, MyGUI::Align::Center, "Main");
    _listBox->eventListSelectAccept += MyGUI::newDelegate(this, &Indie::Bomberman::selectedAction);

    _functionPtr.push_back(std::make_pair(std::string("Return to game"), &Indie::Bomberman::toggleMenu));
    _functionPtr.push_back(std::make_pair(std::string("Return to menu"), &Indie::Bomberman::returnToMenu));
    _functionPtr.push_back(std::make_pair(std::string("Return to desktop"), &Indie::Bomberman::exitGame));

    std::vector<std::pair<std::string, void (Indie::Bomberman::*)()> >::const_iterator    it = _functionPtr.begin();

    while (it != _functionPtr.end()) {
        _listBox->addItem((*it).first);
        ++it;
    }
    _menuControl->setVisible(false);
}

void    Indie::Bomberman::selectedAction(MyGUI::ListBox *_sender, size_t idx) {
    static_cast<void>(_sender);
    _listBox->clearIndexSelected();
    if (idx < _functionPtr.size()) {
        (this->*(this->_functionPtr[idx].second))();
    }
}

void    Indie::Bomberman::returnToMenu() {
    _state = Indie::AViewController::ExitStatus::GO_BACK;
}

void    Indie::Bomberman::exitGame() {
    _state = Indie::AViewController::ExitStatus::EXIT;
}

void    Indie::Bomberman::toggleMenu() {
    mToggleMenu = !mToggleMenu;
    _menuControl->setVisible(mToggleMenu);
    if (mToggleMenu)
        _delegate.getGUI()->showPointer();
    else
        _delegate.getGUI()->hidePointer();
}

void    Indie::Bomberman::viewShouldDisapear() {
    if (mToggleMenu)
        toggleMenu();
}

/*
 * Dtor
 */
Indie::Bomberman::~Bomberman() {
    mSceneDisplayer.reset();
}

/**
 * Callback's functions
 */
bool    Indie::Bomberman::keyPressed(const OIS::KeyEvent& arg) {
    if (arg.key == OIS::KeyCode::KC_ESCAPE) {
        toggleMenu();
    }
    else if (!mToggleMenu){
        mSceneDisplayer->keyPressed(arg);
    }
    return true;
}

bool    Indie::Bomberman::keyReleased(const OIS::KeyEvent& arg) {
    if (!mToggleMenu)
        return mSceneDisplayer->keyReleased(arg);
}

bool Indie::Bomberman::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (mToggleMenu)
        MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
    return true;
}