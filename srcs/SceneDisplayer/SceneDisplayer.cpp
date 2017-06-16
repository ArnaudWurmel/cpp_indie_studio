//
// Created by wurmel on 13/05/17.
//

#include <iostream>
#include "SceneDisplayer.hh"
#include "../Entities/EntityManager.hh"
#include "../Player/HumanPlayer.hh"
#include "../DataManager/DataManager.h"
#include "../UserManager/User.hh"
#include "../Exception/Exception.hh"

Indie::SceneDisplayer::SceneDisplayer(Ogre::SceneManager *sceneManager) {
    mSceneManager = sceneManager;
    mToggleScoreboard = false;
    mError = false;
}

void Indie::SceneDisplayer::initScene(RootViewController& delegate) {
    MapParser&  mapParser = MapParser::getMapParser("resources/maps/level0");
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    int          left;
    int          top;


    mapParser.loadMap("");
    _map = mapParser.getMap();
    if (_map.size() > 0) {
        this->createMap();
    }
    initScoreboard(delegate);
    bool    success = false;
    DataManager *dataManager = Indie::DataManager::getSingloton();
    Ogre::Vector3   posPlayer = dataManager->getPlayerStart(User::getUser()->getLogName(), success);
    if (!success)
        throw GameException();
    EntityManager::createHuman(mSceneManager, Ogre::Vector3(posPlayer.x, 32, posPlayer.z), User::getUser()->getLogName());
    initEventRegister();
    delegate.getRenderWindow()->getMetrics(width, height, depth, left, top);
    mResultHUD = delegate.getGUI()->createWidget<MyGUI::ImageBox>("ImageBox", (width - (width / 3)) / 2, (height - (height / 3)) / 2, width / 3, height / 3, MyGUI::Align::Default, "Main");
    mResultHUD->setVisible(false);
    _thread = std::unique_ptr<std::thread>(new std::thread(&Indie::SceneDisplayer::updaterThread, this));
}

void Indie::SceneDisplayer::createMap() {
    std::vector<std::vector<MapParser::TileType> >::iterator    it;
    std::map<MapParser::TileType, EntityManager::EntityType>    converter;
    int    i;
    int    j;

    converter.insert(std::make_pair(MapParser::TileType::STATIC_BLOCK, EntityManager::EntityType::BLOCK));
    converter.insert(std::make_pair(MapParser::TileType::DYNAMIC_BLOCK, EntityManager::EntityType::DYNAMIC_BLOCK));
    converter.insert(std::make_pair(MapParser::TileType::EMPTY, EntityManager::EntityType::EMPTY));
    it = _map.begin();
    i = 0;
    while (it != _map.end()) {
        std::vector<MapParser::TileType>::iterator  it_line;
        j = 0;
        it_line = (*it).begin();
        while (it_line != (*it).end()) {
            long x = _map.size() * 100 / 2 - (i * 100);
            long z = ((*it).size() * 100) / 2 - (100 * j);
            EntityManager::createEntity(converter[*it_line], mSceneManager, Ogre::Vector3(x, 50, z));
            _groundEntityList.push_back(std::unique_ptr<AEntity>(new Indie::Block(mSceneManager, Ogre::Vector3(x, -51, z))));
            _groundEntityList.back()->setMaterialName("Bomberman/BlockGround");
            ++it_line;
            ++j;
        }
        ++i;
        ++it;
    }
}

void    Indie::SceneDisplayer::initScoreboard(RootViewController& delegate) {
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    int          left;
    int          top;

    delegate.getRenderWindow()->getMetrics(width, height, depth, left, top);

    mScoreboard = delegate.getGUI()->createWidget<MyGUI::MultiListBox>("MultiListBox", (width - (width / 2)) / 2, (height - (height / 2)) / 2, width / 2, height / 2, MyGUI::Align::Default, "Main");
    mScoreboard->addColumn("Player Name", mScoreboard->getWidth() / 2);
    mScoreboard->addColumn("Score", mScoreboard->getWidth() / 2);
    mScoreboard->setVisible(false);
    mScoreboard->setEnabled(true);
}

void    Indie::SceneDisplayer::viewShouldDisapear() {
    if (mToggleScoreboard)
        toggleScoreboard();
}

