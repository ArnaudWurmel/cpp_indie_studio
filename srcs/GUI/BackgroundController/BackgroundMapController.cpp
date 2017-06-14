//
// Created by wurmel_a on 14/06/17.
//

#include <cmath>
#include "../../Player/HumanPlayer.hh"
#include "BackgroundMapController.hh"
#define PI 3.14159265

Indie::BackgroundMapController::BackgroundMapController(RootViewController& delegate) {
    generateBackground(delegate);
    _animationPtrFunctions.insert(std::make_pair(AnimationType::BREAK, &Indie::BackgroundMapController::animeBreak));
    _animationPtrFunctions.insert(std::make_pair(AnimationType::GO_THROUGHT, &Indie::BackgroundMapController::animeThrought));
    _animationPtrFunctions.insert(std::make_pair(AnimationType::NONE, &Indie::BackgroundMapController::animeNone));

}

void    Indie::BackgroundMapController::generateBackground(RootViewController &delegate) {
    _onAnimation = false;
    _type = AnimationType::NONE;
    _blockList.push_back(std::unique_ptr<AEntity>(new Indie::BreakableBlock(delegate.getSceneManager(), Ogre::Vector3(0, 50, 0))));
    _blockList.push_back(std::unique_ptr<AEntity>(new Indie::BreakableBlock(delegate.getSceneManager(), Ogre::Vector3(0, 50, 100))));
    _blockList.push_back(std::unique_ptr<AEntity>(new Indie::BreakableBlock(delegate.getSceneManager(), Ogre::Vector3(0, 50, -100))));
    _blockList.push_back(std::unique_ptr<AEntity>(new Indie::BreakableBlock(delegate.getSceneManager(), Ogre::Vector3(0, 150, 100))));
    _blockList.push_back(std::unique_ptr<AEntity>(new Indie::BreakableBlock(delegate.getSceneManager(), Ogre::Vector3(0, 150, -100))));
    _blockList.push_back(std::unique_ptr<AEntity>(new Indie::BreakableBlock(delegate.getSceneManager(), Ogre::Vector3(0, 250, 0))));
    _blockList.push_back(std::unique_ptr<AEntity>(new Indie::BreakableBlock(delegate.getSceneManager(), Ogre::Vector3(0, 250, 100))));
    _blockList.push_back(std::unique_ptr<AEntity>(new Indie::BreakableBlock(delegate.getSceneManager(), Ogre::Vector3(0, 250, -100))));
    _blockList.push_back(std::unique_ptr<AEntity>(new Indie::HumanPlayer(Ogre::Vector3(0, 130, 0), delegate.getSceneManager(), "HumanMenu", true)));
    _blockList.back()->rotate(AEntity::Direction::DOWN);
    _radius = 0;

}

void    Indie::BackgroundMapController::menuSelected(RootViewController& delegate, AnimationType const& animationType) {
    std::vector<std::unique_ptr<AEntity> >::iterator    it = _blockList.begin();

    _type = animationType;
    _onAnimation = true;
    if (animationType == AnimationType::BREAK) {
        while (it != _blockList.end()) {
            if ((*it)->isAlive())
                (*it)->explode(delegate.getSceneManager());
            ++it;
        }
    }
    else if (animationType == AnimationType::GO_THROUGHT) {
        Ogre::Camera *camera = delegate.getSceneManager()->getCamera("MainCam");

        if (camera) {
            camera->setPosition(Ogre::Vector3(-500, 150, 0));
            camera->lookAt(Ogre::Vector3(0, 150, 0));
        }
    }
}

bool Indie::BackgroundMapController::updateBackground(RootViewController& delegate) {
    Ogre::Camera *camera = delegate.getSceneManager()->getCamera("MainCam");

    if (!_onAnimation) {
        if (camera) {
            camera->setPosition(Ogre::Vector3(500 * std::cos(_radius * PI / 180.0), 150, 500 * std::sin(_radius * PI / 180.0)));
            camera->lookAt(Ogre::Vector3(0, 150, 0));
        }
        _radius = (_radius + 1) % 360;
        return true;
    }
    else {
        if (_animationPtrFunctions.find(_type) != _animationPtrFunctions.end()) {
            return (this->*(this->_animationPtrFunctions[_type]))(delegate);
        }
        return false;
    }
}

bool    Indie::BackgroundMapController::animeBreak(RootViewController &delegate) {
    Ogre::Camera *camera = delegate.getSceneManager()->getCamera("MainCam");
    std::vector<std::unique_ptr<AEntity> >::iterator    it = _blockList.begin();

    while (it != _blockList.end()) {
        if (!(*it)->updateFromLoop(delegate.getSceneManager()))
            _blockList.erase(it);
        else
            ++it;
    }
    if (camera) {
        camera->setPosition(Ogre::Vector3(500, 150, 0));
        camera->lookAt(Ogre::Vector3(0, 150, 0));
    }
    return _blockList.size() > 0;
}

bool    Indie::BackgroundMapController::animeNone(RootViewController& delegate) {
    static_cast<void>(delegate);
    return false;
}

bool    Indie::BackgroundMapController::animeThrought(RootViewController &delegate) {
    Ogre::Camera *camera = delegate.getSceneManager()->getCamera("MainCam");

    if (camera) {
        Ogre::Vector3   posCam = camera->getPositionForViewUpdate();

        if (posCam.x < 120) {
            posCam.x = posCam.x + 5;
            camera->setPosition(posCam);
            return true;
        }
    }
    return false;
}

void    Indie::BackgroundMapController::setHidden(bool hidden) {
    std::vector<std::unique_ptr<AEntity> >::iterator    it = _blockList.begin();

    while (it != _blockList.end()) {
        (*it)->setHidden(hidden);
        ++it;
    }
}

Indie::BackgroundMapController::~BackgroundMapController() {}