//
// Created by wurmel on 22/05/17.
//

#include "APlayer.hh"

Indie::APlayer::APlayer(const Indie::APlayer::PlayerType &pType,
                        Ogre::Vector3 const& entityPos,
                        Ogre::SceneManager *sceneManager,
                        const char *entityMesh) : AEntity(sceneManager, entityPos, entityMesh)
{

}


bool Indie::APlayer::hittedByExplosion() const {
    return true;
}

Indie::APlayer::~APlayer() {}
