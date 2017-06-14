//
// Created by wurmel_a on 08/06/17.
//

#ifndef CPP_INDIE_STUDIO_ROOMLISTVIEWCONTROLLER_HH
#define CPP_INDIE_STUDIO_ROOMLISTVIEWCONTROLLER_HH

# include <vector>
# include <utility>
# include <functional>

# include "RootViewController.hh"
# include "../Models/Room.hh"
# include "BackgroundController/BackgroundMapController.hh"

namespace   Indie {
    class RoomListViewController : public AViewController, public BackgroundMapController {
    public:
        struct  ActionDelegate {
            std::string menuName;
            void (Indie::RoomListViewController::*fctPtr)();
            char    changeScreen;
            BackgroundMapController::AnimationType type;
        };
    public:
        RoomListViewController(RootViewController&);
        ~RoomListViewController();

    public:
        virtual void    initView();
        virtual ExitStatus   updateView();
        void    viewShouldDisapear();
        void    viewShouldReapear();


    private:
        void    disconnectUser();
        void    refreshButton();
        void    createNewRoom();
        void    showGlobalRanking();
        void    joinRoom();

    private:
        void    selectedRoom(MyGUI::ListBox *, size_t);
        void    selectedAction(MyGUI::ListBox *, size_t);

    private:
        void    setUpMenu(unsigned int, unsigned int);

    private:
        MyGUI::ListBox      *mRoomList;
        MyGUI::TextBox      *mTextBox;
        MyGUI::ListBox      *mMenuList;

    private:
        std::vector<Room>   _roomList;
        std::vector<ActionDelegate> _functionPtr;
//        std::vector<std::pair<std::string, void (Indie::RoomListViewController::*)()> > _functionPtr;
        int                 _indexSelected;
    };
}

#endif //CPP_INDIE_STUDIO_ROOMLISTVIEWCONTROLLER_HH
