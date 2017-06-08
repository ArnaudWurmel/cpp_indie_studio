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
    };
}

#endif //CPP_INDIE_STUDIO_ROOMLISTVIEWCONTROLLER_HH
