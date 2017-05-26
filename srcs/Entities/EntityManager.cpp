//
// Created by wurmel on 22/05/17.
//

#include <map>
#include <functional>
#include <exception>
#include "EntityManager.hh"
#include "../Entities/BreakableBlock.hh"
#include "../Player/HumanPlayer.hh"

Indie::EntityManager    *Indie::EntityManager::getEntityManager(bool reset) {
    static Indie::EntityManager *entityManager = NULL;

    if (reset && entityManager) {
        delete entityManager;
        entityManager = NULL;
    }
    else if (entityManager == NULL)
        entityManager = new EntityManager();
    return (entityManager);
}

void    Indie::EntityManager::addExplosableEntity(AEntity *entity) {
    Indie::EntityManager    *entityManager = getEntityManager();

    if (entityManager)
        entityManager->_entityList.push_back(std::shared_ptr<AEntity>(entity));
}

std::vector<std::shared_ptr<Indie::AEntity> >& Indie::EntityManager::getEntityList() {
    Indie::EntityManager    *entityManager = getEntityManager();

    if (entityManager)
        return (entityManager->_entityList);
    throw std::exception();
}

Indie::EntityManager::EntityManager() {

}

Indie::EntityManager::~EntityManager() {
    _entityList.clear();
}

Indie::AEntity *Indie::EntityManager::createEntity(Indie::MapParser::TileType const& tileType, Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    std::map<MapParser::TileType, Indie::AEntity *(*)(Ogre::SceneManager *, Ogre::Vector3 const&)>    functionPtr;

    functionPtr.insert(std::make_pair(MapParser::TileType::STATIC_BLOCK, &Indie::EntityManager::createBlock));
    functionPtr.insert(std::make_pair(MapParser::TileType::DYNAMIC_BLOCK, &Indie::EntityManager::createDynamicBlock));
    functionPtr.insert(std::make_pair(MapParser::TileType::PLAYER, &Indie::EntityManager::createHuman));
    functionPtr.insert(std::make_pair(MapParser::TileType::DYNAMIC_PARTICLE, &Indie::EntityManager::createDynamicParticle));
    if (functionPtr.find(tileType) != functionPtr.end()) {
        return (*functionPtr[tileType])(sceneManager, entityPos);
    }
    return nullptr;
}

Indie::AEntity *Indie::EntityManager::createBlock(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    return new Indie::Block(sceneManager, entityPos);
}

Indie::AEntity  *Indie::EntityManager::createDynamicBlock(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    AEntity *entity = new Indie::BreakableBlock(sceneManager, entityPos);

    EntityManager::addExplosableEntity(entity);
    return (entity);
}

Indie::AEntity  *Indie::EntityManager::createHuman(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    return new Indie::HumanPlayer(entityPos, sceneManager);
}

Indie::AEntity  *Indie::EntityManager::createDynamicParticle(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    return new Indie::BreakableBlock(sceneManager, entityPos, AEntity::BlockType::PARTICLE);
}