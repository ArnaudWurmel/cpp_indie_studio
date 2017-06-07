//
// Created by wurmel_a on 07/06/17.
//

#include <MYGUI/MyGUI.h>
#include "AViewController.hh"
#include "RootViewController.hh"

Indie::AViewController::AViewController(RootViewController& delegate) : _delegate(delegate) {
    _state = GO_ON;
}

/**
 * Callbacks for event
 *
 */
bool Indie::AViewController::mouseMoved( const OIS::MouseEvent &arg )
{
    MyGUI::InputManager::getInstance().injectMouseMove(arg.state.X.abs, arg.state.Y.abs, arg.state.Z.abs);
    return true;
}

bool Indie::AViewController::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    MyGUI::InputManager::getInstance().injectMousePress(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
    return true;
}

bool Indie::AViewController::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    MyGUI::InputManager::getInstance().injectMouseRelease(arg.state.X.abs, arg.state.Y.abs, MyGUI::MouseButton::Enum(id));
    return true;
}

bool Indie::AViewController::keyPressed( const OIS::KeyEvent &arg )
{
    if (arg.key == OIS::KeyCode::KC_ESCAPE) {
        _delegate.getRenderWindow()->destroy();
        return false;
    }
    MyGUI::InputManager::getInstance().injectKeyPress(MyGUI::KeyCode::Enum(arg.key), arg.text);
    return true;
}

bool Indie::AViewController::keyReleased( const OIS::KeyEvent &arg )
{
    MyGUI::InputManager::getInstance().injectKeyRelease(MyGUI::KeyCode::Enum(arg.key));
    return true;
}

void    Indie::AViewController::registerKeyboardEvent(OIS::Keyboard* keyboard) {
    static_cast<void>(keyboard);
}

void    Indie::AViewController::registerMouseEvent(OIS::Mouse *mouse) {
    static_cast<void>(mouse);
}

void    Indie::AViewController::viewShouldDisapear() {}

void    Indie::AViewController::viewShouldReapear() {}

Indie::AViewController::~AViewController() {}