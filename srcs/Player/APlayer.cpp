//
// Created by wurmel on 22/05/17.
//

#include <iostream>
#include "APlayer.hh"

Indie::APlayer::APlayer(const Indie::APlayer::PlayerType &pType,
                        Ogre::Vector3 const& entityPos,
                        Ogre::SceneManager *sceneManager,
                        const char *entityMesh) : AEntity(sceneManager, entityPos, entityMesh)
{
    mSceneNode->showBoundingBox(true);
}


bool Indie::APlayer::hittedByExplosion() const {
    return true;
}

void Indie::APlayer::rotate(const Indie::AEntity::Direction &dir) {
    std::vector<int>    orientation = {90, 270, 180, 0, 135, 45, 225, 315};

    if (dir < 8) {
        mSceneNode->setOrientation(Ogre::Quaternion(Ogre::Degree(orientation[dir]), Ogre::Vector3(0, 1, 0)));
    }
}

Indie::APlayer::~APlayer() {}
