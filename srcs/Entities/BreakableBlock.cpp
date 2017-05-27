//
// Created by wurmel on 22/05/17.
//

#include <cstdlib>
#include <iostream>
#include "BreakableBlock.hh"
#include "EntityManager.hh"

Indie::BreakableBlock::BreakableBlock(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos, BlockType const& blockType) : Indie::AEntity(sceneManager, entityPos, "cube.mesh"), Indie::ExplosableEntity() {
    mEntity->setMaterialName("Bomberman/BreakableBlock");
    _blockType = blockType;
    addParticlesColor("Particles/Grey");
    addParticlesColor("Particles/Orange");
}

bool Indie::BreakableBlock::hittedByExplosion() const {
    return mSceneNode != NULL && _blockType == NORMAL;
}

void Indie::BreakableBlock::explode(Ogre::SceneManager *sceneManager) {
    if (mEntity != NULL && mSceneNode != NULL)
    {
        createAllParticles(sceneManager, mSceneNode->getPosition(), getSize().y);
        Indie::AEntity::explode(sceneManager);
    }
}

bool    Indie::BreakableBlock::updateFromLoop(Ogre::SceneManager *sceneManager) {
    return mEntity != NULL || updateParticles(sceneManager);
}

Indie::BreakableBlock::~BreakableBlock() {}