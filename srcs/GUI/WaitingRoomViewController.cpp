//
// Created by wurmel_a on 09/06/17.
//

#include <OgreRectangle2D.h>
#include "../Config/Config.hh"
#include "RoomListViewController.hh"
#include "WaitingRoomViewController.hh"
#include "../DataManager/DataManager.h"
#include "../UserManager/User.hh"
#include "../Bomberman/Bomberman.hh"

Indie::WaitingRoomViewController::WaitingRoomViewController(Indie::RootViewController& delegate, bool isCreator) : AViewController(delegate) {
    _continue = true;
    _gameRunning = false;
    _isCreator = isCreator;
    _lock = std::unique_ptr<std::mutex>(new std::mutex());
    _mapName = "N/A";
    _threadUpdate = std::unique_ptr<std::thread>(new std::thread(&Indie::WaitingRoomViewController::threadUpdate, this));
}

void    Indie::WaitingRoomViewController::initView() {
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    int          left;
    int          top;

    _delegate.getGUI()->showPointer();
    _delegate.getRenderWindow()->getMetrics(width, height, depth, left, top);
    mPlayerList = _delegate.getGUI()->createWidget<MyGUI::ListBox>("ListBoxPlayerList", width - ((width / 3) + 10), 150, width / 3, height - 350, MyGUI::Align::Default, "Main");
    mMenuList = _delegate.getGUI()->createWidget<MyGUI::ListBox>("ListBoxMenu", 10, 150, width / 3, height / 3, MyGUI::Align::Default, "Main");
    mMenuList->eventListSelectAccept += MyGUI::newDelegate(this, &Indie::WaitingRoomViewController::selectedAction);
    setUpMenu();
    mTextBox = _delegate.getGUI()->createWidget<MyGUI::TextBox>("TextBox", 0, 50, width, 50, MyGUI::Align::Default, "Main");
    mTextBox->setFontName("TitleFont");
    mTextBox->setCaption(Indie::Config::getGameName());
    mTextBox->setTextAlign(MyGUI::Align::Center);
    mTextBox->setTextColour(MyGUI::Colour(1.0, 1.0, 1.0));
    mTextBox->setFontHeight(30);
    mMapBox = _delegate.getGUI()->createWidget<MyGUI::ImageBox>("ImageBox", 10, 150 + height / 3 + 10, height - (150 + height / 3 + 10), height - (150 + height / 3 + 10), MyGUI::Align::Default, "Main");
    setImageForMap();
}

void    Indie::WaitingRoomViewController::setImageForMap() {
   Ogre::MaterialPtr ptr = Ogre::MaterialManager::getSingleton().getByName("MapOverview/" + _mapName);

    if (ptr.isNull())
		mMapBox->setImageTexture("Unknown.png");
	else
        mMapBox->setImageTexture(_mapName + ".png");
}

Indie::AViewController::ExitStatus   Indie::WaitingRoomViewController::updateView() {
    if (_gameRunning && _state == Indie::AViewController::GO_ON) {
        _delegate.addViewController(new Indie::Bomberman(_delegate));
        return Indie::AViewController::GO_ON;
    }
    _lock->lock();
    std::vector<std::string>::iterator  it = _playerList.begin();

    mPlayerList->removeAllItems();
    mPlayerList->setEnabled(false);
    while (it != _playerList.end()) {
        std::string toDisp;
        if (!(*it).compare(User::getUser()->getLogName())) {
            toDisp = "#F1C40F";
        }
        toDisp += *it;
        mPlayerList->addItem(toDisp, NULL);
        ++it;
    }
    if (mMenuList->getItemCount() > 1) {
        mMenuList->setItemNameAt(1, "#FFFFFFMap name : #F1C40F" + _mapName);
    }
    setImageForMap();
    _lock->unlock();
    return _state;
}

void    Indie::WaitingRoomViewController::viewShouldReapear() {
    mPlayerList->setVisible(true);
    mTextBox->setVisible(true);
    mMenuList->setVisible(true);
    _lock->unlock();
    _delegate.getGUI()->showPointer();
}

void    Indie::WaitingRoomViewController::viewShouldDisapear() {
    _state = AViewController::ExitStatus::GO_BACK;
    mPlayerList->setVisible(false);
    mTextBox->setVisible(false);
    mMenuList->setVisible(false);
    _lock->lock();
}

void    Indie::WaitingRoomViewController::selectedAction(MyGUI::ListBox *_sender, size_t idx) {
    static_cast<void>(_sender);
    mMenuList->clearIndexSelected();
    if (idx < _functionPtr.size()) {
        (this->*(this->_functionPtr[idx].second))();
    }
}

void    Indie::WaitingRoomViewController::setUpMenu() {
    if (_isCreator)
        _functionPtr.push_back(std::make_pair(std::string("#FFFFFFStart Game"), &Indie::WaitingRoomViewController::runGame));
    _functionPtr.push_back(std::make_pair("#FFFFFFMap name : #F1C40F" + _mapName, &Indie::WaitingRoomViewController::changeMap));
    _functionPtr.push_back(std::make_pair(std::string("#E74C3CExit Room"), &Indie::WaitingRoomViewController::returnToMenu));
    std::vector<std::pair<std::string, void (Indie::WaitingRoomViewController::*)()> >::iterator it = _functionPtr.begin();

    while (it != _functionPtr.end()) {
        mMenuList->addItem((*it).first, *it);
        ++it;
    }
}

void    Indie::WaitingRoomViewController::returnToMenu() {
    _state = AViewController::ExitStatus::GO_BACK;
}

void    Indie::WaitingRoomViewController::runGame() {
    DataManager *dataManager = DataManager::getSingloton();

    dataManager->runGame();
}

void    Indie::WaitingRoomViewController::threadUpdate() {
    Indie::DataManager  *dataManager = DataManager::getSingloton();

    while (_continue) {
        _lock->lock();
        _playerList.clear();
        try {
            _playerList = dataManager->getPlayerList();
            _gameRunning = dataManager->gameIsRunning(_mapName);
            std::cout << _mapName << std::endl;
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
        _lock->unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    try {
        dataManager->quitRoom(User::getUser()->getLogName());
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void    Indie::WaitingRoomViewController::changeMap() {
    if (_isCreator) {
        DataManager::getSingloton()->setNextMap(User::getUser()->getRoomId());
    }
}

Indie::WaitingRoomViewController::~WaitingRoomViewController() {
    _lock->unlock();
    _continue = false;
    _threadUpdate->join();
    _threadUpdate.reset();
    _lock.reset();
}