//
// Created by wurmel on 22/05/17.
//

#include <iostream>
#include "APlayer.hh"
#include "../Config/Config.hh"

Indie::APlayer::APlayer(const Indie::APlayer::PlayerType &pType,
                        Ogre::Vector3 const& entityPos,
                        Ogre::SceneManager *sceneManager,
                        const char *entityMesh) : AEntity(sceneManager, entityPos, entityMesh)
{
    mSceneNode->showBoundingBox(true);
    _moveSpeed = Indie::Config::getMoveSpeed();
    _nbBombs = Indie::Config::getInitialNbBomb();
    _godMode = false;
}


bool Indie::APlayer::hittedByExplosion() const {
    return true;
}

void Indie::APlayer::rotate(const Indie::AEntity::Direction &dir) {
    int    orientation[8] = {90, 270, 180, 0, 135, 45, 225, 315};

    if (dir < 8) {
        mSceneNode->setOrientation(Ogre::Quaternion(Ogre::Degree(orientation[dir]), Ogre::Vector3(0, 1, 0)));
    }
}

bool    Indie::APlayer::updateFromLoop(Ogre::SceneManager *sceneManager) {
    std::vector<std::unique_ptr<Bomb> >::iterator   it;

    it = _bombList.begin();
    while (it != _bombList.end()) {
        if (!(*it)->updateFromLoop(sceneManager)) {
            (*it)->explode(sceneManager);
            _bombList.erase(it);
        }
        else {
            ++it;
        }
    }
    return true;
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

void    Indie::APlayer::godMode() {
    _godMode = !_godMode;
}

bool    Indie::APlayer::isGodMode() const {
    return _godMode;
}

Indie::APlayer::~APlayer() {}
