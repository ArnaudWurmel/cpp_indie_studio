//
// Created by wurmel on 21/05/17.
//

#include <iostream>
#include "AEntity.hh"

Indie::AEntity::AEntity(Ogre::SceneManager *sceneManager, Ogre::Vector3 const &entityPos, const char *entityName) {
    mEntity = sceneManager->createEntity(entityName);
    mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(entityPos);
    mSceneNode->attachObject(mEntity);
    mTransformation = Ogre::Vector3(1, 1, 1);
    mIsAlive = true;
}

Ogre::Vector3    Indie::AEntity::getPosition() const {
    return mSceneNode->getPosition();
}

Ogre::Vector3    Indie::AEntity::getSize() const {
    Ogre::AxisAlignedBox    aab = mEntity->getBoundingBox();

    return Ogre::Vector3(aab.getSize().x * mTransformation.x, aab.getSize().y * mTransformation.y, aab.getSize().z * mTransformation.z);
}

bool    Indie::AEntity::checkCollide(AEntity const& other) {
    if (!other.mIsAlive || !mIsAlive)
        return true;

    Ogre::AxisAlignedBox    myBox = mSceneNode->_getWorldAABB();
    Ogre::AxisAlignedBox    otherBox = other.mSceneNode->_getWorldAABB();

    if (myBox.intersects(otherBox)) {
        return false;
    }
    return !myBox.intersects(otherBox);
}

void Indie::AEntity::move(Ogre::Vector3 const& transform)
{
    mSceneNode->translate(transform);
    mSceneNode->_update(true, false);
}

void Indie::AEntity::rotate(const Indie::AEntity::Direction &dir) {
    static_cast<void>(dir);
}

void    Indie::AEntity::setScale(Ogre::Vector3 const& scale) {
    mSceneNode->setScale(scale);
}

void    Indie::AEntity::explode(Ogre::SceneManager *sceneManager) {
    mIsAlive = false;
    sceneManager->destroyEntity(mEntity);
    mEntity = NULL;
    sceneManager->destroySceneNode(mSceneNode);
    mSceneNode = NULL;
}

bool    Indie::AEntity::updateFromLoop(Ogre::SceneManager *sceneManager) {
    static_cast<void>(sceneManager);
    return true;
}

Indie::AEntity::~AEntity() {}
