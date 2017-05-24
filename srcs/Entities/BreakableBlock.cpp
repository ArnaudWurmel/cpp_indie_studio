//
// Created by wurmel on 22/05/17.
//

#include <cstdlib>
#include <iostream>
#include "BreakableBlock.hh"
#include "EntityManager.hh"

Indie::BreakableBlock::BreakableBlock(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos, BlockType const& blockType) : Indie::AEntity(sceneManager, entityPos, "cube.mesh") {
    mEntity->setMaterialName("Bomberman/BreakableBlock");
    _blockType = blockType;
}

bool Indie::BreakableBlock::hittedByExplosion() const {
    if (mSceneNode != NULL && mSceneNode != NULL && _blockType == NORMAL && _particleList.size() == 0)
        return true;
    return false;
}

void Indie::BreakableBlock::explode(Ogre::SceneManager *sceneManager) {
    if (_blockType == NORMAL) {
        int nb_entity;
        int i;
        nb_entity = (rand() % 100) + 100;
        i = 0;
        while (i < nb_entity) {
            Indie::AEntity  *entity = EntityManager::createEntity(MapParser::DYNAMIC_PARTICLE, sceneManager, mSceneNode->getPosition());

            if (entity != nullptr) {
                _particleList.push_back(std::unique_ptr<Particle>(new Particle(entity)));
            }
            ++i;
        }
    }
    if (mEntity != NULL && mSceneNode != NULL)
        Indie::AEntity::explode(sceneManager);
}

bool    Indie::BreakableBlock::updateFromLoop(Ogre::SceneManager *sceneManager) {
    std::vector<std::unique_ptr<Indie::Particle> >::iterator    it;

    it = _particleList.begin();
    while (it != _particleList.end()) {
        if (!(*it)->updateParticle()) {
            (*it)->explode(sceneManager);
            _particleList.erase(it);
        }
        else
            ++it;
    }
    return mEntity != NULL || _particleList.size() > 0;
}

Indie::BreakableBlock::~BreakableBlock() {}