//
// Created by wurmel on 13/05/17.
//

#include <iostream>
#include "SceneDisplayer.hh"
#include "../Entities/EntityManager.hh"
#include "../Entities/Block.hh"

Indie::SceneDisplayer::SceneDisplayer(Ogre::SceneManager *sceneManager) {
    mSceneManager = sceneManager;
}

void Indie::SceneDisplayer::initScene() {
    MapParser   mapParser("resources/maps/level0");

    this->createGround();
    _map = mapParser.getMap();
    if (_map.size() > 0) {
        this->createMap();
    }
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

void Indie::SceneDisplayer::createMap() {
    std::vector<std::vector<MapParser::TileType> >::iterator    it;
    int    i;
    int    j;

    it = _map.begin();
    i = 0;
    while (it != _map.end()) {
        std::vector<MapParser::TileType>::iterator  it_line;
        j = 0;
        it_line = (*it).begin();
        while (it_line != (*it).end()) {
            Indie::AEntity  *entity = EntityManager::createEntity(*it_line, mSceneManager, Ogre::Vector3(-30 * i, 15, -30 * j));

            if (entity != nullptr) {
                _entityList.push_back(std::unique_ptr<AEntity>(entity));
            }
            else
                std::cout << "Null ptr" << std::endl;
            ++it_line;
            ++j;
        }
        ++i;
        ++it;
    }
}

Indie::SceneDisplayer::~SceneDisplayer() {}