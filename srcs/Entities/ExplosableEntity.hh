//
// Created by wurmel_a on 27/05/17.
//

#ifndef CPP_INDIE_STUDIO_EXPLOSABLEENTITY_HH
#define CPP_INDIE_STUDIO_EXPLOSABLEENTITY_HH

# include <vector>
# include <Ogre.h>
# include <memory>
# include "../Particle/Particle.hh"

namespace   Indie
{
    class ExplosableEntity {
    public:
        ExplosableEntity();
        ~ExplosableEntity();

    public:
        void    createAllParticles(Ogre::SceneManager *, Ogre::Vector3 const&);
        void    addParticlesColor(std::string const&);
        bool    updateParticles(Ogre::SceneManager *);

    private:
        std::string const&  getAMaterialName() const;

    private:
        std::vector<std::string>    _materialName;
        std::vector<std::unique_ptr<Indie::Particle> >  _particlesList;
    };
}

#endif //CPP_INDIE_STUDIO_EXPLOSABLEENTITY_HH
