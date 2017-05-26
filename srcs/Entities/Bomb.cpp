//
// Created by wurmel_a on 26/05/17.
//

#include <iostream>
#include "Bomb.h"
#include "../Player/APlayer.hh"

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

Indie::Bomb::Bomb(Ogre::SceneManager *sceneManager, const Indie::APlayer& delegate) : AEntity(sceneManager, getBombPosition(delegate), "bomb.mesh") {
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
