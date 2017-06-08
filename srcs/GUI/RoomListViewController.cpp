//
// Created by wurmel_a on 08/06/17.
//

#include "RoomListViewController.hh"
#include "../DataManager/DataManager.h"

Indie::RoomListViewController::RoomListViewController(RootViewController& delegate) : AViewController(delegate) {

}

void    Indie::RoomListViewController::initView() {
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    int          left;
    int          top;

    _delegate.getGUI()->showPointer();
    _delegate.getRenderWindow()->getMetrics(width, height, depth, left, top);
    mDisconnectButton = _delegate.getGUI()->createWidget<MyGUI::Button>("Button", (width - 200) / 2, height - 100, 200, 26, MyGUI::Align::Default, "Main");
    mDisconnectButton->setCaption("Log out");
    mDisconnectButton->eventMouseButtonClick += MyGUI::newDelegate(this, &Indie::RoomListViewController::disconnectUser);

    mRefreshButton = _delegate.getGUI()->createWidget<MyGUI::Button>("Button", (width - 200) / 2, height - 150, 200, 26, MyGUI::Align::Default, "Main");
    mRefreshButton->setCaption("Refresh");
    mRefreshButton->eventMouseButtonClick += MyGUI::newDelegate(this, &Indie::RoomListViewController::refreshButton);

    mListBox = _delegate.getGUI()->createWidget<MyGUI::ListBox>("ListBox", 0, 30, width, height - 200, MyGUI::Align::Default, "Main");
}

void    Indie::RoomListViewController::disconnectUser(MyGUI::WidgetPtr _sender) {
    static_cast<void>(_sender);
    _state = Indie::AViewController::ExitStatus::GO_BACK;
}

void    Indie::RoomListViewController::selectedRoom(MyGUI::ListBox *_sender, size_t index) {
    static_cast<void>(_sender);
    std::cout << index << std::endl;
}

void    Indie::RoomListViewController::refreshButton(MyGUI::WidgetPtr _sender) {
    static_cast<void>(_sender);
    mListBox->removeAllItems();
    mListBox->eventMouseButtonClick += MyGUI::newDelegate(this, &Indie::RoomListViewController::selectedRoom);
    std::vector<Room>   roomVector = Indie::DataManager::getSingloton()->listRoom();
    std::vector<Room>::iterator it = roomVector.begin();
    while (it != roomVector.end()) {
        mListBox->addItem("Bonjour les amis", *it);
        std::cout << (*it).getRoomID() << " " << (*it).getNbPlayers() << std::endl;
        ++it;
    }
}

void    Indie::RoomListViewController::viewShouldReapear() {
    mDisconnectButton->setVisible(true);
    mRefreshButton->setVisible(true);
    mListBox->setVisible(true);
    _delegate.getGUI()->showPointer();
}

void    Indie::RoomListViewController::viewShouldDisapear() {
    mDisconnectButton->setVisible(false);
    mRefreshButton->setVisible(false);
    mListBox->setVisible(false);
}

Indie::AViewController::ExitStatus   Indie::RoomListViewController::updateView() {
    return _state;
}

Indie::RoomListViewController::~RoomListViewController() {}