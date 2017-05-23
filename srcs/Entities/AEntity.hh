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
        Ogre::Vector3 getSize() const;
        Ogre::Vector3 getPosition() const;
        void    move(Ogre::Vector3 const&);
        virtual bool collide(AEntity const&) const;
        virtual void    rotate(Direction const& dir);


    protected:
        Ogre::SceneNode *mSceneNode;
        Ogre::Entity    *mEntity;
        Ogre::Vector3   mTransformation;
    };
}

#endif //CPP_INDIE_STUDIO_AENTITY_HH
