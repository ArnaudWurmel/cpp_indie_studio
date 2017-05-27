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

void    Indie::EntityManager::addEntity(AEntity *entity) {
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

void    Indie::EntityManager::setMainPlayer(Indie::APlayer *player) {
    Indie::EntityManager    *entityManager = getEntityManager();

    if (entityManager)
        entityManager->_mainPlayer = std::unique_ptr<Indie::APlayer>(player);
}

std::unique_ptr<Indie::APlayer>&    Indie::EntityManager::getMainPlayer() {
    Indie::EntityManager    *entityManager = getEntityManager();

    if (entityManager)
        return (entityManager->_mainPlayer);
    throw std::exception();
}

Indie::EntityManager::EntityManager() {}

Indie::EntityManager::~EntityManager() {
    _entityList.clear();
}

Indie::AEntity *Indie::EntityManager::createEntity(Indie::EntityManager::EntityType const& tileType, Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    std::map<Indie::EntityManager::EntityType, Indie::AEntity *(*)(Ogre::SceneManager *, Ogre::Vector3 const&)>    functionPtr;

    functionPtr.insert(std::make_pair(EntityType::BLOCK, &Indie::EntityManager::createBlock));
    functionPtr.insert(std::make_pair(EntityType::DYNAMIC_BLOCK, &Indie::EntityManager::createDynamicBlock));
    functionPtr.insert(std::make_pair(EntityType::HUMAN, &Indie::EntityManager::createHuman));
    functionPtr.insert(std::make_pair(EntityManager::PARTICLE, &Indie::EntityManager::createDynamicParticle));
    if (functionPtr.find(tileType) != functionPtr.end()) {
        return (*functionPtr[tileType])(sceneManager, entityPos);
    }
    return nullptr;
}

Indie::AEntity *Indie::EntityManager::createBlock(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    AEntity *entity = new Indie::Block(sceneManager, entityPos);

    EntityManager::addEntity(entity);
    return entity;
}

Indie::AEntity  *Indie::EntityManager::createDynamicBlock(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    AEntity *entity = new Indie::BreakableBlock(sceneManager, entityPos);

    EntityManager::addEntity(entity);
    return (entity);
}

Indie::AEntity  *Indie::EntityManager::createHuman(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    Indie::HumanPlayer  *player = new Indie::HumanPlayer(entityPos, sceneManager);

    setMainPlayer(player);
    return player;
}

Indie::AEntity  *Indie::EntityManager::createDynamicParticle(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    return new Indie::Block(sceneManager, entityPos);
}