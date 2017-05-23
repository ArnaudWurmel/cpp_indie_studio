//
// Created by wurmel on 22/05/17.
//

#ifndef CPP_INDIE_STUDIO_APLAYER_HH
#define CPP_INDIE_STUDIO_APLAYER_HH

# include <Ogre.h>
# include "../Entities/AEntity.hh"

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
        virtual void    rotate(Direction const& dir);

    private:
        PlayerType  _pType;
    };
}

#endif //CPP_INDIE_STUDIO_APLAYER_HH
