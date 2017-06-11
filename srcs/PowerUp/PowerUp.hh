//
// Created by wurmel_a on 11/06/17.
//

#ifndef CPP_INDIE_STUDIO_POWERUP_HH
#define CPP_INDIE_STUDIO_POWERUP_HH

#include "../Player/APlayer.hh"

namespace   Indie {
    class PowerUp : public AEntity{
    public:
        PowerUp(Ogre::SceneManager *, std::string const&, Ogre::Vector3 const&, int);
        ~PowerUp();

    public:
        virtual bool    updateFromLoop(Ogre::SceneManager *);
        virtual bool    hittedByExplosion() const;

    public:
        virtual void    boostPlayer(APlayer&) const = 0;

    public:
        int getID() const;

    protected:
        int    _id;
    };
}


#endif //CPP_INDIE_STUDIO_POWERUP_HH
