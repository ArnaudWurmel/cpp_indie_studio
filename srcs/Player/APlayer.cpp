//
// Created by wurmel on 22/05/17.
//

#include <iostream>
#include "APlayer.hh"
#include "../Config/Config.hh"
#include "../DataManager/DataManager.h"

Indie::APlayer::APlayer(const Indie::APlayer::PlayerType &pType,
                        Ogre::Vector3 const& entityPos,
                        Ogre::SceneManager *sceneManager,
                        const char *entityMesh) : AEntity(sceneManager, entityPos, entityMesh)
{
    mSceneNode->showBoundingBox(true);
    _moveSpeed = Indie::Config::getMoveSpeed();
    _nbBombs = Indie::Config::getInitialNbBomb();
    _bombRange = Indie::Config::getBombRange();
    _godMode = false;
    _frameUpdate = Config::getNbTicks();
    _countFrame = 0;
    _updated = false;
    _pId = "";
}


bool Indie::APlayer::hittedByExplosion() const {
    return isAlive();
}

bool    Indie::APlayer::updateFromLoop(Ogre::SceneManager *sceneManager) {
    std::vector<std::unique_ptr<Bomb> >::iterator   it;

    it = _bombList.begin();
    while (it != _bombList.end()) {
        if (!(*it)->updateFromLoop(sceneManager))
            _bombList.erase(it);
        else
            ++it;
    }
    if (isAlive()) {
        if (60 / _frameUpdate == _countFrame) {
            DataManager *dataManager = DataManager::getSingloton();

            dataManager->updatePlayerPos("Erwan", getPosition());
            _countFrame = 0;
        }
        ++_countFrame;
    }
    return isAlive() || updateParticles(sceneManager);
}

void    Indie::APlayer::explode(Ogre::SceneManager *sceneManager) {
    if (mSceneNode != NULL && mEntity != NULL) {
        createAllParticles(sceneManager, getPosition(), getSize().y * 200);
        Indie::AEntity::explode(sceneManager);
    }
}

std::string const&  Indie::APlayer::getPlayerId() const {
    return _pId;
}

Ogre::Real    Indie::APlayer::getRotation() const {
    return mRotation;
}

void    Indie::APlayer::setUpdate(bool const& value) {
    _updated = value;
}

bool const&    Indie::APlayer::isUpdate() const {
    return _updated;
}

/****************************
** Player's stat
*////////////////////////////
Ogre::Real const&    Indie::APlayer::getMoveSpeed() const {
    return _moveSpeed;
}

/*
 * Speed power-up
 */
void    Indie::APlayer::setMoveSpeed(Ogre::Real const& moveSpeed) {
    _moveSpeed = moveSpeed;
}

/*
 * Bomb power-up
 */
void    Indie::APlayer::addABomb() {
    _nbBombs += 1;
}

void    Indie::APlayer::plantABomb(Ogre::SceneManager *sceneManager) {
    if (_bombList.size() < _nbBombs) {
        _bombList.push_back(std::unique_ptr<Indie::Bomb>(new Indie::Bomb(sceneManager, *this)));
    }
}

unsigned int    Indie::APlayer::getBombRange() const {
    return _bombRange;
}

void    Indie::APlayer::godMode() {
    _godMode = !_godMode;
}

bool    Indie::APlayer::isGodMode() const {
    return _godMode;
}

Indie::APlayer::~APlayer() {}