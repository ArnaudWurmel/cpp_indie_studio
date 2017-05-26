//
// Created by wurmel on 24/05/17.
//

#include "Config.hh"

Ogre::Real Indie::Config::getGravity() {
    return Ogre::Real(4);
}

Ogre::Real Indie::Config::getMoveSpeed() {
    return 5.0;
}

unsigned int Indie::Config::getInitialNbBomb() {
    return 1;
}

unsigned int Indie::Config::getExplodeTime() {
    return 180;
}

unsigned int    Indie::Config::getBombRange() {
    return 2;
}

unsigned int    Indie::Config::getExplosionTime() {
    return 30;
}