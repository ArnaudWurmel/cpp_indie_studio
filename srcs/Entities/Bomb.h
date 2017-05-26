//
// Created by wurmel_a on 26/05/17.
//

#ifndef CPP_INDIE_STUDIO_BOMB_H
#define CPP_INDIE_STUDIO_BOMB_H

# include "AEntity.hh"
# include "../Config/Config.hh"

namespace Indie {
    class   APlayer;
    class Bomb : public AEntity {
    public:
        Bomb(Ogre::SceneManager *, APlayer const&);
        ~Bomb();

    public:
        bool    hittedByExplosion() const;
        bool    updateFromLoop(Ogre::SceneManager *);

    private:
        unsigned int    _explodeTime;
    };
}

#endif //CPP_INDIE_STUDIO_BOMB_H
