//
// Created by wurmel on 13/05/17.
//

#include <iostream>
#include "SceneDisplayer.hh"
#include "../Entities/Block.hh"

Indie::SceneDisplayer::SceneDisplayer(Ogre::SceneManager *sceneManager) {
    mSceneManager = sceneManager;
}

void Indie::SceneDisplayer::initScene() {
    this->createGround();
    std::cout << mSceneManager->getRootSceneNode()->_getWorldAABB().getSize().x << std::endl;
    Block   block(mSceneManager, Ogre::Vector3(0, 0, 0));
    std::cout << mSceneManager->getRootSceneNode()->_getWorldAABB().getSize().x << std::endl;
}

void Indie::SceneDisplayer::createGround() {
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
            "ground",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            plane,
            1500, 1500, 20, 20,
            true,
            1, 5, 5,
            Ogre::Vector3::UNIT_Z
    );
    Ogre::Entity    *groundEntity = mSceneManager->createEntity("ground");
    mSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("Bomberman/Ground");
}

Indie::SceneDisplayer::~SceneDisplayer() {}