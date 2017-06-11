//
// Created by wurmel_a on 11/06/17.
//

#include "PowerUp.hh"

Indie::PowerUp::PowerUp(Ogre::SceneManager *sceneManager, std::string const& entityName, Ogre::Vector3 const& entityPos, int id) : AEntity(sceneManager, entityPos, entityName.c_str(), true) {
    _id = id;
}

bool    Indie::PowerUp::updateFromLoop(Ogre::SceneManager *sceneManager) {
    if (isWaiting())
        createEntity(sceneManager);
}

bool    Indie::PowerUp::hittedByExplosion() const {
    return false;
}

int Indie::PowerUp::getID() const {
    return _id;
}

Indie::PowerUp::~PowerUp() {}