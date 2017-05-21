//
// Created by wurmel on 21/05/17.
//

#ifndef CPP_INDIE_STUDIO_BLOCK_HH
#define CPP_INDIE_STUDIO_BLOCK_HH

# include "AEntity.hh"

namespace  Indie
{
    class Block : public Indie::AEntity {

    public:
        Block(Ogre::SceneManager *, Ogre::Vector3 const&);
        ~Block();

    public:
        bool hittedByExplosion() const;
    };
}


#endif //CPP_INDIE_STUDIO_BLOCK_HH
