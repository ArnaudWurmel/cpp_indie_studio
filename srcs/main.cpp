//
// Created by wurmel on 13/05/17.
//

#include <iostream>
#include <ctime>
#include "GUI/RootViewController.hh"
#include "DataManager/DataManager.h"
#include "UserManager/User.hh"
#include "SoundManager/SoundManager.hh"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
	int main()
#endif
{
    Indie::SoundManager *soundManager = Indie::SoundManager::getSingloton();
    Indie::DataManager  *dataManager = Indie::DataManager::getSingloton("192.168.1.1", 4242);

    soundManager->loadSound("resources/sound/main.ogg");
    std::srand(std::time(0));
    Indie::RootViewController    *rootViewController = new Indie::RootViewController();
    try {
        if (!rootViewController->loadApp())
        {
            delete rootViewController;
            delete dataManager;
            delete soundManager;
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox(NULL, "Error", "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "Can't load app" << std::endl;
#endif
			return 1;
        }
        rootViewController->runApp();
        delete rootViewController;
        delete soundManager;
        delete dataManager;
        return 0;
    } catch (std::exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox(NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << e.what() << std::endl;
#endif
    }
    delete rootViewController;
    delete dataManager;
    delete soundManager;
    return 0;
}