void    Indie::SceneDisplayer::updaterThread() {
    Indie::DataManager  *dataManager = Indie::DataManager::getSingloton();

    while (true) {
        if (_locker.try_lock()) {
            try {
                dataManager->updateAllPlayers(User::getUser()->getRoomId(), mSceneManager);
                if (EntityManager::getMainPlayer()->isAlive())
                    dataManager->updatePlayerPos(User::getUser()->getLogName(), EntityManager::getMainPlayer()->getPosition());
                dataManager->listBomb(User::getUser()->getRoomId(), User::getUser()->getLogName());
                dataManager->getPowerUpList();
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                mError = true;
                EntityManager::unlockEntities();
                _locker.unlock();
                return ;
            }
            mScoreboard->removeAllItems();
            mScoreboard->addItem("#F1C40F" + EntityManager::getMainPlayer()->getPlayerId());
            mScoreboard->setSubItemNameAt(1, mScoreboard->getItemCount() - 1, std::to_string(EntityManager::getMainPlayer()->getScore()));

            std::vector<APlayer *>::iterator    it = EntityManager::getPlayerList().begin();
            while (it != EntityManager::getPlayerList().end()) {
                mScoreboard->addItem("#E74C3C" + (*it)->getPlayerId());
                mScoreboard->setSubItemNameAt(1, mScoreboard->getItemCount() - 1, std::to_string((*it)->getScore()));
                ++it;
            }
            _locker.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        else {
            return ;
        }
    }
}

bool    Indie::SceneDisplayer::updateScene() {
    std::vector<AEntity *>::iterator    it;

    EntityManager::lockEntities();
    if (!mResultHUD->getVisible() && (!EntityManager::getMainPlayer()->isAlive() || EntityManager::getPlayerList().size() == 0)) {
        mResultHUD->setVisible(true);
        mResultHUD->setImageTexture("ImageVictoire.png");
        if (!EntityManager::getMainPlayer()->isAlive()) {
            DataManager::getSingloton()->quitRoom(User::getUser()->getLogName());
            mResultHUD->setImageTexture("ImageDefaite.png");
        }
        mAnimationTime = Config::getWinLoseAnimationTime();
    }
    if (mResultHUD->getVisible() && mAnimationTime == 0) {
        EntityManager::unlockEntities();
        return false;
    }
    else if (mResultHUD->getVisible())
        mAnimationTime -= 1;
    if (mError || (!EntityManager::getMainPlayer()->updateFromLoop(mSceneManager) && !mResultHUD->getVisible())) {
        EntityManager::unlockEntities();
        return false;
    }
    it = EntityManager::getEntityList().begin();
    while (it != EntityManager::getEntityList().end()) {
        if (!(*it)->updateFromLoop(mSceneManager)) {
            EntityManager::getEntityList().erase(it);
        }
        else
            ++it;
    }
    std::vector<APlayer *>::iterator    itP;

    itP = EntityManager::getPlayerList().begin();
    while (itP != EntityManager::getPlayerList().end()) {
        if (!(*itP)->updateFromLoop(mSceneManager))
            EntityManager::getPlayerList().erase(itP);
        else
            ++itP;
    }

    std::vector<Bomb* >::iterator   itB = EntityManager::getBombList().begin();
    while (itB != EntityManager::getBombList().end()) {
        (*itB)->updateFromLoop(mSceneManager);
        ++itB;
    }

    std::vector<PowerUp *>::iterator    itPU = EntityManager::getPowerUpList().begin();

    while (itPU != EntityManager::getPowerUpList().end()) {
        if (!(*itPU)->checkCollide(*EntityManager::getMainPlayer())) {
            (*itPU)->boostPlayer(*EntityManager::getMainPlayer(), mSceneManager);
        }
        (*itPU)->updateFromLoop(mSceneManager);
        ++itPU;
    }
    EntityManager::unlockEntities();
    return true;
}

bool Indie::SceneDisplayer::makeCollide(Indie::APlayer *entity, OIS::KeyCode const& keyCode) {
    std::vector<Indie::AEntity* >::iterator it = EntityManager::getEntityList().begin();

    if (_collideGetter.find(keyCode) != _collideGetter.end()) {
        while (it != EntityManager::getEntityList().end()) {
            if (entity != (*it)) {
                if (!(this->*_collideGetter[keyCode])(entity, *it))
                    return false;
            }
            ++it;
        }
    }
    return true;
}

bool    Indie::SceneDisplayer::checkUp(APlayer *entity, AEntity const *collider) const {
    bool state = false;

    entity->rotate(APlayer::Direction::UP);
    entity->move(Ogre::Vector3(entity->getMoveSpeed(), 0, 0));
    if (entity->checkCollide(*collider)) {
        state = true;
    }
    entity->move(Ogre::Vector3(-entity->getMoveSpeed(), 0, 0));
    return state;
}

bool    Indie::SceneDisplayer::checkDown(APlayer *entity, AEntity const *collider) const {
    bool state = false;

    entity->rotate(APlayer::Direction::DOWN);
    entity->move(Ogre::Vector3(-entity->getMoveSpeed(), 0, 0));
    if (entity->checkCollide(*collider)) {
        state = true;
    }
    entity->move(Ogre::Vector3(entity->getMoveSpeed(), 0, 0));
    return state;
}

bool    Indie::SceneDisplayer::checkLeft(APlayer *entity, AEntity const *collider) const {
    bool state = false;

    entity->rotate(APlayer::Direction::LEFT);
    entity->move(Ogre::Vector3(0, 0, -entity->getMoveSpeed()));
    if (entity->checkCollide(*collider)) {
        state = true;
    }
    entity->move(Ogre::Vector3(0, 0, entity->getMoveSpeed()));
    return state;
}

bool    Indie::SceneDisplayer::checkRight(APlayer *entity, AEntity const *collider) const {
    bool state = false;

    entity->rotate(APlayer::Direction::RIGHT);
    entity->move(Ogre::Vector3(0, 0, entity->getMoveSpeed()));
    if (entity->checkCollide(*collider)) {
        state = true;
    }
    entity->move(Ogre::Vector3(0, 0, -entity->getMoveSpeed()));
    return state;
}

Indie::SceneDisplayer::~SceneDisplayer() {
    _locker.lock();
    _thread->join();
    EntityManager::lockEntities();
    EntityManager::removeAllEntities(mSceneManager);
    std::vector<std::unique_ptr<AEntity> >::iterator    it = _groundEntityList.begin();

    while (it != _groundEntityList.end()) {
        (*it)->destroyEntity(mSceneManager);
        ++it;
    }
    _groundEntityList.clear();
    mResultHUD->setVisible(false);
    EntityManager::unlockEntities();
    EntityManager::getEntityManager(true);
}

/**********************************
** Callback register
*//////////////////////////////////
void Indie::SceneDisplayer::initEventRegister() {
    _functionPtr.insert(std::make_pair(KEY_UP, &Indie::SceneDisplayer::movePlayerUp));
    _functionPtr.insert(std::make_pair(KEY_DOWN, &Indie::SceneDisplayer::movePlayerDown));
    _functionPtr.insert(std::make_pair(KEY_RIGHT, &Indie::SceneDisplayer::movePlayerRight));
    _functionPtr.insert(std::make_pair(KEY_LEFT, &Indie::SceneDisplayer::movePlayerLeft));
    _functionPtr.insert(std::make_pair(OIS::KC_UP, &Indie::SceneDisplayer::moveCameraUp));
    _functionPtr.insert(std::make_pair(OIS::KC_DOWN, &Indie::SceneDisplayer::moveCameraDown));

    _collideGetter.insert(std::make_pair(KEY_UP, &Indie::SceneDisplayer::checkUp));
    _collideGetter.insert(std::make_pair(KEY_DOWN, &Indie::SceneDisplayer::checkDown));
    _collideGetter.insert(std::make_pair(KEY_LEFT, &Indie::SceneDisplayer::checkLeft));
    _collideGetter.insert(std::make_pair(KEY_RIGHT, &Indie::SceneDisplayer::checkRight));
}

void    Indie::SceneDisplayer::registerKeyboardEvent(OIS::Keyboard *keyboard) {
    std::map<OIS::KeyCode, void (Indie::SceneDisplayer::*)(OIS::Keyboard *)>::iterator it;

    it = _functionPtr.begin();
    while (it != _functionPtr.end()) {
        if (keyboard->isKeyDown((*it).first) && (EntityManager::getMainPlayer()->isGodMode() || makeCollide(EntityManager::getMainPlayer(), (*it).first)))
            (this->*(*it).second)(keyboard);
        ++it;
    }
    Ogre::Camera    *camera = mSceneManager->getCamera("MainCam");
    if (camera && EntityManager::getMainPlayer()->isAlive()) {
        camera->setPosition(Ogre::Vector3(EntityManager::getMainPlayer()->getPosition().x - 200, camera->getPositionForViewUpdate().y, EntityManager::getMainPlayer()->getPosition().z));
        camera->lookAt(EntityManager::getMainPlayer()->getPosition());
    }
}

bool    Indie::SceneDisplayer::keyPressed(const OIS::KeyEvent &ke) {
    if (ke.key == OIS::KC_SPACE)
        EntityManager::getMainPlayer()->plantABomb(mSceneManager);
    else if (ke.key == OIS::KC_G)
        EntityManager::getMainPlayer()->godMode();
    else if (ke.key == OIS::KC_TAB)
        toggleScoreboard();
    return true;
}

bool    Indie::SceneDisplayer::keyReleased(const OIS::KeyEvent &ke) {
    if (ke.key == OIS::KC_TAB)
        toggleScoreboard();
    return true;
}

void    Indie::SceneDisplayer::registerMouseEvent(OIS::Mouse *mouse) {
    static_cast<void>(mouse);
}

void    Indie::SceneDisplayer::movePlayerDown(OIS::Keyboard *keyboard) {
    EntityManager::getMainPlayer()->move(Ogre::Vector3(-EntityManager::getMainPlayer()->getMoveSpeed(), 0, 0));
    if (keyboard->isKeyDown(KEY_LEFT) && !keyboard->isKeyDown(KEY_RIGHT))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::DOWN_LEFT);
    else if (keyboard->isKeyDown(KEY_RIGHT) && !keyboard->isKeyDown(KEY_LEFT))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::DOWN_RIGHT);
    else
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::DOWN);
}

