//
// Created by wurmel on 22/05/17.
//

#include "HumanPlayer.hh"

Indie::HumanPlayer::HumanPlayer(Ogre::Vector3 const &entityPos, Ogre::SceneManager *sceneManager) : APlayer(PlayerType::HUMAN, entityPos, sceneManager, "human.mesh")
{
    mSceneNode->setScale(Ogre::Vector3(50.0f, 53.459f, 50.0f));
    mTransformation = Ogre::Vector3(50.0f, 50.0f, 50.0f);
}

Indie::HumanPlayer::~HumanPlayer() {}