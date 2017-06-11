//
// Created by wurmel_a on 11/06/17.
//

#include "GlobalRankingViewController.hh"
#include "../Config/Config.hh"
#include "../DataManager/DataManager.h"

Indie::GlobalRankingViewController::GlobalRankingViewController(RootViewController& delegate) : AViewController(delegate) {
    _data = DataManager::getSingloton()->getGlobalRanking();
}

void    Indie::GlobalRankingViewController::initView() {
    unsigned int width;
    unsigned int height;
    unsigned int depth;
    int          left;
    int          top;

    _delegate.getGUI()->showPointer();
    _delegate.getRenderWindow()->getMetrics(width, height, depth, left, top);
    mTextBox = _delegate.getGUI()->createWidget<MyGUI::TextBox>("TextBox", 0, 50, width, 50, MyGUI::Align::Default, "Main");
    mTextBox->setFontName("TitleFont");
    mTextBox->setCaption(Indie::Config::getGameName());
    mTextBox->setTextAlign(MyGUI::Align::Center);
    mTextBox->setTextColour(MyGUI::Colour(1.0, 1.0, 1.0));
    mTextBox->setFontHeight(30);
    mScoreboard = _delegate.getGUI()->createWidget<MyGUI::MultiListBox>("MultiListBox", (width - (width / 2)) / 2, 100, width / 2, height - 100, MyGUI::Align::Default, "Main");
    mScoreboard->addColumn("Rank", mScoreboard->getWidth() / 10);
    mScoreboard->addColumn("Player Name", (mScoreboard->getWidth() - 2 * (mScoreboard->getWidth() / 10)));
    mScoreboard->addColumn("Score", (mScoreboard->getWidth() / 10));
    mScoreboard->setEnabled(true);

    std::vector<std::pair<std::string, int> >::iterator it = _data.begin();
    unsigned int i = 1;

    while (it != _data.end()) {
        mScoreboard->addItem("##" + std::to_string(i));
        mScoreboard->setSubItemNameAt(1, mScoreboard->getItemCount() - 1, (*it).first);
        mScoreboard->setSubItemNameAt(2, mScoreboard->getItemCount() - 1, std::to_string((*it).second));
        ++i;
        ++it;
    }
}

void    Indie::GlobalRankingViewController::viewShouldDisapear() {
    mTextBox->setVisible(false);
    mScoreboard->setVisible(false);
}

void    Indie::GlobalRankingViewController::viewShouldReapear() {
    mTextBox->setVisible(true);
    mScoreboard->setVisible(true);
    _delegate.getGUI()->showPointer();
}

Indie::AViewController::ExitStatus   Indie::GlobalRankingViewController::updateView() {
    return _state;
}

Indie::GlobalRankingViewController::~GlobalRankingViewController() {}