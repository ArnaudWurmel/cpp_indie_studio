//
// Created by wurmel on 23/05/17.
//

#include <cstdlib>
#include "Particle.hh"

Indie::Particle::Particle(Indie::AEntity *entity) {
    mEntity = std::unique_ptr<Indie::AEntity>(entity);
    _power = (std::rand() % 500) + 300;
    _dirVector = Ogre::Vector3(std::rand() % 10, (std::rand() % 10) + 5, std::rand() % 10);
    _up = true;
    mEntity->setScale(Ogre::Vector3(0.1f, 0.1f, 0.1f));
}

bool Indie::Particle::updateParticle() {
    if (mEntity->getPosition().y >= _power)
        _up = false;
    if (_up) {
        mEntity->move(_dirVector);
        int rotate = static_cast<int>(mEntity->getPosition().y);
        mEntity->rotate(static_cast<AEntity::Direction>(rotate % 8));
    }
    else {
        mEntity->move(Ogre::Vector3(- _dirVector.x, - _dirVector.y, - _dirVector.z));
    }
    return mEntity->getPosition().y >= 0;
}

void    Indie::Particle::explode(Ogre::SceneManager *sceneManager) {
    mEntity->explode(sceneManager);
}

Indie::Particle::~Particle() {}
