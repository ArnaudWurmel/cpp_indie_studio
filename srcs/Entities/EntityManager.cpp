//
// Created by wurmel on 22/05/17.
//

#include <map>
#include <functional>
#include "EntityManager.hh"
#include "../Entities/BreakableBlock.hh"
#include "../Player/HumanPlayer.hh"

Indie::AEntity *Indie::EntityManager::createEntity(Indie::MapParser::TileType const& tileType, Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    std::map<MapParser::TileType, Indie::AEntity *(*)(Ogre::SceneManager *, Ogre::Vector3 const&)>    functionPtr;

    functionPtr.insert(std::make_pair(MapParser::TileType::STATIC_BLOCK, &Indie::EntityManager::createBlock));
    functionPtr.insert(std::make_pair(MapParser::TileType::DYNAMIC_BLOCK, &Indie::EntityManager::createDynamicBlock));
    functionPtr.insert(std::make_pair(MapParser::TileType::PLAYER, &Indie::EntityManager::createHuman));
    if (functionPtr.find(tileType) != functionPtr.end()) {
        return (*functionPtr[tileType])(sceneManager, entityPos);
    }
    return nullptr;
}

Indie::AEntity *Indie::EntityManager::createBlock(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    return new Indie::Block(sceneManager, entityPos);
}

Indie::AEntity  *Indie::EntityManager::createDynamicBlock(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    return new Indie::BreakableBlock(sceneManager, entityPos);
}

Indie::AEntity  *Indie::EntityManager::createHuman(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    return new Indie::HumanPlayer(entityPos, sceneManager);
}