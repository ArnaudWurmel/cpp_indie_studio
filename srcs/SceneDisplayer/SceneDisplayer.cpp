//
// Created by wurmel on 13/05/17.
//

#include <iostream>
#include "SceneDisplayer.hh"
#include "../Entities/EntityManager.hh"
#include "../Player/HumanPlayer.hh"
#include "../DataManager/DataManager.h"

Indie::SceneDisplayer::SceneDisplayer(Ogre::SceneManager *sceneManager) {
    mSceneManager = sceneManager;
}

void Indie::SceneDisplayer::initScene() {
    MapParser&  mapParser = MapParser::getMapParser("resources/maps/level0");

    this->createGround();
    _map = mapParser.getMap();
    if (_map.size() > 0) {
        this->createMap();
    }
    bool    success = false;

    DataManager *dataManager = Indie::DataManager::getSingloton();
    Ogre::Vector3   posPlayer = dataManager->getPlayerStart("Thibaud", success);
    if (!success)
        throw std::exception();
    EntityManager::createHuman(mSceneManager, Ogre::Vector3(posPlayer.x, 25, posPlayer.z), "Thibaud");
    initEventRegister();
    _thread = std::unique_ptr<std::thread>(new std::thread(&Indie::SceneDisplayer::updaterThread, this));
}

void Indie::SceneDisplayer::createGround() {
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
            "ground",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            plane,
            5000, 5000, 20, 20,
            true,
            1, 5, 5,
            Ogre::Vector3::UNIT_Z
    );
    Ogre::Entity    *groundEntity = mSceneManager->createEntity("ground");
    mSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("Bomberman/Ground");
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
            ++it_line;
            ++j;
        }
        ++i;
        ++it;
    }
}

void    Indie::SceneDisplayer::updaterThread() {
    Indie::DataManager  *dataManager = Indie::DataManager::getSingloton();

    while (true) {
        if (_locker.try_lock()) {
            dataManager->updateAllPlayers(0, mSceneManager);
            if (EntityManager::getMainPlayer()->isAlive())
                dataManager->updatePlayerPos("Thibaud", EntityManager::getMainPlayer()->getPosition());
            dataManager->listBomb(0, "Thibaud");
            _locker.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        else {
            return ;
        }
    }
}

bool    Indie::SceneDisplayer::updateScene() {
    std::vector<std::shared_ptr<AEntity> >::iterator    it;

    if (!EntityManager::getMainPlayer()->updateFromLoop(mSceneManager))
        return false;
    it = EntityManager::getEntityList().begin();
    while (it != EntityManager::getEntityList().end()) {
        if (!(*it)->updateFromLoop(mSceneManager)) {
            EntityManager::getEntityList().erase(it);
        }
        else
            ++it;
    }
    std::vector<std::unique_ptr<APlayer> >::iterator    itP;

    itP = EntityManager::getPlayerList().begin();
    while (itP != EntityManager::getPlayerList().end()) {
        if (!(*itP)->updateFromLoop(mSceneManager))
            EntityManager::getPlayerList().erase(itP);
        else
            ++itP;
    }

    std::vector<std::unique_ptr<Bomb> >::iterator   itB = EntityManager::getBombList().begin();
    while (itB != EntityManager::getBombList().end()) {
        (*itB)->updateFromLoop(mSceneManager);
        ++itB;
    }
    return true;
}

bool Indie::SceneDisplayer::makeCollide(std::unique_ptr<Indie::APlayer> &entity, OIS::KeyCode const& keyCode) {
    std::vector<std::shared_ptr<Indie::AEntity> >::iterator it = EntityManager::getEntityList().begin();

    if (_collideGetter.find(keyCode) != _collideGetter.end()) {
        while (it != EntityManager::getEntityList().end()) {
            if (entity.get() != (*it).get()) {
                if (!(this->*_collideGetter[keyCode])(entity, *it))
                    return false;
            }
            ++it;
        }
    }
    return true;
}

bool    Indie::SceneDisplayer::checkUp(std::unique_ptr<APlayer>& entity, std::shared_ptr<AEntity> const& collider) const {
    bool state = false;

    entity->rotate(APlayer::Direction::UP);
    entity->move(Ogre::Vector3(entity->getMoveSpeed(), 0, 0));
    if (entity->checkCollide(*(collider.get()))) {
        state = true;
    }
    entity->move(Ogre::Vector3(-entity->getMoveSpeed(), 0, 0));
    return state;
}

bool    Indie::SceneDisplayer::checkDown(std::unique_ptr<APlayer>& entity, std::shared_ptr<AEntity> const& collider) const {
    bool state = false;

    entity->rotate(APlayer::Direction::DOWN);
    entity->move(Ogre::Vector3(-entity->getMoveSpeed(), 0, 0));
    if (entity->checkCollide(*(collider.get()))) {
        state = true;
    }
    entity->move(Ogre::Vector3(entity->getMoveSpeed(), 0, 0));
    return state;
}

bool    Indie::SceneDisplayer::checkLeft(std::unique_ptr<APlayer>& entity, std::shared_ptr<AEntity> const& collider) const {
    bool state = false;

    entity->rotate(APlayer::Direction::LEFT);
    entity->move(Ogre::Vector3(0, 0, -entity->getMoveSpeed()));
    if (entity->checkCollide(*(collider.get()))) {
        state = true;
    }
    entity->move(Ogre::Vector3(0, 0, entity->getMoveSpeed()));
    return state;
}

bool    Indie::SceneDisplayer::checkRight(std::unique_ptr<APlayer>& entity, std::shared_ptr<AEntity> const& collider) const {
    bool state = false;

    entity->rotate(APlayer::Direction::RIGHT);
    entity->move(Ogre::Vector3(0, 0, entity->getMoveSpeed()));
    if (entity->checkCollide(*(collider.get()))) {
        state = true;
    }
    entity->move(Ogre::Vector3(0, 0, -entity->getMoveSpeed()));
    return state;
}

Indie::SceneDisplayer::~SceneDisplayer() {
    std::cout << "Deleting..." << std::endl;
    std::cout << _thread->joinable() << std::endl;
    _locker.lock();
    std::cout << "Mutex locked" << std::endl;
    _thread->join();
}

/**********************************
** Callback register
*//////////////////////////////////
void Indie::SceneDisplayer::initEventRegister() {
    _functionPtr.insert(std::make_pair(OIS::KC_Z, &Indie::SceneDisplayer::movePlayerUp));
    _functionPtr.insert(std::make_pair(OIS::KC_S, &Indie::SceneDisplayer::movePlayerDown));
    _functionPtr.insert(std::make_pair(OIS::KC_D, &Indie::SceneDisplayer::movePlayerRight));
    _functionPtr.insert(std::make_pair(OIS::KC_Q, &Indie::SceneDisplayer::movePlayerLeft));
    _functionPtr.insert(std::make_pair(OIS::KC_UP, &Indie::SceneDisplayer::moveCameraUp));
    _functionPtr.insert(std::make_pair(OIS::KC_DOWN, &Indie::SceneDisplayer::moveCameraDown));

    _collideGetter.insert(std::make_pair(OIS::KC_Z, &Indie::SceneDisplayer::checkUp));
    _collideGetter.insert(std::make_pair(OIS::KC_S, &Indie::SceneDisplayer::checkDown));
    _collideGetter.insert(std::make_pair(OIS::KC_Q, &Indie::SceneDisplayer::checkLeft));
    _collideGetter.insert(std::make_pair(OIS::KC_D, &Indie::SceneDisplayer::checkRight));
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
    if (keyboard->isKeyDown(OIS::KC_M)) {
        std::vector<std::shared_ptr<AEntity> >::iterator    it;

        it = EntityManager::getEntityList().begin();
        while (it != EntityManager::getEntityList().end()) {
            if ((*it)->hittedByExplosion()) {
                (*it)->explode(mSceneManager);
                return ;
            }
            ++it;
        }
    }
}

bool    Indie::SceneDisplayer::keyPressed(const OIS::KeyEvent &ke) {
    if (ke.key == OIS::KC_SPACE) {
        EntityManager::getMainPlayer()->plantABomb(mSceneManager);
    }
    else if (ke.key == OIS::KC_G)
        EntityManager::getMainPlayer()->godMode();
    return true;
}

bool    Indie::SceneDisplayer::keyReleased(const OIS::KeyEvent &ke) {
    static_cast<void>(ke);
}

void    Indie::SceneDisplayer::registerMouseEvent(OIS::Mouse *mouse) {
    static_cast<void>(mouse);
}

void    Indie::SceneDisplayer::movePlayerDown(OIS::Keyboard *keyboard) {
    EntityManager::getMainPlayer()->move(Ogre::Vector3(-EntityManager::getMainPlayer()->getMoveSpeed(), 0, 0));
    if (keyboard->isKeyDown(OIS::KC_Q) && !keyboard->isKeyDown(OIS::KC_D))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::DOWN_LEFT);
    else if (keyboard->isKeyDown(OIS::KC_D) && !keyboard->isKeyDown(OIS::KC_Q))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::DOWN_RIGHT);
    else
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::DOWN);
}

