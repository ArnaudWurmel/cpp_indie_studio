//
// Created by wurmel_a on 11/06/17.
//

#ifndef CPP_INDIE_STUDIO_GLOBALRANKINGVIEWCONTROLLER_HH
#define CPP_INDIE_STUDIO_GLOBALRANKINGVIEWCONTROLLER_HH

# include "AViewController.hh"
# include "RootViewController.hh"

namespace   Indie {
    class GlobalRankingViewController : public AViewController {
    public:
        GlobalRankingViewController(RootViewController&);
        ~GlobalRankingViewController();

    public:
        virtual void    initView();
        virtual ExitStatus   updateView();
        void    viewShouldDisapear();
        void    viewShouldReapear();

    private:
        MyGUI::TextBox      *mTextBox;
        MyGUI::MultiListBox  *mScoreboard;

    private:
        std::vector<std::pair<std::string, int> >   _data;
    };
}

#endif //CPP_INDIE_STUDIO_GLOBALRANKINGVIEWCONTROLLER_HH
