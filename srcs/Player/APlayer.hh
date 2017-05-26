//
// Created by wurmel on 22/05/17.
//

#ifndef CPP_INDIE_STUDIO_APLAYER_HH
#define CPP_INDIE_STUDIO_APLAYER_HH

# include <vector>
# include <Ogre.h>
# include "../Entities/AEntity.hh"
# include "../Entities/Bomb.h"

namespace Indie
{
    class APlayer : public Indie::AEntity {
    public:
        enum PlayerType
        {
            HUMAN = 1,
            IA
        };
    public:
        APlayer(PlayerType const& pType, Ogre::Vector3 const&, Ogre::SceneManager *, const char *);
        ~APlayer();

    public:
        bool hittedByExplosion() const;
        bool    updateFromLoop(Ogre::SceneManager *);
        void    rotate(Direction const& dir);

    public:
        Ogre::Real const&   getMoveSpeed() const;
        void            setMoveSpeed(Ogre::Real const&);

        void            addABomb();
        void            plantABomb(Ogre::SceneManager *);

        void            godMode();
        bool            isGodMode() const;

    private:
        std::vector<std::unique_ptr<Indie::Bomb> >  _bombList;

    private:
        Ogre::Real      _moveSpeed;
        unsigned int    _nbBombs;
        bool            _godMode;

    private:
        PlayerType  _pType;
    };
}

#endif //CPP_INDIE_STUDIO_APLAYER_HH
