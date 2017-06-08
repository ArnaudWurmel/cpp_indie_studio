//
// Created by wurmel on 22/05/17.
//

#ifndef CPP_INDIE_STUDIO_ENTITYMANAGER_HH
#define CPP_INDIE_STUDIO_ENTITYMANAGER_HH

# include <vector>
# include "AEntity.hh"
# include "../MapParser/MapParser.hh"
# include "Block.hh"
# include "../Player/APlayer.hh"

namespace Indie {
    class EntityManager {
    public:
        enum    EntityType {
            BLOCK = 0,
            DYNAMIC_BLOCK,
            HUMAN,
            ENEMY,
            PARTICLE,
            EMPTY
        };
    public:
        EntityManager();
        ~EntityManager();

        static EntityManager*   getEntityManager(bool reset = false);
        static void addEntity(AEntity *);
        static std::vector<std::shared_ptr<Indie::AEntity> >&   getEntityList();

        static void setMainPlayer(Indie::APlayer *);
        static std::unique_ptr<Indie::APlayer>& getMainPlayer();

        static void addPlayer(Indie::APlayer *);
        static std::vector<std::unique_ptr<Indie::APlayer> >&   getPlayerList();

        static void addBomb(Indie::Bomb *);
        static std::vector<std::unique_ptr<Indie::Bomb> >&  getBombList();

        static void removeAllEntities(Ogre::SceneManager *);


    public:
        static AEntity  *createEntity(EntityType const&, Ogre::SceneManager *, Ogre::Vector3 const&);

    public:
        static AEntity    *createBlock(Ogre::SceneManager *, Ogre::Vector3 const&);
        static AEntity    *createDynamicBlock(Ogre::SceneManager *, Ogre::Vector3 const&);
        static AEntity    *createDynamicParticle(Ogre::SceneManager *, Ogre::Vector3 const&);
        static AEntity    *createHuman(Ogre::SceneManager *, Ogre::Vector3 const&, std::string const&);
        static APlayer    *createEnemy(Ogre::SceneManager *, Ogre::Vector3 const&, std::string const&);

    private:
        std::vector<std::shared_ptr<Indie::AEntity> >   _entityList;
        std::vector<std::unique_ptr<Indie::APlayer> >   _enemyList;
        std::vector<std::unique_ptr<Indie::Bomb> >  _bombList;
        std::unique_ptr<Indie::APlayer> _mainPlayer;
    };
}


#endif //CPP_INDIE_STUDIO_ENTITYMANAGER_HH
