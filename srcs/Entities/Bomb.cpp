//
// Created by wurmel_a on 26/05/17.
//

#include <iostream>
#include "Bomb.h"
#include "../Player/APlayer.hh"

Indie::Bomb::Bomb(Ogre::SceneManager *sceneManager, const Indie::APlayer& delegate) : AEntity(sceneManager, Ogre::Vector3(delegate.getPosition().x, delegate.getPosition().y + 10, delegate.getPosition().z), "bomb.mesh") {
    mSceneNode->setScale(Ogre::Vector3(5.0f, 5.0f, 5.0f));
    mTransformation = Ogre::Vector3(10.0f, 10.0f, 10.0f);
    _explodeTime = Config::getExplodeTime();
}

bool    Indie::Bomb::hittedByExplosion() const {
    return true;
}

bool    Indie::Bomb::updateFromLoop(Ogre::SceneManager *sceneManager) {
    static_cast<void>(sceneManager);
    if (!_explodeTime)
        return false;
    _explodeTime -= 1;
    return true;
}

Indie::Bomb::~Bomb() {}
