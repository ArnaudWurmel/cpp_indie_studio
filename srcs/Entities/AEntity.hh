//
// Created by wurmel on 21/05/17.
//

#ifndef CPP_INDIE_STUDIO_AENTITY_HH
#define CPP_INDIE_STUDIO_AENTITY_HH

#include <Ogre.h>

namespace Indie
{
    class   AEntity
    {
    public:
        enum BlockType
        {
            NORMAL,
            PARTICLE
        };
    public:
        enum Direction
        {
            UP = 0,
            DOWN,
            LEFT,
            RIGHT,
            UP_LEFT,
            UP_RIGHT,
            DOWN_LEFT,
            DOWN_RIGHT
        };
    public:
        AEntity(Ogre::SceneManager *, Ogre::Vector3 const&, const char *);
        virtual ~AEntity();

    public:
        virtual bool hittedByExplosion() const = 0;

    public:
        bool    isAlive() const;
        Ogre::Vector3 getSize() const;
        Ogre::Vector3 getPosition() const;
        void    setScale(Ogre::Vector3 const&);
        void    move(Ogre::Vector3 const&);
        bool    checkCollide(AEntity const&);
        virtual void    rotate(Direction const& dir);
        virtual void    explode(Ogre::SceneManager *);
        virtual bool    updateFromLoop(Ogre::SceneManager *);

    protected:
        Ogre::SceneNode *mSceneNode;
        Ogre::Entity    *mEntity;
        Ogre::Vector3   mTransformation;
        bool            mIsAlive;
    };
}

#endif //CPP_INDIE_STUDIO_AENTITY_HH
