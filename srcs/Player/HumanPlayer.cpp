//
// Created by wurmel on 22/05/17.
//

#include "HumanPlayer.hh"

Indie::HumanPlayer::HumanPlayer(Ogre::Vector3 const &entityPos, Ogre::SceneManager *sceneManager,
                                std::string const& pId, bool mainP) : APlayer(PlayerType::HUMAN, entityPos, sceneManager, (mainP ? "Ally.mesh" : "Enemy.mesh"), mainP)
{
    setScale(Ogre::Vector3(50.0f, 53.459f, 50.0f));
    mTransformation = Ogre::Vector3(50.0f, 50.0f, 50.0f);
    addParticlesColor("Particles/Grey");
    if (mainP) {
        addParticlesColor("Particles/Blue");
    }
    else {
        addParticlesColor("Particles/Orange");
    }
    _pId = pId;
}

Indie::HumanPlayer::~HumanPlayer() {}