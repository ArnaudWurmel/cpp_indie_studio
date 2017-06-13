//
// Created by wurmel_a on 11/06/17.
//

#include "ExtendBoost.hh"

Indie::ExtendBoost::ExtendBoost(Ogre::SceneManager *sceneManager, Ogre::Vector3 const &entityPos, int id) : PowerUp(sceneManager, "extend.mesh", entityPos, id) {
    mTransformation = Ogre::Vector3(5.0f, 5.0f, 5.0f);
    addParticlesColor("Particles/Vert");
}

void    Indie::ExtendBoost::boostPlayer(APlayer& player, Ogre::SceneManager *sceneManager) {
    if (isAlive() && takePowerUp()) {
        player.setBombRange(player.getBombRange() + 1);
        createAllParticles(sceneManager, getPosition(), 10.0);
        explode(sceneManager);
    }
}

Indie::ExtendBoost::~ExtendBoost() {}