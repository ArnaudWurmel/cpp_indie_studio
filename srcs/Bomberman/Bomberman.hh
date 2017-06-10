//
// Created by wurmel on 13/05/17.
//

#ifndef CPP_INDIE_STUDIO_BOMBERMAN_HH
#define CPP_INDIE_STUDIO_BOMBERMAN_HH

# include <MYGUI/MyGUI.h>
# include <memory>
# include <vector>
# include <utility>
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
        void viewShouldDisapear();

    public:
        virtual bool    keyPressed(const OIS::KeyEvent&);
        virtual bool    mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
        virtual bool    keyReleased(const OIS::KeyEvent&);

    private:
        void    toggleMenu();
        void    createMenu();
        void    selectedAction(MyGUI::ListBox *_sender, size_t idx);

    private:
        void    exitGame();
        void    returnToMenu();

    private:
        std::unique_ptr<Indie::SceneDisplayer> mSceneDisplayer;

        /*
         * When escape key is pressed
         */
    private:
        bool    mToggleMenu;
        MyGUI::WindowPtr  _menuControl;
        MyGUI::ListBox  *_listBox;
        std::vector<std::pair<std::string, void (Indie::Bomberman::*)()> > _functionPtr;
    };

}

#endif //CPP_INDIE_STUDIO_BOMBERMAN_HH
