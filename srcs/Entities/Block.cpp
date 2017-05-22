//
// Created by wurmel on 21/05/17.
//

#include "Block.hh"

Indie::Block::Block(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) : Indie::AEntity(sceneManager, entityPos, "cube.mesh") {
    mEntity->setMaterialName("Bomberman/Block");
    //mSceneNode->setScale(Ogre::Vector3(0.3f, 0.3f, 0.3f));
}

bool Indie::Block::hittedByExplosion() const {
    return false;
}

Indie::Block::~Block() {

}
