//
// Created by wurmel on 13/05/17.
//

#include <iostream>
#include <exception>
#include "Bomberman/Bomberman.hh"

int main()
{
    Indie::Bomberman    bomberman;

    try {
        if (!bomberman.loadApp())
        {
            std::cerr << "Can't load app" << std::endl;
            return 1;
        }
        bomberman.runApp();
        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}