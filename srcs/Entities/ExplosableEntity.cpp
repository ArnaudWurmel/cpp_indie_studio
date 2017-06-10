//
// Created by wurmel_a on 27/05/17.
//

#include "EntityManager.hh"
#include "ExplosableEntity.hh"

Indie::ExplosableEntity::ExplosableEntity() {

}

void    Indie::ExplosableEntity::createAllParticles(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& startPos, Ogre::Real const& nbEntity) {
    int i;

    if (_materialName.size() == 0)
        return ;
    i = 0;
    while (i < nbEntity) {
        Indie::AEntity  *entity = EntityManager::createEntity(EntityManager::EntityType::PARTICLE, sceneManager, startPos);

        if (entity != nullptr) {
            _particlesList.push_back(std::unique_ptr<Particle>(new Particle(entity, getAMaterialName())));
        }
        ++i;
    }
}

void    Indie::ExplosableEntity::addParticlesColor(std::string const& materialName) {
    _materialName.push_back(materialName);
}

bool    Indie::ExplosableEntity::updateParticles(Ogre::SceneManager *sceneManager) {
    std::vector<std::unique_ptr<Indie::Particle> >::iterator    it;

    it = _particlesList.begin();
    while (it != _particlesList.end()) {
        if (!(*it)->updateParticle()) {
            (*it)->explode(sceneManager);
            _particlesList.erase(it);
        }
        else
            ++it;
    }
    return _particlesList.size() > 0;
}

void    Indie::ExplosableEntity::removeAllParticles(Ogre::SceneManager *sceneManager) {
    std::vector<std::unique_ptr<Indie::Particle> >::iterator    it;

    it = _particlesList.begin();
    while (it != _particlesList.end()) {
        (*it)->removeEntity(sceneManager);
        ++it;
    }
    _particlesList.clear();
}

std::string const&  Indie::ExplosableEntity::getAMaterialName() const {
    return _materialName[std::rand() % _materialName.size()];
}

Indie::ExplosableEntity::~ExplosableEntity() {}