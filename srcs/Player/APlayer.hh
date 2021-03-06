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
    class APlayer : public Indie::AEntity, public Indie::ExplosableEntity {
    public:
        enum PlayerType
        {
            HUMAN = 1,
            IA
        };
    public:
        APlayer(PlayerType const& pType, Ogre::Vector3 const&, Ogre::SceneManager *, const char *, bool mainP = false);
        ~APlayer();

    public:
        bool hittedByExplosion() const;
        bool    updateFromLoop(Ogre::SceneManager *);
        void    explode(Ogre::SceneManager *);

        void    destroyEntity(Ogre::SceneManager *);

    public:
        Ogre::Real const&   getMoveSpeed() const;
        void            setMoveSpeed(Ogre::Real const&);

        unsigned int    getBombRange() const;
        void            setBombRange(unsigned int);

        void            addABomb();
        void            plantABomb(Ogre::SceneManager *);

        void            godMode();
        bool            isGodMode() const;

        std::string const&  getPlayerId() const;
        Ogre::Real        getRotation() const;

        void    setUpdate(bool const&);
        bool const&    isUpdate() const;

        unsigned int    getScore() const;
        void    setScore(unsigned int);

    private:
        std::vector<std::unique_ptr<Indie::Bomb> >  _bombList;

    private:
        Ogre::Real      _moveSpeed;
        unsigned int    _nbBombs;
        unsigned int    _bombRange;
        bool            _godMode;
        unsigned int    _score;

    private:
        PlayerType  _pType;
        unsigned int    _frameUpdate;
        unsigned int    _countFrame;
        bool            _updated;
        bool    _mainP;

    protected:
        std::string _pId;
    };
}

#endif //CPP_INDIE_STUDIO_APLAYER_HH
