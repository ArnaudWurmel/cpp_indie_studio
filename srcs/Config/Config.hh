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
        static unsigned int getBombRange();
        static unsigned int getExplosionTime();
        static unsigned int getNbTicks();
        static std::string  getGameName();
    };
}

#endif //CPP_INDIE_STUDIO_CONFIG_HH
