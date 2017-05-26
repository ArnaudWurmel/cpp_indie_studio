//
// Created by wurmel_a on 26/05/17.
//

#include <iostream>
#include "Bomb.h"
#include "../Player/APlayer.hh"
#include "EntityManager.hh"

Ogre::Vector3   Indie::Bomb::getBombPosition(const APlayer& player) {
    Ogre::Vector3   ret;

    if (player.getPosition().x > 0)
        ret.x = player.getPosition().x - (static_cast<int>(player.getPosition().x) % 100) + 50;
    else
        ret.x = player.getPosition().x - (static_cast<int>(player.getPosition().x) % 100) - 50;
    ret.y = 50;
    if (player.getPosition().z > 0)
        ret.z = player.getPosition().z - (static_cast<int>(player.getPosition().z) % 100) + 50;
    else
        ret.z = player.getPosition().z - (static_cast<int>(player.getPosition().z) % 100) - 50;
    return (ret);
}

Indie::Bomb::Bomb(Ogre::SceneManager *sceneManager, const Indie::APlayer& delegate) : AEntity(sceneManager, getBombPosition(delegate), "bomb.mesh"), _delegate(delegate) {
    mSceneNode->setScale(Ogre::Vector3(5.0f, 5.0f, 5.0f));
    mTransformation = Ogre::Vector3(10.0f, 10.0f, 10.0f);
    _explodeTime = Config::getExplodeTime();
}

bool    Indie::Bomb::hittedByExplosion() const {
    return true;
}

bool    Indie::Bomb::updateFromLoop(Ogre::SceneManager *sceneManager) {
    static_cast<void>(sceneManager);
    std::vector<std::unique_ptr<Indie::AEntity> >::iterator it;

    it = _explosionList.begin();
    while (it != _explosionList.end()) {
        if (!(*it)->updateFromLoop(sceneManager)) {
            (*it)->explode(sceneManager);
            _explosionList.erase(it);
        }
        else
            ++it;
    }
    if (mIsAlive) {
        if (!_explodeTime)
            this->explode(sceneManager);
        else
            _explodeTime -= 1;
    }
    else
        return _explosionList.size() > 0;
    return true;
}

void    Indie::Bomb::explode(Ogre::SceneManager *sceneManager) {
    unsigned int    i;

    i = 0;
    _explosionList.push_back(std::unique_ptr<Indie::AEntity>(new Indie::Explosion(sceneManager, Ogre::Vector3(getPosition().x, getPosition().y - 35, getPosition().z))));
    while (i < _delegate.getBombRange()) {
        _explosionList.push_back(std::unique_ptr<Indie::AEntity>(new Indie::Explosion(sceneManager, Ogre::Vector3(getPosition().x - (100 * (i + 1)), getPosition().y - 35, getPosition().z))));
        _explosionList.push_back(std::unique_ptr<Indie::AEntity>(new Indie::Explosion(sceneManager, Ogre::Vector3(getPosition().x + (100 * (i + 1)), getPosition().y - 35, getPosition().z))));
        _explosionList.push_back(std::unique_ptr<Indie::AEntity>(new Indie::Explosion(sceneManager, Ogre::Vector3(getPosition().x, getPosition().y - 35, getPosition().z - (100 * (i + 1))))));
        _explosionList.push_back(std::unique_ptr<Indie::AEntity>(new Indie::Explosion(sceneManager, Ogre::Vector3(getPosition().x, getPosition().y - 35, getPosition().z + (100 * (i + 1))))));
        ++i;
    }
    std::vector<std::unique_ptr<Indie::AEntity> >::iterator   explosionIt = _explosionList.begin();
    std::vector<std::shared_ptr<Indie::AEntity> >&  entityList = EntityManager::getEntityList();

    while (explosionIt != _explosionList.end()) {
        std::vector<std::shared_ptr<Indie::AEntity> >::iterator itEntity = entityList.begin();

        while (itEntity != entityList.end()) {
            if (!(*itEntity)->checkCollide(*(*explosionIt))) {
                (*itEntity)->explode(sceneManager);
            }
            else
                ++itEntity;
        }
        ++explosionIt;
    }
    Indie::AEntity::explode(sceneManager);
}

Indie::Bomb::~Bomb() {}
