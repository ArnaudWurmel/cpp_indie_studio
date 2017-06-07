//
// Created by ballet_e on 6/7/17.
//

#include "AI.hh"

indie::AI::AI(Ogre::Vector3 const &entityPos, Ogre::SceneManager *sceneManager, std::string const &pId, bool mainP) : APlayer(PlayerType::IA, entityPos, sceneManager, "IA.mesh", mainP)
{
    setScale(Ogre::Vector3(50.0f, 53.459f, 50.0f));
    mTransformation = Ogre::Vector3(50.0f, 50.0f, 50.0f);
    addParticlesColor("Particles/Pink");
    addParticlesColor("Particles/Grey");
    _pId = pId;
}

Indie::HumanPlayer::~HumanPlayer() {}