//
// Created by wurmel_a on 09/06/17.
//

#ifndef CPP_INDIE_STUDIO_WAITINGROOMVIEWCONTROLLER_HH
#define CPP_INDIE_STUDIO_WAITINGROOMVIEWCONTROLLER_HH

# include <thread>
# include <mutex>
# include <MYGUI/MyGUI_ListBox.h>
# include <vector>
# include <utility>
# include "AViewController.hh"
# include "../Models/Room.hh"

namespace Indie {
    class WaitingRoomViewController : public Indie::AViewController {
    public:
        WaitingRoomViewController(RootViewController&);
        ~WaitingRoomViewController();

    public:
        virtual void    initView();
        virtual ExitStatus   updateView();
        virtual void    viewShouldDisapear();
        virtual void    viewShouldReapear();

    private:
        void    setUpMenu(unsigned int, unsigned int);
        void    selectedAction(MyGUI::ListBox *, size_t);

        /*
         * Menu's callback functions
         */
    private:
        void    returnToMenu();
        void    runGame();

    private:
        void    threadUpdate();

    private:
        std::unique_ptr<std::thread>    _threadUpdate;
        std::unique_ptr<std::mutex>     _lock;
        bool                            _continue;
        bool                            _gameRunning;

    private:
        MyGUI::ListBox      *mPlayerList;
        MyGUI::TextBox      *mTextBox;
        MyGUI::ListBox      *mMenuList;

    private:
        std::vector<std::string>    _playerList;
        std::vector<std::pair<std::string, void (Indie::WaitingRoomViewController::*)()> > _functionPtr;
    };

}

#endif //CPP_INDIE_STUDIO_WAITINGROOMVIEWCONTROLLER_HH
