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

    return Ogre::Vector3(aab.getSize().x, aab.getSize().y, aab.getSize().z);
}

bool    Indie::AEntity::checkCollide(AEntity const& other) {
    if (!other.mIsAlive || !mIsAlive)
        return true;

    Ogre::AxisAlignedBox    myBox = mSceneNode->_getWorldAABB();
    Ogre::AxisAlignedBox    otherBox = other.mSceneNode->_getWorldAABB();

    if (myBox.intersects(otherBox) || (other.getPosition().x == getPosition().x && other.getPosition().z == getPosition().z)) {
        return false;
    }
    if (getPosition().x >= other.getPosition().x - (other.getSize().x / 2) && getPosition().x <= other.getPosition().x + (other.getSize().x / 2) && getPosition().z >= other.getPosition().z - (other.getSize().z / 2) && getPosition().z <= other.getPosition().z + (other.getSize().z / 2))
        return false;
    return !myBox.intersects(otherBox);
}

void Indie::AEntity::move(Ogre::Vector3 const& transform)
{
    if (mIsAlive) {
        mSceneNode->translate(transform);
        mSceneNode->_update(true, false);
    }
}

void Indie::AEntity::rotate(const Indie::AEntity::Direction &dir) {
    int orientation[8] = {90, 270, 180, 0, 135, 45, 225, 315};

    if (!mIsAlive)
        return ;
    if (dir < 8) {
        mSceneNode->setOrientation(Ogre::Quaternion(Ogre::Degree(orientation[dir]), Ogre::Vector3(0, 1, 0)));
    }
}

void    Indie::AEntity::setScale(Ogre::Vector3 const& scale) {
    mSceneNode->setScale(scale);
}

void    Indie::AEntity::explode(Ogre::SceneManager *sceneManager) {
    if (mIsAlive) {
        mIsAlive = false;
        sceneManager->destroyEntity(mEntity);
        mEntity = NULL;
        sceneManager->destroySceneNode(mSceneNode);
        mSceneNode = NULL;
    }
}

bool    Indie::AEntity::updateFromLoop(Ogre::SceneManager *sceneManager) {
    static_cast<void>(sceneManager);
    return true;
}

bool Indie::AEntity::isAlive() const {
    return mIsAlive;
}

void    Indie::AEntity::setMaterialName(std::string const& materialName) {
    mEntity->setMaterialName(materialName);
}

Indie::AEntity::~AEntity() {}