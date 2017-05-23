//
// Created by wurmel on 13/05/17.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include "Bomberman/Bomberman.hh"

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
    Indie::Bomberman    bomberman;

    std::srand(std::time(0));
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
        return 0;
    } catch (std::exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBox(NULL, e.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << e.what() << std::endl;
#endif
    }
    return 0;
}