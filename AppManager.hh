//
// Created by wurmel on 01/05/17.
//

#ifndef CPP_INDIE_STUDIO_APPMANAGER_HH
#define CPP_INDIE_STUDIO_APPMANAGER_HH

# include <memory>
# include <Ogre.h>

namespace IndieStudio
{
    class AppManager {

    public:
        AppManager();

        ~AppManager();

    public:
        bool loadApp();
        void execApp();

    private:
        void initResources();
        void createCamera();
        void createViewPort();

    private:
        std::unique_ptr<Ogre::Root> mRoot;
        Ogre::RenderWindow *mWindow;
        Ogre::SceneManager *mSceneMgr;
        Ogre::Camera *mCamera;
    };
}

#endif //CPP_INDIE_STUDIO_APPMANAGER_HH
