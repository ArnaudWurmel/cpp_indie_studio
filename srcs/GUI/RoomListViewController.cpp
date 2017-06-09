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

    mRefreshButton = _delegate.getGUI()->createWidget<MyGUI::Button>("Button", width - ((width / 3) + 10), 100, width / 3, 26, MyGUI::Align::Default, "Main");
    mRefreshButton->setCaption("Refresh");
    mRefreshButton->eventMouseButtonClick += MyGUI::newDelegate(this, &Indie::RoomListViewController::refreshButton);

    mListBox = _delegate.getGUI()->createWidget<MyGUI::ListBox>("ListBox", width - ((width / 3) + 10), 150, width / 3, height - 350, MyGUI::Align::Default, "Main");
    mListBox->eventListSelectAccept += MyGUI::newDelegate(this, &Indie::RoomListViewController::selectedRoom);

    mTextBox = _delegate.getGUI()->createWidget<MyGUI::TextBox>("TextBox", 0, 50, width, 50, MyGUI::Align::Default, "Main");
    mTextBox->setFontName("TitleFont");
    mTextBox->setCaption("Bombertron");
    mTextBox->setTextAlign(MyGUI::Align::Center);
    mTextBox->setTextColour(MyGUI::Colour(1.0, 1.0, 1.0));
    mTextBox->setFontHeight(30);
}

void    Indie::RoomListViewController::disconnectUser(MyGUI::WidgetPtr _sender) {
    static_cast<void>(_sender);
    _state = Indie::AViewController::ExitStatus::GO_BACK;
}

void    Indie::RoomListViewController::selectedRoom(MyGUI::ListBox *_sender, size_t index) {
    static_cast<void>(_sender);
    std::cout << index << std::endl;
    if (index < _roomList.size()) {
        std::cout << _roomList[index].getRoomID() << std::endl;
    }
}

void    Indie::RoomListViewController::refreshButton(MyGUI::WidgetPtr _sender) {
    static_cast<void>(_sender);
    mListBox->removeAllItems();
    _roomList = Indie::DataManager::getSingloton()->listRoom();
    std::vector<Room>::iterator it = _roomList.begin();
    while (it != _roomList.end()) {
        std::string displayInfo = "Room ##" + std::to_string((*it).getRoomID()) + " (" + std::to_string((*it).getNbPlayers()) + "/4)";
        mListBox->addItem(displayInfo, *it);
        ++it;
    }
}

void    Indie::RoomListViewController::viewShouldReapear() {
    mDisconnectButton->setVisible(true);
    mRefreshButton->setVisible(true);
    mListBox->setVisible(true);
    mTextBox->setVisible(true);
    _delegate.getGUI()->showPointer();
}

void    Indie::RoomListViewController::viewShouldDisapear() {
    mDisconnectButton->setVisible(false);
    mRefreshButton->setVisible(false);
    mListBox->setVisible(false);
    mTextBox->setVisible(false);
}

Indie::AViewController::ExitStatus   Indie::RoomListViewController::updateView() {
    return _state;
}

Indie::RoomListViewController::~RoomListViewController() {}