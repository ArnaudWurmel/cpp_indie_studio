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
# include "ExplosableEntity.hh"

namespace Indie {
    class   APlayer;
    class Bomb : public AEntity, public ExplosableEntity {
    public:
        Bomb(Ogre::SceneManager *, APlayer const&);
        Bomb(int, int, int, int);
        ~Bomb();

    public:
        static  Ogre::Vector3   getBombPosition(const APlayer&);

    public:
        bool    hittedByExplosion() const;
        bool    updateFromLoop(Ogre::SceneManager *);
        void    explode(Ogre::SceneManager *);

    public:
        int const&   getID() const;

    private:
        bool    haveEntityWithPos(Ogre::Vector3 const&, bool&) const;

    private:
        int             _id;
        unsigned int    _explodeTime;
        int    _explodeSize;
        std::vector<std::unique_ptr<Indie::AEntity> >    _explosionList;
    };
}

#endif //CPP_INDIE_STUDIO_BOMB_H
