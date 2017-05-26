//
// Created by wurmel on 24/05/17.
//

#ifndef CPP_INDIE_STUDIO_CONFIG_HH
#define CPP_INDIE_STUDIO_CONFIG_HH

# include <Ogre.h>

namespace Indie
{
    class Config {
    public:
        /*
         * Board infos
         */
        static Ogre::Real getGravity();

        /*
         * Player infos
         */
        static Ogre::Real getMoveSpeed();
        static unsigned int getInitialNbBomb();
        static unsigned int getExplodeTime();

    };
}

#endif //CPP_INDIE_STUDIO_CONFIG_HH
