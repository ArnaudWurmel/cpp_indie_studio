//
// Created by wurmel_a on 11/06/17.
//

#include "PowerUp.hh"

Indie::PowerUp::PowerUp(Ogre::SceneManager *sceneManager, std::string const& entityName, Ogre::Vector3 const& entityPos, int id) : AEntity(sceneManager, entityPos, entityName.c_str(), true) {
    _id = id;
    _mTime = 0;
    _isTaken = false;
}

bool    Indie::PowerUp::isTaken() const {
    return _isTaken;
}

void    Indie::PowerUp::setTaken(bool value) {
    _isTaken = value;
}

bool    Indie::PowerUp::updateFromLoop(Ogre::SceneManager *sceneManager) {
    if (isWaiting())
        createEntity(sceneManager);
    if (mBackgroundKill) {
        mBackgroundKill = false;
        explode(sceneManager);
    }
    if (_mTime < 50)
        this->move(Ogre::Vector3(0, 1, 0));
    else
        this->move(Ogre::Vector3(0, -1, 0));
    this->rotate((mRotation + 1) % 360);
    _mTime = (_mTime + 1) % 100;
    updateParticles(sceneManager);
    return true;
}

bool    Indie::PowerUp::hittedByExplosion() const {
    return false;
}

void    Indie::PowerUp::explode(Ogre::SceneManager *sceneManager) {
    if (sceneManager && mSceneNode != NULL && mEntity != NULL) {
        createAllParticles(sceneManager, getPosition(), getSize().y * 200);
        Indie::AEntity::explode(sceneManager);
    }
    else
        mBackgroundKill = true;
}

void    Indie::PowerUp::destroyEntity(Ogre::SceneManager *sceneManager) {
    removeAllParticles(sceneManager);
    Indie::AEntity::destroyEntity(sceneManager);
}

int Indie::PowerUp::getID() const {
    return _id;
}

Indie::PowerUp::~PowerUp() {}