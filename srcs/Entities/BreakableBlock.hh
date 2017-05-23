//
// Created by wurmel on 22/05/17.
//

#ifndef CPP_INDIE_STUDIO_BREAKABLEBLOCK_HH
#define CPP_INDIE_STUDIO_BREAKABLEBLOCK_HH

# include <vector>
# include "../Particle/Particle.hh"
# include "AEntity.hh"

namespace Indie {

    class BreakableBlock : public Indie::AEntity {

    public:
        BreakableBlock(Ogre::SceneManager *, Ogre::Vector3 const&, AEntity::BlockType const& blockType = BlockType::NORMAL);
        ~BreakableBlock();

    public:
        bool hittedByExplosion() const;
        void    explode(Ogre::SceneManager *sceneManager);
        bool    updateFromLoop(Ogre::SceneManager *);

    private:
        std::vector<std::unique_ptr<Indie::Particle> >   _particleList;
        BlockType  _blockType;
    };
}

#endif //CPP_INDIE_STUDIO_BREAKABLEBLOCK_HH
