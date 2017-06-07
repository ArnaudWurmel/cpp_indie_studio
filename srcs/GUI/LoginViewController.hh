//
// Created by wurmel_a on 06/06/17.
//

#ifndef CPP_INDIE_STUDIO_LOGINVIEWCONTROLLER_HH
#define CPP_INDIE_STUDIO_LOGINVIEWCONTROLLER_HH

# include <MYGUI/MyGUI.h>
# include <MYGUI/MyGUI_OgrePlatform.h>
# include "AViewController.hh"
# include "RootViewController.hh"

namespace   Indie {

    class LoginViewController : public Indie::AViewController {
    public:
        LoginViewController(Indie::RootViewController&);
        ~LoginViewController();

    public:
        void initView();
        ExitStatus updateView();

        void    viewShouldDisapear();
        void    viewShouldReapear();


    private:
        void    exitAsked(MyGUI::WidgetPtr);
        void    logMyUser(MyGUI::WidgetPtr);

    private:
        MyGUI::EditBox  *mLoginEditBox;
        MyGUI::EditBox  *mPasswdEditBox;
        MyGUI::TextBox  *mTextBox;
        MyGUI::ButtonPtr mQuitButton;
        MyGUI::ButtonPtr mConnectButton;
    };
}



#endif //CPP_INDIE_STUDIO_LOGINVIEWCONTROLLER_HH
