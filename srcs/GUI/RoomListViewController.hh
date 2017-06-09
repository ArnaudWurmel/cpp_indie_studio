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

namespace   Indie {
    class RoomListViewController : public AViewController {
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
        std::vector<std::pair<std::string, void (Indie::RoomListViewController::*)()> > _functionPtr;
    };
}

#endif //CPP_INDIE_STUDIO_ROOMLISTVIEWCONTROLLER_HH
