//
// Created by wurmel_a on 11/06/17.
//

#ifndef CPP_INDIE_STUDIO_POWERUP_HH
#define CPP_INDIE_STUDIO_POWERUP_HH

#include "../Player/APlayer.hh"

namespace   Indie {
    class PowerUp : public AEntity, public ExplosableEntity {
    public:
        PowerUp(Ogre::SceneManager *, std::string const&, Ogre::Vector3 const&, int);
        ~PowerUp();

    public:
        virtual bool    updateFromLoop(Ogre::SceneManager *);
        virtual bool    hittedByExplosion() const;
        void    explode(Ogre::SceneManager *);
        virtual void    destroyEntity(Ogre::SceneManager *);

    public:
        bool    isTaken() const;
        void    setTaken(bool);

    public:
        virtual void    boostPlayer(APlayer&, Ogre::SceneManager *) = 0;

    public:
        int getID() const;

    protected:
        int    _id;

    private:
        size_t  _mTime;
        bool    _isTaken;
    };
}


#endif //CPP_INDIE_STUDIO_POWERUP_HH
