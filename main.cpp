#include <iostream>
#include "AppManager.hh"

int main() {
    try {
        IndieStudio::AppManager appManager;

        if (!appManager.loadApp())
        {
            std::cerr << "Failed to load app" << std::endl;
            return 1;
        }
        appManager.execApp();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    std::cout << "Indie Studio shutting down." << std::endl;
    return 0;
}