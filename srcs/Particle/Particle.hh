//
// Created by wurmel on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_PARTICLE_HH
#define CPP_INDIE_STUDIO_PARTICLE_HH

# include <memory>
# include "../Entities/AEntity.hh"

namespace Indie {

    class Particle {
    public:
        Particle(Indie::AEntity *, std::string const&);
        ~Particle();

    public:
        bool    updateParticle();

    public:
        void    explode(Ogre::SceneManager *);
        void    removeEntity(Ogre::SceneManager *);

    private:
        std::unique_ptr<Indie::AEntity> mEntity;
        Ogre::Vector3   _dirVector;
        int t;
    };
}


#endif //CPP_INDIE_STUDIO_PARTICLE_HH
