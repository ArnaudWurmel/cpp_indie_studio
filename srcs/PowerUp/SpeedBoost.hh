//
// Created by wurmel_a on 11/06/17.
//

#ifndef CPP_INDIE_STUDIO_SPEEDBOOST_HH
#define CPP_INDIE_STUDIO_SPEEDBOOST_HH
# include "PowerUp.hh"

namespace Indie {
    class SpeedBoost : public PowerUp {
    public:
        SpeedBoost(Ogre::SceneManager *, Ogre::Vector3 const&, int);
        ~SpeedBoost();

    public:
        virtual void    boostPlayer(APlayer&, Ogre::SceneManager *);
    };
}

#endif //CPP_INDIE_STUDIO_SPEEDBOOST_HH
