//
// Created by wurmel on 22/05/17.
//

#include "BreakableBlock.hh"

Indie::BreakableBlock::BreakableBlock(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) : Indie::AEntity(sceneManager, entityPos, "cube.mesh") {
    mEntity->setMaterialName("Bomberman/BreakableBlock");
}

bool Indie::BreakableBlock::hittedByExplosion() const {
    return true;
}

Indie::BreakableBlock::~BreakableBlock() {}