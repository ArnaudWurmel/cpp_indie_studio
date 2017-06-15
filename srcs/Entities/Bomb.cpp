//
// Created by wurmel_a on 26/05/17.
//

#include <iostream>
#include "Bomb.h"
#include "../Player/APlayer.hh"
#include "EntityManager.hh"
#include "../DataManager/DataManager.h"
#include "../SoundManager/SoundManager.hh"

Ogre::Vector3   Indie::Bomb::getBombPosition(const APlayer& player) {
    Ogre::Vector3   ret;

    if (player.getPosition().x >= 0) {
        ret.x = player.getPosition().x - (static_cast<int>(player.getPosition().x) % 100);
        if (MapParser::getMapParser("").getMap().size() % 2)
            ret.x += 50;
        else if (static_cast<int>(player.getPosition().x) % 100 >= 50) {
            ret.x += 100;
        }
    }
    else {
        ret.x = player.getPosition().x - (static_cast<int>(player.getPosition().x) % 100);
        if (MapParser::getMapParser("").getMap().size() % 2)
            ret.x -= 50;
        else if (static_cast<int>(player.getPosition().x) % 100 <= -50) {
            ret.x -= 100;
        }
    }
    if (player.getPosition().z >= 0) {
        ret.z = player.getPosition().z - (static_cast<int>(player.getPosition().z) % 100);
        if ((*MapParser::getMapParser("").getMap().begin()).size() % 2)
            ret.z += 50;
        else if (static_cast<int>(player.getPosition().z) % 100 >= 50) {
            ret.z += 100;
        }
    }
    else {
        ret.z = player.getPosition().z - (static_cast<int>(player.getPosition().z) % 100);
        if ((*MapParser::getMapParser("").getMap().begin()).size() % 2)
            ret.z -= 50;
        else if (static_cast<int>(player.getPosition().z) % 100 <= -50)
            ret.z -= 100;
    }
    ret.x = static_cast<int>(ret.x);
    ret.z = static_cast<int>(ret.z);
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
    _pId = "";
}

Indie::Bomb::Bomb(std::string const& pId, int id, int x, int y, int power) : AEntity(NULL, Ogre::Vector3(x, 35, y), "bomb.mesh", true), ExplosableEntity() {
    mTransformation = Ogre::Vector3(5.0f, 5.0f, 5.0f);
    addParticlesColor("Particles/Blue");
    addParticlesColor("Particles/Grey");
    _explodeTime = Config::getExplodeTime();
    _explodeSize = power;
    _id = id;
    _pId = pId;
}

int const&     Indie::Bomb::getID() const {
    return _id;
}

bool    Indie::Bomb::hittedByExplosion() const {
    return true;
}

bool    Indie::Bomb::updateFromLoop(Ogre::SceneManager *sceneManager) {
    std::vector<std::unique_ptr<Indie::AEntity> >::iterator it;

    if (isWaiting()) {
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
        if (_explodeTime == 45)
            SoundManager::getSingloton()->loadSound("resources/sound/bomb.ogg");
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
    std::vector<AEntity *>::iterator    it = EntityManager::getEntityList().begin();
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
    std::vector<Indie::AEntity *>&  entityList = EntityManager::getEntityList();

    while (explosionIt != _explosionList.end()) {
        std::vector<Indie::AEntity *>::iterator itEntity = entityList.begin();
        if (!EntityManager::getMainPlayer()->checkCollide(*(*explosionIt))) {
            if (_id != -1)
                DataManager::getSingloton()->getKilledBy(getPId());
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

std::string const&  Indie::Bomb::getPId() const {
    return _pId;
}

void    Indie::Bomb::destroyEntity(Ogre::SceneManager *sceneManager) {
    removeAllParticles(sceneManager);
    std::vector<std::unique_ptr<Indie::AEntity> >::iterator it = _explosionList.begin();

    while (it != _explosionList.end()) {
        (*it)->destroyEntity(sceneManager);
        ++it;
    }
    _explosionList.clear();
    Indie::AEntity::destroyEntity(sceneManager);
}

Indie::Bomb::~Bomb() {}
