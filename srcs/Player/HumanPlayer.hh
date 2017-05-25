//
// Created by wurmel on 22/05/17.
//

#ifndef CPP_INDIE_STUDIO_HUMANPLAYER_HH
#define CPP_INDIE_STUDIO_HUMANPLAYER_HH

# include <Ogre.h>
# include "APlayer.hh"

namespace Indie
{
    class HumanPlayer : public APlayer {
    public:
        HumanPlayer(Ogre::Vector3 const& entityPos, Ogre::SceneManager *sceneManager);
        ~HumanPlayer();
    };
}

#endif //CPP_INDIE_STUDIO_HUMANPLAYER_HH