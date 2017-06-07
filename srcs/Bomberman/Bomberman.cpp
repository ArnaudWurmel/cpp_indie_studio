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
    mSceneDisplayer = std::unique_ptr<Indie::SceneDisplayer>(new Indie::SceneDisplayer(_delegate.getSceneManager()));
    mSceneDisplayer->initScene();
    _menuControl = _delegate.getGUI()->createWidget<MyGUI::MenuControl>("MenuControl", 0, 0, 200, 200, MyGUI::Align::Center, "Main");
}

Indie::AViewController::ExitStatus   Indie::Bomberman::updateView() {
    if (!mSceneDisplayer->updateScene())
        return Indie::AViewController::ExitStatus::EXIT;
    mSceneDisplayer->registerKeyboardEvent(_delegate.getEventListener()->getKeyboard());
    return _state;
}

void    Indie::Bomberman::toggleMenu() {
    mToggleMenu = !mToggleMenu;
    if (mToggleMenu) {

    }
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

bool Indie::Bomberman::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (mToggleMenu)
        MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
    return true;
}