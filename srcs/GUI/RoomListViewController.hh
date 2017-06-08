//
// Created by wurmel_a on 08/06/17.
//

#ifndef CPP_INDIE_STUDIO_ROOMLISTVIEWCONTROLLER_HH
#define CPP_INDIE_STUDIO_ROOMLISTVIEWCONTROLLER_HH

# include "RootViewController.hh"

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
        void    disconnectUser(MyGUI::WidgetPtr);
        void    refreshButton(MyGUI::WidgetPtr);
        void    selectedRoom(MyGUI::ListBox *, size_t);

    private:
        MyGUI::ButtonPtr    mRefreshButton;
        MyGUI::ButtonPtr    mDisconnectButton;
        MyGUI::ListBox      *mListBox;
    };
}

#endif //CPP_INDIE_STUDIO_ROOMLISTVIEWCONTROLLER_HH
