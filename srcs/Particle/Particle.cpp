//
// Created by wurmel on 23/05/17.
//

#include <iostream>
#include <cstdlib>
#include "Particle.hh"
#include "../Config/Config.hh"

Indie::Particle::Particle(Indie::AEntity *entity, std::string const& materialName) {
    mEntity = std::unique_ptr<Indie::AEntity>(entity);
    mEntity->setMaterialName(materialName);
    t = 0;
    _dirVector = Ogre::Vector3(-20 + std::rand() % 40, 20 + (std::rand() % 20), -20 + std::rand() % 40);
    mEntity->setScale(Ogre::Vector3(0.1f, 0.1f, 0.1f));
}

bool Indie::Particle::updateParticle() {
    Ogre::Real y;

    y = -(1.0f/16.0f) * Indie::Config::getGravity() * (t * t);
    mEntity->move(Ogre::Vector3(_dirVector.x, y + _dirVector.y, _dirVector.z));
    t += 1;
    mEntity->rotate(static_cast<AEntity::Direction >(t % 8));
    return mEntity->getPosition().y >= 0;
}

void    Indie::Particle::explode(Ogre::SceneManager *sceneManager) {
    mEntity->explode(sceneManager);
}

Indie::Particle::~Particle() {}
