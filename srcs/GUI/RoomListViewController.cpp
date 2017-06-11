//
// Created by wurmel_a on 08/06/17.
//

#include "RoomListViewController.hh"
#include "../DataManager/DataManager.h"
#include "../Config/Config.hh"
#include "WaitingRoomViewController.hh"
#include "../UserManager/User.hh"
#include "GlobalRankingViewController.hh"

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
    mRoomList = _delegate.getGUI()->createWidget<MyGUI::ListBox>("ListBox", width - ((width / 3) + 10), 150, width / 3, height - 350, MyGUI::Align::Default, "Main");
    mRoomList->eventListSelectAccept += MyGUI::newDelegate(this, &Indie::RoomListViewController::selectedRoom);
    setUpMenu(width, height);
    mTextBox = _delegate.getGUI()->createWidget<MyGUI::TextBox>("TextBox", 0, 50, width, 50, MyGUI::Align::Default, "Main");
    mTextBox->setFontName("TitleFont");
    mTextBox->setCaption(Indie::Config::getGameName());
    mTextBox->setTextAlign(MyGUI::Align::Center);
    mTextBox->setTextColour(MyGUI::Colour(1.0, 1.0, 1.0));
    mTextBox->setFontHeight(30);
    refreshButton();
}

void    Indie::RoomListViewController::setUpMenu(unsigned int width, unsigned int height) {
    mMenuList = _delegate.getGUI()->createWidget<MyGUI::ListBox>("ListBoxMenu", 10, 150, width / 3, height - 350, MyGUI::Align::Default, "Main");
    mMenuList->eventListSelectAccept += MyGUI::newDelegate(this, &Indie::RoomListViewController::selectedAction);
    _functionPtr.push_back(std::make_pair(std::string("#FFFFFFCreate Room"), &Indie::RoomListViewController::createNewRoom));
    _functionPtr.push_back(std::make_pair(std::string("#FFFFFFRefresh List"), &Indie::RoomListViewController::refreshButton));
    _functionPtr.push_back(std::make_pair(std::string("#FFFFFFGlobal Ranking"), &Indie::RoomListViewController::showGlobalRanking));
    _functionPtr.push_back(std::make_pair(std::string("#E74C3CLog out"), &Indie::RoomListViewController::disconnectUser));

    std::vector<std::pair<std::string, void (Indie::RoomListViewController::*)()> >::iterator it = _functionPtr.begin();

    while (it != _functionPtr.end()) {
        mMenuList->addItem((*it).first, *it);
        ++it;
    }
}

void    Indie::RoomListViewController::createNewRoom() {
    DataManager *dataManager = DataManager::getSingloton();

    if (dataManager->createRoom()) {
        _delegate.addViewController(new Indie::WaitingRoomViewController(_delegate, true));
        return ;
    }
}

void    Indie::RoomListViewController::selectedAction(MyGUI::ListBox *_sender, size_t index) {
    static_cast<void>(_sender);
    mMenuList->clearIndexSelected();
    if (index < _functionPtr.size()) {
        (this->*(this->_functionPtr[index].second))();
    }
}

void    Indie::RoomListViewController::disconnectUser() {
    _state = Indie::AViewController::ExitStatus::GO_BACK;
}

void    Indie::RoomListViewController::selectedRoom(MyGUI::ListBox *_sender, size_t index) {
    static_cast<void>(_sender);
    mRoomList->clearIndexSelected();
    if (index < _roomList.size()) {
        DataManager *dataManager = DataManager::getSingloton();
        if (dataManager->joinRoom(User::getUser()->getLogName(), _roomList[index].getRoomID()))
            _delegate.addViewController(new Indie::WaitingRoomViewController(_delegate));
    }
}

void    Indie::RoomListViewController::refreshButton() {
    mRoomList->removeAllItems();
    _roomList = Indie::DataManager::getSingloton()->listRoom();
    std::vector<Room>::iterator it = _roomList.begin();
    while (it != _roomList.end()) {
        std::string displayInfo = "Room ##" + std::to_string((*it).getRoomID());
        if ((*it).getNbPlayers() <= 2)
            displayInfo += "#27AE60";
        else if ((*it).getNbPlayers() == 3)
            displayInfo += "#E67E22";
        else
            displayInfo += "#E74C3C";
        displayInfo += " (" + std::to_string((*it).getNbPlayers()) + "/4)";
        mRoomList->addItem(displayInfo, *it);
        ++it;
    }
}

void    Indie::RoomListViewController::showGlobalRanking() {
    _delegate.addViewController(new Indie::GlobalRankingViewController(_delegate));
}

void    Indie::RoomListViewController::viewShouldReapear() {
    mRoomList->setVisible(true);
    mMenuList->setVisible(true);
    mTextBox->setVisible(true);
    _delegate.getGUI()->showPointer();
}

void    Indie::RoomListViewController::viewShouldDisapear() {
    mRoomList->setVisible(false);
    mTextBox->setVisible(false);
    mMenuList->setVisible(false);
}

Indie::AViewController::ExitStatus   Indie::RoomListViewController::updateView() {
    return _state;
}

Indie::RoomListViewController::~RoomListViewController() {}