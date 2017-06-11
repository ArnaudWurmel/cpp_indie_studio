//
// Created by wurmel_a on 11/06/17.
//

#include "SpeedBoost.hh"

Indie::SpeedBoost::SpeedBoost(Ogre::SceneManager *sceneManager, Ogre::Vector3 const &entityPos, int id) : PowerUp(sceneManager, "bomb.mesh", entityPos, id) {
    mTransformation = Ogre::Vector3(5.0f, 5.0f, 5.0f);
//    addParticlesColor("Particles/Blue");
  //  addParticlesColor("Particles/Grey");
}

void    Indie::SpeedBoost::boostPlayer(APlayer& player) const {
    player.setMoveSpeed(player.getMoveSpeed() + Ogre::Real(5.0));
}

Indie::SpeedBoost::~SpeedBoost() {}