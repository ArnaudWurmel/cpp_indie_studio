//
// Created by wurmel on 13/05/17.
//

#include <iostream>
#include "SceneDisplayer.hh"
#include "../Entities/EntityManager.hh"
#include "../Config/Config.hh"

Indie::SceneDisplayer::SceneDisplayer(Ogre::SceneManager *sceneManager) {
    mSceneManager = sceneManager;
}

void Indie::SceneDisplayer::initScene() {
    MapParser   mapParser("resources/maps/level0");

    this->createGround();
    _map = mapParser.getMap();
    if (_map.size() > 0) {
        this->createMap();
    }
    _player = std::unique_ptr<AEntity>(EntityManager::createEntity(MapParser::PLAYER, mSceneManager, Ogre::Vector3(0, 50, 0)));
    initEventRegister();
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
    int    i;
    int    j;

    it = _map.begin();
    i = 0;
    while (it != _map.end()) {
        std::vector<MapParser::TileType>::iterator  it_line;
        j = 0;
        it_line = (*it).begin();
        while (it_line != (*it).end()) {
            long x = _map.size() * 100 / 2 - (i * 100);
            long z = ((*it).size() * 100) / 2 - (100 * j);
            Indie::AEntity  *entity = EntityManager::createEntity(*it_line, mSceneManager, Ogre::Vector3(x, 50, z));
            if (entity != nullptr) {
                _entityList.push_back(std::unique_ptr<AEntity>(entity));
            }
            ++it_line;
            ++j;
        }
        ++i;
        ++it;
    }
}

void    Indie::SceneDisplayer::updateScene() {
    std::vector<std::unique_ptr<AEntity> >::iterator    it;

    it = _entityList.begin();
    while (it != _entityList.end()) {
        if (!(*it)->updateFromLoop(mSceneManager)) {
            _entityList.erase(it);
        }
        else
            ++it;
    }
}

Indie::SceneDisplayer::~SceneDisplayer() {}

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
}

void    Indie::SceneDisplayer::registerKeyboardEvent(OIS::Keyboard *keyboard) {
    std::map<OIS::KeyCode, void (Indie::SceneDisplayer::*)(OIS::Keyboard *)>::iterator it;

    it = _functionPtr.begin();
    while (it != _functionPtr.end()) {
        if (keyboard->isKeyDown((*it).first))
            (this->*(*it).second)(keyboard);
        ++it;
    }
    Ogre::Camera    *camera = mSceneManager->getCamera("MainCam");
    if (camera) {
        camera->setPosition(Ogre::Vector3(_player->getPosition().x - 200, camera->getPositionForViewUpdate().y, _player->getPosition().z));
        camera->lookAt(_player->getPosition());
    }

    if (keyboard->isKeyDown(OIS::KC_M)) {
        std::vector<std::unique_ptr<AEntity> >::iterator    it;

        it = _entityList.begin();
        while (it != _entityList.end()) {
            if ((*it)->hittedByExplosion()) {
                (*it)->explode(mSceneManager);
                return ;
            }
            ++it;
        }
    }
}

void    Indie::SceneDisplayer::registerMouseEvent(OIS::Mouse *mouse) {
    static_cast<void>(mouse);
}

void    Indie::SceneDisplayer::movePlayerDown(OIS::Keyboard *keyboard) {
    _player->move(Ogre::Vector3(-Indie::Config::getMoveSpeed(), 0, 0));
    if (keyboard->isKeyDown(OIS::KC_Q) && !keyboard->isKeyDown(OIS::KC_D))
        _player->rotate(AEntity::Direction::DOWN_LEFT);
    else if (keyboard->isKeyDown(OIS::KC_D) && !keyboard->isKeyDown(OIS::KC_Q))
        _player->rotate(AEntity::Direction::DOWN_RIGHT);
    else
        _player->rotate(AEntity::Direction::DOWN);
}

void    Indie::SceneDisplayer::movePlayerLeft(OIS::Keyboard *keyboard) {
    _player->move(Ogre::Vector3(0, 0, -Indie::Config::getMoveSpeed()));
    if (keyboard->isKeyDown(OIS::KC_S) && !keyboard->isKeyDown(OIS::KC_Z))
        _player->rotate(AEntity::Direction::DOWN_LEFT);
    else if (keyboard->isKeyDown(OIS::KC_Z) && !keyboard->isKeyDown(OIS::KC_S))
        _player->rotate(AEntity::Direction::UP_LEFT);
    else
        _player->rotate(AEntity::Direction::LEFT);
}

void    Indie::SceneDisplayer::movePlayerUp(OIS::Keyboard *keyboard) {
    _player->move(Ogre::Vector3(Indie::Config::getMoveSpeed(), 0, 0));
    if (keyboard->isKeyDown(OIS::KC_Q) && !keyboard->isKeyDown(OIS::KC_D))
        _player->rotate(AEntity::Direction::UP_LEFT);
    else if (keyboard->isKeyDown(OIS::KC_D) && !keyboard->isKeyDown(OIS::KC_Q))
        _player->rotate(AEntity::Direction::UP_RIGHT);
    else
        _player->rotate(AEntity::Direction::UP);
}

void    Indie::SceneDisplayer::movePlayerRight(OIS::Keyboard *keyboard) {
    _player->move(Ogre::Vector3(0, 0, Indie::Config::getMoveSpeed()));
    if (keyboard->isKeyDown(OIS::KC_Z) && !keyboard->isKeyDown(OIS::KC_S))
        _player->rotate(AEntity::Direction::UP_RIGHT);
    else if (keyboard->isKeyDown(OIS::KC_S) && !keyboard->isKeyDown(OIS::KC_Z))
        _player->rotate(AEntity::Direction::DOWN_RIGHT);
    else
        _player->rotate(AEntity::Direction::RIGHT);
}

void    Indie::SceneDisplayer::moveCameraUp(OIS::Keyboard *keyboard) {
    Ogre::Camera    *camera = mSceneManager->getCamera("MainCam");
    if (camera) {
        camera->setPosition(Ogre::Vector3(_player->getPosition().x - 200, camera->getPositionForViewUpdate().y + 10, _player->getPosition().z));
        camera->lookAt(_player->getPosition());
    }
}

void    Indie::SceneDisplayer::moveCameraDown(OIS::Keyboard *keyboard) {
    Ogre::Camera    *camera = mSceneManager->getCamera("MainCam");
    if (camera) {
        camera->setPosition(Ogre::Vector3(_player->getPosition().x - 200, camera->getPositionForViewUpdate().y - 10, _player->getPosition().z));
        camera->lookAt(_player->getPosition());
    }
}