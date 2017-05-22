//
// Created by wurmel on 22/05/17.
//

#ifndef CPP_INDIE_STUDIO_ENTITYMANAGER_HH
#define CPP_INDIE_STUDIO_ENTITYMANAGER_HH

# include "AEntity.hh"
# include "../MapParser/MapParser.hh"
# include "Block.hh"

namespace Indie {
    class EntityManager {
    public:
        static AEntity  *createEntity(MapParser::TileType const&, Ogre::SceneManager *, Ogre::Vector3 const&);

    public:
        static AEntity    *createBlock(Ogre::SceneManager *, Ogre::Vector3 const&);
    };
}


#endif //CPP_INDIE_STUDIO_ENTITYMANAGER_HH
