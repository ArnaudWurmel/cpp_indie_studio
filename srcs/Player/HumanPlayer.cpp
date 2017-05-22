//
// Created by wurmel on 22/05/17.
//

#include "HumanPlayer.hh"

Indie::HumanPlayer::HumanPlayer(Ogre::Vector3 const &entityPos, Ogre::SceneManager *sceneManager) : APlayer(PlayerType::HUMAN, entityPos, sceneManager, "human.mesh")
{

}

Indie::HumanPlayer::~HumanPlayer() {}