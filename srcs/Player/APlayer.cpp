//
// Created by wurmel on 22/05/17.
//

#include <iostream>
#include "APlayer.hh"
#include "../Config/Config.hh"
#include "../DataManager/DataManager.h"
#include "../UserManager/User.hh"

Indie::APlayer::APlayer(const Indie::APlayer::PlayerType &pType,
                        Ogre::Vector3 const& entityPos,
                        Ogre::SceneManager *sceneManager,
                        const char *entityMesh, bool mainP) : AEntity(sceneManager, entityPos, entityMesh, !mainP)
{
    if (mainP)
        mSceneNode->showBoundingBox(true);
    _moveSpeed = Indie::Config::getMoveSpeed();
    _nbBombs = Indie::Config::getInitialNbBomb();
    _bombRange = Indie::Config::getBombRange();
    _godMode = false;
    _frameUpdate = Config::getNbTicks();
    _countFrame = 0;
    _updated = false;
    _pId = "";
    _mainP = mainP;
    _score = 0;
}


bool Indie::APlayer::hittedByExplosion() const {
    return isAlive();
}

bool    Indie::APlayer::updateFromLoop(Ogre::SceneManager *sceneManager) {
    std::vector<std::unique_ptr<Bomb> >::iterator   it;

    if (isWaiting()) {
        createEntity(sceneManager);
    }
    if (mBackgroundKill)
        explode(sceneManager);
    it = _bombList.begin();
    while (it != _bombList.end()) {
        if (!(*it)->updateFromLoop(sceneManager))
            _bombList.erase(it);
        else
            ++it;
    }
    if (isAlive() && _mainP) {
        if (60 / _frameUpdate == _countFrame) {
            _countFrame = 0;
        }
        ++_countFrame;
    }
    return isAlive() || updateParticles(sceneManager);
}

void    Indie::APlayer::explode(Ogre::SceneManager *sceneManager) {
    if (sceneManager && mSceneNode != NULL && mEntity != NULL) {
        createAllParticles(sceneManager, getPosition(), getSize().y * 200);
        Indie::AEntity::explode(sceneManager);
    }
    else
        mBackgroundKill = true;
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

void    Indie::APlayer::destroyEntity(Ogre::SceneManager *sceneManager) {
    removeAllParticles(sceneManager);
    Indie::AEntity::destroyEntity(sceneManager);
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
        DataManager *dataManager = DataManager::getSingloton();

        dataManager->addBomb(User::getUser()->getRoomId(), _pId, Bomb::getBombPosition(*this).z, Bomb::getBombPosition(*this).x, _bombRange);
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

unsigned int    Indie::APlayer::getScore() const
{
    return _score;
}

void    Indie::APlayer::setScore(unsigned int newScore) {
    _score = newScore;
}

Indie::APlayer::~APlayer() {}