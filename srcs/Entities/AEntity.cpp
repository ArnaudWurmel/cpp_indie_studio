//
// Created by wurmel on 21/05/17.
//

#include "AEntity.hh"

Indie::AEntity::AEntity(Ogre::SceneManager *sceneManager, Ogre::Vector3 const &entityPos, const char *entityName) {
    mEntity = sceneManager->createEntity(entityName);
    mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(entityPos);
    mSceneNode->attachObject(mEntity);
}

Ogre::Vector3 const*    Indie::AEntity::getPosition() const {
    Ogre::AxisAlignedBox    aab = mEntity->getBoundingBox();

    return aab.getAllCorners();
}

Ogre::Vector3    Indie::AEntity::getSize() const {
    Ogre::AxisAlignedBox    aab = mEntity->getBoundingBox();

    return aab.getSize();
}

Indie::AEntity::~AEntity() {}