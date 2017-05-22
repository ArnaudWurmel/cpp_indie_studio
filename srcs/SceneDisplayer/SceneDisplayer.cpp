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
    Block   block(mSceneManager, Ogre::Vector3(0, 0, 0));
    std::cout << block.getPosition().x << std::endl;
    std::cout << block.getPosition().y << std::endl;
    std::cout << block.getPosition().z << std::endl;
    std::cout << block.getSize().x << std::endl;
    std::cout << block.getSize().y << std::endl;
    std::cout << block.getSize().z << std::endl;

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