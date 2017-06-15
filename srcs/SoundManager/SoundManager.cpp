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
}

void    Indie::SoundManager::loadSound(std::string const& fileName, bool loop) {
    sf::Music   *music = new sf::Music();

    if (!music->openFromFile(fileName))
        return ;
    music->setLoop(loop);
    music->play();
    _musicList.push_back(std::unique_ptr<sf::Music>(music));
    std::vector<std::unique_ptr<sf::Music> >::iterator  it = _musicList.begin();

    while (it != _musicList.end()) {
        if ((*it)->getStatus() == sf::SoundSource::Stopped || (*it)->getStatus() == sf::SoundStream::Paused)
            _musicList.erase(it);
        else
            ++it;
    }
}

Indie::SoundManager::~SoundManager() {
    std::vector<std::unique_ptr<sf::Music> >::iterator  it = _musicList.begin();

    while (it != _musicList.end()) {
        (*it)->stop();
        ++it;
    }
    _musicList.clear();
}