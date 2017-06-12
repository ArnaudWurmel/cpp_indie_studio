//
// Created by wurmel_a on 12/06/17.
//

#ifndef CPP_INDIE_STUDIO_BOMBUP_HH
#define CPP_INDIE_STUDIO_BOMBUP_HH

#include "PowerUp.hh"

namespace   Indie {
    class BombUp : public PowerUp {
    public:
        BombUp(Ogre::SceneManager *, Ogre::Vector3 const&, int);
        ~BombUp();

    public:
        virtual void    boostPlayer(APlayer&, Ogre::SceneManager *);
    };
}

#endif //CPP_INDIE_STUDIO_BOMBUP_HH
