//
// Created by wurmel_a on 14/06/17.
//

#ifndef CPP_INDIE_STUDIO_BACKGROUNDIMAGECONTROLLER_HH
#define CPP_INDIE_STUDIO_BACKGROUNDIMAGECONTROLLER_HH

# include "../RootViewController.hh"

namespace   Indie {
    class BackgroundImageController {
    public:
        BackgroundImageController(RootViewController&);
        ~BackgroundImageController();

    public:
        void    hideBackground();
        void    showBackground();
        void    setBackgroundMaterialName(std::string const&);

    private:
        std::unique_ptr<Ogre::Rectangle2D>  mBackgroundRect;
    };
}

#endif //CPP_INDIE_STUDIO_BACKGROUNDIMAGECONTROLLER_HH
