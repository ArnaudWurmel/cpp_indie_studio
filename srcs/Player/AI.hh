//
// Created by ballet_e on 6/7/17.
//

#ifndef CPP_INDIE_STUDIO_AI_HH
# define CPP_INDIE_STUDIO_AI_HH

# include <Ogre.h>
# include "APlayer.hh"
# include "../Entities/ExplosableEntity.hh"

namespace   indie
{
    class   AI : public Player
    {
    public:
        AI(Ogre::Vector3 const& entityPos, Ogre::SceneManager *sceneManager, std::string const& pId, bool mainP = false);
        ~AI();
    };
}

#endif //CPP_INDIE_STUDIO_AI_HH
