//
// Created by wurmel on 13/05/17.
//

#ifndef CPP_INDIE_STUDIO_SCENEMANAGER_HH
#define CPP_INDIE_STUDIO_SCENEMANAGER_HH

# include <Ogre.h>

namespace   Indie
{
    class SceneDisplayer {
    public:
        SceneDisplayer(Ogre::SceneManager *);
        ~SceneDisplayer();

    private:
        Ogre::SceneManager  *mSceneManager;
    };
}

#endif //CPP_INDIE_STUDIO_SCENEMANAGER_HH
