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
    ret.y = 35;
    return (ret);
}

Indie::Bomb::Bomb(Ogre::SceneManager *sceneManager, const Indie::APlayer& delegate) : AEntity(sceneManager, getBombPosition(delegate), "bomb.mesh"), ExplosableEntity() {
    mSceneNode->setScale(Ogre::Vector3(5.0f, 5.0f, 5.0f));
    mTransformation = Ogre::Vector3(5.0f, 5.0f, 5.0f);
    _explodeTime = Config::getExplodeTime();
    addParticlesColor("Particles/Blue");
    addParticlesColor("Particles/Grey");
    _id = -1;
    _explodeSize = delegate.getBombRange();
}

Indie::Bomb::Bomb(int id, int x, int y, int power) : AEntity(NULL, Ogre::Vector3(x, 35, y), "bomb.mesh", true), ExplosableEntity() {
    mTransformation = Ogre::Vector3(5.0f, 5.0f, 5.0f);
    addParticlesColor("Particles/Blue");
    addParticlesColor("Particles/Grey");
    _explodeTime = Config::getExplodeTime();
    _explodeSize = power;
    _id = id;
}

int const&     Indie::Bomb::getID() const {
    return _id;
}

bool    Indie::Bomb::hittedByExplosion() const {
    return true;
}

bool    Indie::Bomb::updateFromLoop(Ogre::SceneManager *sceneManager) {
    std::vector<std::unique_ptr<Indie::AEntity> >::iterator it;

    //std::cout << "On Update " << isWaiting() << std::endl;
    if (isWaiting()) {
        std::cout << "Entity created" << std::endl;
        Indie::AEntity::createEntity(sceneManager);
    }
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
        {
            createAllParticles(sceneManager, getPosition(), getSize().y);
            this->explode(sceneManager);
        }
        else
            _explodeTime -= 1;
    }
    else
        return (updateParticles(sceneManager) || _explosionList.size() > 0);
    return true;
}

bool    Indie::Bomb::haveEntityWithPos(Ogre::Vector3 const& entityPos, bool& shouldContinue) const {
    std::vector<std::shared_ptr<AEntity> >::iterator    it = EntityManager::getEntityList().begin();
    bool    ret = shouldContinue;

    while (it != EntityManager::getEntityList().end()) {
        if ((*it)->getPosition().x == entityPos.x && (*it)->getPosition().z == entityPos.z) {
            shouldContinue = false;
            if (ret)
                return false;
            return true;
        }
        ++it;
    }
    return false;
}

void    Indie::Bomb::explode(Ogre::SceneManager *sceneManager) {
    unsigned int    i;
    bool            leftContinue = true;
    bool            rightContinue = true;
    bool            upContinue = true;
    bool            downContinue = true;

    i = 0;
    _explosionList.push_back(std::unique_ptr<Indie::AEntity>(new Indie::Explosion(sceneManager, Ogre::Vector3(getPosition().x, getPosition().y - 35, getPosition().z))));
    while (i < _explodeSize) {

        if (downContinue && !haveEntityWithPos(Ogre::Vector3(getPosition().x - (100 * (i + 1)), getPosition().y - 35, getPosition().z), downContinue))
            _explosionList.push_back(std::unique_ptr<Indie::AEntity>(new Indie::Explosion(sceneManager, Ogre::Vector3(getPosition().x - (100 * (i + 1)), getPosition().y - 35, getPosition().z))));
        if (upContinue && !haveEntityWithPos(Ogre::Vector3(getPosition().x + (100 * (i + 1)), getPosition().y - 35, getPosition().z), upContinue))
            _explosionList.push_back(std::unique_ptr<Indie::AEntity>(new Indie::Explosion(sceneManager, Ogre::Vector3(getPosition().x + (100 * (i + 1)), getPosition().y - 35, getPosition().z))));
        if (leftContinue && !haveEntityWithPos(Ogre::Vector3(getPosition().x, getPosition().y - 35, getPosition().z - (100 * (i + 1))), leftContinue))
            _explosionList.push_back(std::unique_ptr<Indie::AEntity>(new Indie::Explosion(sceneManager, Ogre::Vector3(getPosition().x, getPosition().y - 35, getPosition().z - (100 * (i + 1))))));
        if (rightContinue && !haveEntityWithPos(Ogre::Vector3(getPosition().x, getPosition().y - 35, getPosition().z + (100 * (i + 1))), rightContinue))
            _explosionList.push_back(std::unique_ptr<Indie::AEntity>(new Indie::Explosion(sceneManager, Ogre::Vector3(getPosition().x, getPosition().y - 35, getPosition().z + (100 * (i + 1))))));
        ++i;
    }
    std::vector<std::unique_ptr<Indie::AEntity> >::iterator   explosionIt = _explosionList.begin();
    std::vector<std::shared_ptr<Indie::AEntity> >&  entityList = EntityManager::getEntityList();

    while (explosionIt != _explosionList.end()) {
        std::vector<std::shared_ptr<Indie::AEntity> >::iterator itEntity = entityList.begin();
        if (!EntityManager::getMainPlayer()->checkCollide(*(*explosionIt))) {
            EntityManager::getMainPlayer()->explode(sceneManager);
        }
        while (itEntity != entityList.end()) {
            if ((*itEntity)->hittedByExplosion()) {
                if (!(*itEntity)->checkCollide(*(*explosionIt))) {
                    (*itEntity)->explode(sceneManager);
                }
                else
                    ++itEntity;
            }
            else
                ++itEntity;
        }
        ++explosionIt;
    }
    Indie::AEntity::explode(sceneManager);
}

Indie::Bomb::~Bomb() {}
