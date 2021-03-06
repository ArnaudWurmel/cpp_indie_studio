//
// Created by wurmel_a on 11/06/17.
//

#include "SpeedBoost.hh"

Indie::SpeedBoost::SpeedBoost(Ogre::SceneManager *sceneManager, Ogre::Vector3 const &entityPos, int id) : PowerUp(sceneManager, "SpeedUp.mesh", entityPos, id) {
    mTransformation = Ogre::Vector3(0.5f, 0.5f, 0.5f);
    addParticlesColor("Particles/Vert");
}

void    Indie::SpeedBoost::boostPlayer(APlayer& player, Ogre::SceneManager *sceneManager) {
    if (isAlive() && takePowerUp()) {
        player.setMoveSpeed(player.getMoveSpeed() + Config::getSpeedBoostIncrease());
        createAllParticles(sceneManager, getPosition(), 20.0);
        explode(sceneManager);
    }
}

Indie::SpeedBoost::~SpeedBoost() {}