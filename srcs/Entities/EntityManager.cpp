//
// Created by wurmel on 22/05/17.
//

#include <thread>
#include <map>
#include <sys/types.h>
#include <functional>
#include <exception>
#include <iostream>
#include "EntityManager.hh"
#include "../Entities/BreakableBlock.hh"
#include "../Player/HumanPlayer.hh"
#include "../Player/AI.hh"
#include "../Exception/Exception.hh"

Indie::EntityManager    *Indie::EntityManager::getEntityManager(bool reset) {
    static Indie::EntityManager *entityManager = NULL;

    if (reset && entityManager) {
        entityManager->_lock->lock();
        delete entityManager;
        entityManager = NULL;
    }
    else if (entityManager == NULL)
        entityManager = new EntityManager();
    return (entityManager);
}

void    Indie::EntityManager::addEntity(AEntity *entity) {
    Indie::EntityManager    *entityManager = getEntityManager();

    if (entityManager) {
        entityManager->_entityList.push_back(entity);
    }
}

std::vector<Indie::AEntity *>& Indie::EntityManager::getEntityList() {
    Indie::EntityManager    *entityManager = getEntityManager();

    if (entityManager) {
        return (entityManager->_entityList);
    }
    throw EntityManagerException();
}

void    Indie::EntityManager::setMainPlayer(Indie::APlayer *player) {
    Indie::EntityManager    *entityManager = getEntityManager();

    if (entityManager)
        entityManager->_mainPlayer = player;
}

Indie::APlayer    *Indie::EntityManager::getMainPlayer() {
    Indie::EntityManager    *entityManager = getEntityManager();

    if (entityManager)
        return (entityManager->_mainPlayer);
    throw EntityManagerException();
}

void    Indie::EntityManager::addPlayer(Indie::APlayer *player) {
    Indie::EntityManager    *entityManager = getEntityManager();

    if (entityManager) {
        entityManager->_enemyList.push_back(player);
        return ;
    }
    throw EntityManagerException();}

std::vector<Indie::APlayer *>&  Indie::EntityManager::getPlayerList() {
    Indie::EntityManager    *entityManager = getEntityManager();

    if (entityManager)
        return entityManager->_enemyList;
    throw EntityManagerException();}

void    Indie::EntityManager::addBomb(Indie::Bomb *bomb) {
    Indie::EntityManager    *entityManager = getEntityManager();

    if (entityManager) {
        entityManager->_bombList.push_back(bomb);
        return ;
    }
    throw EntityManagerException();}

std::vector<Indie::Bomb *>& Indie::EntityManager::getBombList() {
    Indie::EntityManager    *entityManager = getEntityManager();

    if (entityManager) {
        return entityManager->_bombList;
    }
    throw EntityManagerException();
}

void    Indie::EntityManager::removeAllEntities(Ogre::SceneManager *sceneManager) {
    Indie::EntityManager    *entityManager = getEntityManager();

    std::vector<AEntity *>::iterator    it = entityManager->_entityList.begin();

    while (it != entityManager->_entityList.end()) {
        (*it)->destroyEntity(sceneManager);
        delete (*it);
        ++it;
    }
    entityManager->_entityList.clear();
    std::vector<APlayer *>::iterator    itP = entityManager->_enemyList.begin();
    while (itP != entityManager->_enemyList.end()) {
        (*itP)->destroyEntity(sceneManager);
        delete (*itP);
        ++itP;
    }
    entityManager->_enemyList.clear();
    std::vector<Bomb *>::iterator   itB = entityManager->_bombList.begin();

    while (itB != entityManager->_bombList.end()) {
        (*itB)->destroyEntity(sceneManager);
        delete (*itB);
        ++itB;
    }
    entityManager->_bombList.clear();
    std::vector<PowerUp *>::iterator    itPU = entityManager->_powerUpList.begin();

    while (itPU != entityManager->_powerUpList.end()) {
        (*itPU)->destroyEntity(sceneManager);
        delete *itPU;
        ++itPU;
    }
    entityManager->_mainPlayer->destroyEntity(sceneManager);
    delete entityManager->_mainPlayer;
    entityManager->_mainPlayer = NULL;
}

void    Indie::EntityManager::addBoost(Indie::PowerUp *powerUp) {
    Indie::EntityManager    *entityManager = getEntityManager();

    entityManager->_powerUpList.push_back(powerUp);
}

std::vector<Indie::PowerUp* >&    Indie::EntityManager::getPowerUpList() {
    return Indie::EntityManager::getEntityManager()->_powerUpList;
}

void    Indie::EntityManager::lockEntities() {
    Indie::EntityManager    *entityManager = getEntityManager();

    entityManager->_lock->lock();
}

void    Indie::EntityManager::unlockEntities() {
    Indie::EntityManager    *entityManager = getEntityManager();

    entityManager->_lock->unlock();
}

Indie::EntityManager::EntityManager() {
    _lock = new std::mutex();
}

Indie::EntityManager::~EntityManager() {
    delete _lock;
    _lock = NULL;
    _entityList.clear();
}

Indie::AEntity *Indie::EntityManager::createEntity(Indie::EntityManager::EntityType const& tileType, Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    std::map<Indie::EntityManager::EntityType, Indie::AEntity *(*)(Ogre::SceneManager *, Ogre::Vector3 const&)>    functionPtr;

    functionPtr.insert(std::make_pair(EntityType::BLOCK, &Indie::EntityManager::createBlock));
    functionPtr.insert(std::make_pair(EntityType::DYNAMIC_BLOCK, &Indie::EntityManager::createDynamicBlock));
    functionPtr.insert(std::make_pair(EntityManager::PARTICLE, &Indie::EntityManager::createDynamicParticle));
    if (functionPtr.find(tileType) != functionPtr.end()) {
        AEntity *entity = (*functionPtr[tileType])(sceneManager, entityPos);
        return entity;
    }
    return nullptr;
}

Indie::AEntity *Indie::EntityManager::createBlock(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    AEntity *entity = new Indie::Block(sceneManager, entityPos);

    EntityManager::lockEntities();
    EntityManager::addEntity(entity);
    EntityManager::unlockEntities();
    return entity;
}

Indie::AEntity  *Indie::EntityManager::createDynamicBlock(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    AEntity *entity = new Indie::BreakableBlock(sceneManager, entityPos);

    EntityManager::lockEntities();
    EntityManager::addEntity(entity);
    EntityManager::unlockEntities();
    return (entity);
}

Indie::AEntity  *Indie::EntityManager::createHuman(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos, std::string const& pName) {

    Indie::HumanPlayer  *player = new Indie::HumanPlayer(entityPos, sceneManager, pName, true);

    EntityManager::lockEntities();
    setMainPlayer(player);
    EntityManager::unlockEntities();
    return player;
}

Indie::AEntity  *Indie::EntityManager::createDynamicParticle(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos) {
    return new Indie::Block(sceneManager, entityPos);
}

Indie::APlayer  *Indie::EntityManager::createEnemy(Ogre::SceneManager *sceneManager, Ogre::Vector3 const& entityPos, std::string const& pId, bool AI) {
    Indie::APlayer  *player;
    if (!AI)
        player = new Indie::HumanPlayer(entityPos, sceneManager, pId);
    else
        player = new Indie::AI(entityPos, sceneManager, pId);

    addPlayer(player);
    return player;
}