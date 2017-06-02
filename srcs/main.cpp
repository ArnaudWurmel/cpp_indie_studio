//
// Created by wurmel on 13/05/17.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include "Bomberman/Bomberman.hh"
#include "DataManager/DataManager.h"

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
    Indie::DataManager  *dataManager = Indie::DataManager::getSingloton("137.74.196.119", 4242);

    std::srand(std::time(0));
    std::cout << dataManager->quitRoom("Erwan") << std::endl;
    if (!dataManager->joinRoom("Erwan", 0)) {
        std::cout << "Can't join room" << std::endl;
        return (1);
    }
    Indie::Bomberman    bomberman;
    try {
        if (!bomberman.loadApp())
        {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox(NULL, "Error", "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "Can't load app" << std::endl;
#endif
			return 1;
        }
        bomberman.runApp();
        dataManager->quitRoom("Erwan");
        return 0;
    } catch (std::exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox(NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << e.what() << std::endl;
#endif
    }
    dataManager->quitRoom("Erwan");
    return 0;
}