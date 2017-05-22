//
// Created by wurmel on 22/05/17.
//

#ifndef CPP_INDIE_STUDIO_BREAKABLEBLOCK_HH
#define CPP_INDIE_STUDIO_BREAKABLEBLOCK_HH

# include "AEntity.hh"

namespace Indie {

    class BreakableBlock : public Indie::AEntity {

    public:
        BreakableBlock(Ogre::SceneManager *, Ogre::Vector3 const&);
        ~BreakableBlock();

    public:
        bool hittedByExplosion() const;
    };
}

#endif //CPP_INDIE_STUDIO_BREAKABLEBLOCK_HH
