//
// Created by wurmel_a on 26/05/17.
//

#ifndef CPP_INDIE_STUDIO_BOMB_H
#define CPP_INDIE_STUDIO_BOMB_H

# include <vector>
# include <memory>
# include "AEntity.hh"
# include "../Config/Config.hh"
# include "Explosion.hh"

namespace Indie {
    class   APlayer;
    class Bomb : public AEntity {
    public:
        Bomb(Ogre::SceneManager *, APlayer const&);
        ~Bomb();

    public:
        static  Ogre::Vector3   getBombPosition(const APlayer&);

    public:
        bool    hittedByExplosion() const;
        bool    updateFromLoop(Ogre::SceneManager *);
        void    explode(Ogre::SceneManager *);

    private:
        bool    haveEntityWithPos(Ogre::Vector3 const&, bool&) const;

    private:
        unsigned int    _explodeTime;
        APlayer const&  _delegate;
        std::vector<std::unique_ptr<Indie::AEntity> >    _explosionList;
    };
}

#endif //CPP_INDIE_STUDIO_BOMB_H
