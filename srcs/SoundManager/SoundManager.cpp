//
// Created by wurmel_a on 09/06/17.
//

#include <iostream>
#include "SoundManager.hh"

Indie::SoundManager *Indie::SoundManager::getSingloton(bool reset) {
    static Indie::SoundManager  *inst = 0;

    if (reset) {
        delete inst;
        inst = 0;
    }
    else if (inst == 0) {
        inst = new Indie::SoundManager();
    }
    return inst;
}

Indie::SoundManager::SoundManager() {
    _currentMusic = NULL;
}

void    Indie::SoundManager::loadSound(std::string const& fileName) {
    if (_currentMusic) {
        _currentMusic->stop();
    }
    else
        _currentMusic = new sf::Music();
    if (!_currentMusic->openFromFile(fileName))
        return ;
    _currentMusic->setLoop(true);
    _currentMusic->play();
}

Indie::SoundManager::~SoundManager() {
    if (_currentMusic) {
        _currentMusic->stop();
        delete _currentMusic;
    }
}