void    Indie::SceneDisplayer::movePlayerLeft(OIS::Keyboard *keyboard) {
    EntityManager::getMainPlayer()->move(Ogre::Vector3(0, 0, -EntityManager::getMainPlayer()->getMoveSpeed()));
    if (keyboard->isKeyDown(OIS::KC_S) && !keyboard->isKeyDown(OIS::KC_Z))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::DOWN_LEFT);
    else if (keyboard->isKeyDown(OIS::KC_Z) && !keyboard->isKeyDown(OIS::KC_S))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::UP_LEFT);
    else
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::LEFT);
}

void    Indie::SceneDisplayer::movePlayerUp(OIS::Keyboard *keyboard) {
    EntityManager::getMainPlayer()->move(Ogre::Vector3(EntityManager::getMainPlayer()->getMoveSpeed(), 0, 0));
    if (keyboard->isKeyDown(OIS::KC_Q) && !keyboard->isKeyDown(OIS::KC_D))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::UP_LEFT);
    else if (keyboard->isKeyDown(OIS::KC_D) && !keyboard->isKeyDown(OIS::KC_Q))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::UP_RIGHT);
    else
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::UP);
}

void    Indie::SceneDisplayer::movePlayerRight(OIS::Keyboard *keyboard) {
    EntityManager::getMainPlayer()->move(Ogre::Vector3(0, 0, EntityManager::getMainPlayer()->getMoveSpeed()));
    if (keyboard->isKeyDown(OIS::KC_Z) && !keyboard->isKeyDown(OIS::KC_S))
        EntityManager::getMainPlayer()->rotate(AEntity::Direction::UP_RIGHT);
    else if (keyboard->isKeyDown(OIS::KC_S) && !keyboard->isKeyDown(OIS::KC_Z))
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
    if (camera) {
        camera->setPosition(Ogre::Vector3(EntityManager::getMainPlayer()->getPosition().x - 200, camera->getPositionForViewUpdate().y - 10, EntityManager::getMainPlayer()->getPosition().z));
        camera->lookAt(EntityManager::getMainPlayer()->getPosition());
    }
}