void    Indie::SceneDisplayer::movePlayerLeft(OIS::Keyboard *keyboard) {
    EntityManager::getMainPlayer()->move(Ogre::Vector3(0, 0, -EntityManager::getMainPlayer()->getMoveSpeed()));
    if (keyboard->isKeyDown(KEY_DOWN) && !keyboard->isKeyDown(KEY_UP))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::DOWN_LEFT);
    else if (keyboard->isKeyDown(KEY_UP) && !keyboard->isKeyDown(KEY_DOWN))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::UP_LEFT);
    else
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::LEFT);
}

void    Indie::SceneDisplayer::movePlayerUp(OIS::Keyboard *keyboard) {
    EntityManager::getMainPlayer()->move(Ogre::Vector3(EntityManager::getMainPlayer()->getMoveSpeed(), 0, 0));
    if (keyboard->isKeyDown(KEY_LEFT) && !keyboard->isKeyDown(KEY_RIGHT))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::UP_LEFT);
    else if (keyboard->isKeyDown(KEY_RIGHT) && !keyboard->isKeyDown(KEY_LEFT))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::UP_RIGHT);
    else
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::UP);
}

void    Indie::SceneDisplayer::movePlayerRight(OIS::Keyboard *keyboard) {
    EntityManager::getMainPlayer()->move(Ogre::Vector3(0, 0, EntityManager::getMainPlayer()->getMoveSpeed()));
    if (keyboard->isKeyDown(KEY_UP) && !keyboard->isKeyDown(KEY_DOWN))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::UP_RIGHT);
    else if (keyboard->isKeyDown(KEY_DOWN) && !keyboard->isKeyDown(KEY_UP))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::DOWN_RIGHT);
    else
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::RIGHT);
}

