//
// Created by wurmel_a on 14/06/17.
//

#ifndef CPP_INDIE_STUDIO_BACKGROUNDMAPCONTROLLER_HH
#define CPP_INDIE_STUDIO_BACKGROUNDMAPCONTROLLER_HH

# include <map>
# include <utility>
# include "../RootViewController.hh"
# include "../../Entities/Block.hh"
# include "../../Entities/BreakableBlock.hh"

namespace Indie {
    class BackgroundMapController {
    public:
        enum    AnimationType {
            BREAK = 0,
            GO_THROUGHT,
            NONE
        };
    public:
        BackgroundMapController(RootViewController&);
        ~BackgroundMapController();

    public:
        void    generateBackground(RootViewController&);
        bool    updateBackground(RootViewController&);
        void    menuSelected(RootViewController&, AnimationType const&);
        void    setHidden(bool);

    private:
        bool    animeBreak(RootViewController&);
        bool    animeThrought(RootViewController&);
        bool    animeNone(RootViewController&);

    private:
        unsigned int    _radius;
        std::vector<std::unique_ptr<AEntity> >  _blockList;

    private:
        bool    _onAnimation;
        AnimationType _type;

    private:
        std::map<AnimationType, bool (Indie::BackgroundMapController::*)(RootViewController&) > _animationPtrFunctions;
    };
}

#endif //CPP_INDIE_STUDIO_BACKGROUNDMAPCONTROLLER_HH
