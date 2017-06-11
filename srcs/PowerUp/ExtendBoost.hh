//
// Created by wurmel_a on 11/06/17.
//

#ifndef CPP_INDIE_STUDIO_EXTENDBOOST_HH
#define CPP_INDIE_STUDIO_EXTENDBOOST_HH

# include "PowerUp.hh"

namespace   Indie {
    class ExtendBoost : public Indie::PowerUp {
    public:
        ExtendBoost(Ogre::SceneManager *, Ogre::Vector3 const&, int);
        ~ExtendBoost();

    public:
        virtual void    boostPlayer(APlayer&, Ogre::SceneManager *);

    };

}

#endif //CPP_INDIE_STUDIO_EXTENDBOOST_HH
