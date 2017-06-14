//
// Created by wurmel_a on 08/06/17.
//

#include "RoomListViewController.hh"
#include "../DataManager/DataManager.h"
#include "../Config/Config.hh"
#include "WaitingRoomViewController.hh"
#include "../UserManager/User.hh"
#include "GlobalRankingViewController.hh"

Indie::RoomListViewController::RoomListViewController(RootViewController& delegate) : AViewController(delegate), BackgroundMapController(delegate) {
    _indexSelected = -1;
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
	Indie::RoomListViewController::ActionDelegate createroom = {std::string("#FFFFFFCreate Room"), &Indie::RoomListViewController::createNewRoom, 1, BackgroundMapController::GO_THROUGHT};
	Indie::RoomListViewController::ActionDelegate refreshlist = {std::string("#FFFFFFRefresh List"), &Indie::RoomListViewController::refreshButton, 0, BackgroundMapController::NONE};
	Indie::RoomListViewController::ActionDelegate globalranking = {std::string("#FFFFFFGlobal Ranking"), &Indie::RoomListViewController::showGlobalRanking, 1, BackgroundMapController::GO_THROUGHT};
	Indie::RoomListViewController::ActionDelegate logout = {std::string("#E74C3CLog out"), &Indie::RoomListViewController::disconnectUser, 1, BackgroundMapController::BREAK};
	Indie::RoomListViewController::ActionDelegate joinroom = {std::string("JOINROOM"), &Indie::RoomListViewController::joinRoom, 1, BackgroundMapController::GO_THROUGHT};

    mMenuList = _delegate.getGUI()->createWidget<MyGUI::ListBox>("ListBoxMenu", 10, 150, width / 3, height - 350, MyGUI::Align::Default, "Main");
    mMenuList->eventListSelectAccept += MyGUI::newDelegate(this, &Indie::RoomListViewController::selectedAction);
    _functionPtr.push_back(createroom);
    _functionPtr.push_back(refreshlist);
    _functionPtr.push_back(globalranking);
    _functionPtr.push_back(logout);

    std::vector<ActionDelegate>::iterator it = _functionPtr.begin();

    while (it != _functionPtr.end()) {
        mMenuList->addItem((*it).menuName, *it);
        ++it;
    }
    _functionPtr.push_back(joinroom);
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
        if (_functionPtr[index].changeScreen) {
            _indexSelected = index;
            menuSelected(_delegate, _functionPtr[index].type);
        }
        else {
            if (index < _functionPtr.size())
                (this->*(this->_functionPtr[index].fctPtr))();
        }
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
        if (dataManager->joinRoom(User::getUser()->getLogName(), _roomList[index].getRoomID())) {
            menuSelected(_delegate, _functionPtr[_functionPtr.size() - 1].type);
            _indexSelected = _functionPtr.size() - 1;
        }
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
    _indexSelected = -1;
    generateBackground(_delegate);
    mRoomList->setVisible(true);
    mMenuList->setVisible(true);
    mTextBox->setVisible(true);
    setHidden(false);
    _delegate.getGUI()->showPointer();
}

void    Indie::RoomListViewController::viewShouldDisapear() {
    _indexSelected = -1;
    mRoomList->setVisible(false);
    mTextBox->setVisible(false);
    mMenuList->setVisible(false);
    setHidden(true);
}

void    Indie::RoomListViewController::joinRoom() {
    _delegate.addViewController(new Indie::WaitingRoomViewController(_delegate));
}

Indie::AViewController::ExitStatus   Indie::RoomListViewController::updateView() {
    if (!updateBackground(_delegate) && _indexSelected >= 0 && _indexSelected < _functionPtr.size()) {
        (this->*(this->_functionPtr[_indexSelected].fctPtr))();
        _indexSelected = -1;
    }
    return _state;
}

Indie::RoomListViewController::~RoomListViewController() {}