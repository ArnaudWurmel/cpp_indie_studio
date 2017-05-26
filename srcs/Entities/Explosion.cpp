//
// Created by wurmel_a on 26/05/17.
//

#include "Explosion.hh"
#include "../Config/Config.hh"

Indie::Explosion::Explosion(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) : AEntity(sceneManager, entityPos, "cube.mesh") {
    mEntity->setMaterialName("Bomberman/Explosion");
//    mSceneNode->setScale(Ogre::Vector3(0.8f, 0.3f, 0.8f));
//    mTransformation = Ogre::Vector3(0.8f, 0.3f, 0.8f);
    _explosionTime = Config::getExplosionTime();
}

bool Indie::Explosion::hittedByExplosion() const {
    return false;
}

bool    Indie::Explosion::updateFromLoop(Ogre::SceneManager *sceneManager) {
    if (_explosionTime)
        _explosionTime -= 1;
    else
        return false;
    return true;
}

Indie::Explosion::~Explosion() {}