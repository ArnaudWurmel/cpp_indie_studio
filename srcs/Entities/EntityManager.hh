//
// Created by wurmel on 22/05/17.
//

#ifndef CPP_INDIE_STUDIO_ENTITYMANAGER_HH
#define CPP_INDIE_STUDIO_ENTITYMANAGER_HH

# include <vector>
#include <mutex>
# include "AEntity.hh"
# include "../MapParser/MapParser.hh"
# include "Block.hh"
# include "../Player/APlayer.hh"
# include "../PowerUp/PowerUp.hh"

namespace Indie {
    class EntityManager {
    public:
        enum    EntityType {
            BLOCK = 0,
            DYNAMIC_BLOCK,
            PARTICLE,
            EMPTY
        };
    public:
        EntityManager();
        ~EntityManager();

        static EntityManager*   getEntityManager(bool reset = false);
        static void addEntity(AEntity *);
        static std::vector<Indie::AEntity *>&   getEntityList();

        static void setMainPlayer(Indie::APlayer *);
        static Indie::APlayer *getMainPlayer();

        static void addPlayer(Indie::APlayer *);
        static std::vector<Indie::APlayer *>&   getPlayerList();

        static void addBomb(Indie::Bomb *);
        static std::vector<Indie::Bomb *>&  getBombList();

        static void addBoost(Indie::PowerUp *);
        static std::vector<Indie::PowerUp * >&   getPowerUpList();

        static void removeAllEntities(Ogre::SceneManager *);

        static void lockEntities();
        static void unlockEntities();


    public:
        static AEntity  *createEntity(EntityType const&, Ogre::SceneManager *, Ogre::Vector3 const&);

    public:
        static AEntity    *createBlock(Ogre::SceneManager *, Ogre::Vector3 const&);
        static AEntity    *createDynamicBlock(Ogre::SceneManager *, Ogre::Vector3 const&);
        static AEntity    *createDynamicParticle(Ogre::SceneManager *, Ogre::Vector3 const&);
        static AEntity    *createHuman(Ogre::SceneManager *, Ogre::Vector3 const&, std::string const&);
        static APlayer    *createEnemy(Ogre::SceneManager *, Ogre::Vector3 const&, std::string const&, bool AI = false);

    private:
        std::vector<Indie::AEntity* >   _entityList;
        std::vector<Indie::APlayer* >   _enemyList;
        std::vector<Indie::Bomb* >  _bombList;
        std::vector<Indie::PowerUp* >   _powerUpList;
        Indie::APlayer *_mainPlayer;
        std::unique_ptr<std::mutex> _lock;
    };
}


#endif //CPP_INDIE_STUDIO_ENTITYMANAGER_HH