void    Indie::SceneDisplayer::moveCameraUp(OIS::Keyboard *keyboard) {
    Ogre::Camera    *camera = mSceneManager->getCamera("MainCam");

    static_cast<void>(keyboard);
    if (camera) {
        camera->setPosition(Ogre::Vector3(EntityManager::getMainPlayer()->getPosition().x - 200, camera->getPositionForViewUpdate().y + 10, EntityManager::getMainPlayer()->getPosition().z));
        camera->lookAt(EntityManager::getMainPlayer()->getPosition());
    }
}

void    Indie::SceneDisplayer::moveCameraDown(OIS::Keyboard *keyboard) {
    Ogre::Camera    *camera = mSceneManager->getCamera("MainCam");

    static_cast<void>(keyboard);
    if (camera) {
        camera->setPosition(Ogre::Vector3(EntityManager::getMainPlayer()->getPosition().x - 200, camera->getPositionForViewUpdate().y - 10, EntityManager::getMainPlayer()->getPosition().z));
        camera->lookAt(EntityManager::getMainPlayer()->getPosition());
    }
}

bool Indie::SceneDisplayer::mouseMoved( const OIS::MouseEvent &arg)
{
    static_cast<void>(arg);
    return true;
}

bool Indie::SceneDisplayer::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    static_cast<void>(arg);
    static_cast<void>(id);
    return true;
}

bool Indie::SceneDisplayer::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    static_cast<void>(arg);
    static_cast<void>(id);
    return true;
}

void    Indie::SceneDisplayer::toggleScoreboard() {
    mToggleScoreboard = !mToggleScoreboard;
    mScoreboard->setVisible(mToggleScoreboard);
}