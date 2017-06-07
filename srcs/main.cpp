//
// Created by wurmel on 13/05/17.
//

#include <iostream>
#include <ctime>
#include "GUI/RootViewController.hh"
#include "DataManager/DataManager.h"
#include "UserManager/User.hh"

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
    Indie::DataManager  *dataManager = Indie::DataManager::getSingloton("127.0.0.1", 4242);

    std::srand(std::time(0));
   // std::cout << dataManager->quitRoom(Indie::User::getUser().getLogName()) << std::endl;
    Indie::RootViewController    rootViewController;
    try {
        if (!rootViewController.loadApp())
        {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox(NULL, "Error", "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "Can't load app" << std::endl;
#endif
			return 1;
        }
        rootViewController.runApp();
        dataManager->quitRoom(Indie::User::getUser()->getLogName());
        return 0;
    } catch (std::exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox(NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << e.what() << std::endl;
#endif
    }
    dataManager->quitRoom(Indie::User::getUser()->getLogName());
    return 0;
}