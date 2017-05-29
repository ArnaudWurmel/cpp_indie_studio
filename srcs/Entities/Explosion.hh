//
// Created by wurmel_a on 26/05/17.
//

#ifndef CPP_INDIE_STUDIO_EXPLOSION_HH
#define CPP_INDIE_STUDIO_EXPLOSION_HH


# include "AEntity.hh"

namespace  Indie
{
    class Explosion : public Indie::AEntity {

    public:
        Explosion(Ogre::SceneManager *, Ogre::Vector3 const&);
        ~Explosion();

    public:
        bool hittedByExplosion() const;
        bool    updateFromLoop(Ogre::SceneManager *);

    private:
        unsigned int    _explosionTime;
    };
}

#endif //CPP_INDIE_STUDIO_EXPLOSION_HH
