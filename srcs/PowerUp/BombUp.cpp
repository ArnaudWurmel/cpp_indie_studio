//
// Created by wurmel_a on 12/06/17.
//

#include "BombUp.hh"

Indie::BombUp::BombUp(Ogre::SceneManager *sceneManager, Ogre::Vector3 const &entityPos, int id) : PowerUp(sceneManager, "BombUp.mesh", entityPos, id) {
    mTransformation = Ogre::Vector3(1.5f, 1.5f, 1.5f);
    addParticlesColor("Particles/Vert");
}

void    Indie::BombUp::boostPlayer(APlayer& player, Ogre::SceneManager *sceneManager) {
    if (isAlive() && takePowerUp()) {
        player.addABomb();
        createAllParticles(sceneManager, getPosition(), 10.0);
        explode(sceneManager);
    }
}

Indie::BombUp::~BombUp() {}