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
        AEntity(Ogre::SceneManager *, Ogre::Vector3 const&, const char *);
        virtual ~AEntity();

    public:
        virtual bool hittedByExplosion() const = 0;

    public:
        virtual Ogre::Vector3 const&    getSize() const;
        virtual Ogre::Vector3 const&    getPosition() const;

    protected:
        Ogre::SceneNode *mSceneNode;
        Ogre::Entity    *mEntity;
    };
}

#endif //CPP_INDIE_STUDIO_AENTITY_HH