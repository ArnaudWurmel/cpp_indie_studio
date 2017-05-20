//
// Created by wurmel on 13/05/17.
//

#ifndef CPP_INDIE_STUDIO_BOMBERMAN_HH
#define CPP_INDIE_STUDIO_BOMBERMAN_HH

# include <memory>
# include <Ogre.h>
# include "../SceneDisplayer/SceneDisplayer.hh"

namespace Indie
{
    class Bomberman {
    public:
        Bomberman();
        ~Bomberman();

    public:
        bool loadApp();
        void runApp();

    private:
        void loadResources();
        void createCamera();

    private:
        std::unique_ptr<Ogre::Root> mRoot;
        Ogre::RenderWindow          *mRenderWindow;
        Ogre::SceneManager          *mSceneManager;
        Ogre::Camera                *mCamera;
    };

}

#endif //CPP_INDIE_STUDIO_BOMBERMAN_HH
