//
// Created by wurmel on 24/05/17.
//

#include "Config.hh"

Ogre::Real Indie::Config::getGravity() {
    return Ogre::Real(2);
}

Ogre::Real Indie::Config::getMoveSpeed() {
    return 5.0;
}

unsigned int Indie::Config::getInitialNbBomb() {
    return 1;
}

unsigned int Indie::Config::getExplodeTime() {
    return 60;
}

unsigned int    Indie::Config::getBombRange() {
    return 2;
}

unsigned int    Indie::Config::getExplosionTime() {
    return 30;
}

unsigned int    Indie::Config::getNbTicks() {
    return 20;
}

std::string     Indie::Config::getGameName() {
    return "Tronberman";
}

Ogre::Real  Indie::Config::getSpeedBoostIncrease() {
    return Ogre::Real(0.5);
}

unsigned int    Indie::Config::getWinLoseAnimationTime() {
    return 180;
}