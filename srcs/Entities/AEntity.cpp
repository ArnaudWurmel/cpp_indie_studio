//
// Created by wurmel on 21/05/17.
//

#include "AEntity.hh"

Indie::AEntity::AEntity(Ogre::SceneManager *sceneManager, Ogre::Vector3 const &entityPos, const char *entityName) {
    mEntity = sceneManager->createEntity(entityName);
    mSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(entityPos);
    mSceneNode->attachObject(mEntity);
    mTransformation = Ogre::Vector3(1, 1, 1);
}

Ogre::Vector3    Indie::AEntity::getPosition() const {
    return mSceneNode->getPosition();
}

Ogre::Vector3    Indie::AEntity::getSize() const {
    Ogre::AxisAlignedBox    aab = mEntity->getBoundingBox();

    return Ogre::Vector3(aab.getSize().x * mTransformation.x, aab.getSize().y * mTransformation.y, aab.getSize().z * mTransformation.z);
}

bool Indie::AEntity::collide(const Indie::AEntity& other) const {

    return false;
}

void Indie::AEntity::move(Ogre::Vector3 const& transform)
{
    mSceneNode->translate(transform);
}

void Indie::AEntity::rotate(const Indie::AEntity::Direction &dir) {
    static_cast<void>(dir);
}

Indie::AEntity::~AEntity() {}
