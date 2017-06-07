//
// Created by wurmel on 13/05/17.
//

#ifndef CPP_INDIE_STUDIO_BOMBERMAN_HH
#define CPP_INDIE_STUDIO_BOMBERMAN_HH

# include <MYGUI/MyGUI.h>
# include <memory>
# include <Ogre.h>
# include "../EventListener/EventListener.hh"
# include "../SceneDisplayer/SceneDisplayer.hh"
# include "../GUI/RootViewController.hh"

namespace Indie
{
    class Bomberman : public AViewController {
    public:
        Bomberman(RootViewController&);
        ~Bomberman();

    public:
        void initView();
        ExitStatus updateView();

    public:
        virtual bool    keyPressed(const OIS::KeyEvent&);
        virtual bool    mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);

    private:
        void    toggleMenu();

    private:
        std::unique_ptr<Indie::SceneDisplayer> mSceneDisplayer;

    private:
        bool    mToggleMenu;
        MyGUI::MenuControl  *_menuControl;
    };

}

#endif //CPP_INDIE_STUDIO_BOMBERMAN_HH
