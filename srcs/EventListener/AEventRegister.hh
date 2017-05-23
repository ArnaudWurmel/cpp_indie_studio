//
// Created by wurmel on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_AEVENTREGISTER_HH
#define CPP_INDIE_STUDIO_AEVENTREGISTER_HH

# include <OIS/OIS.h>

namespace Indie
{
    class AEventRegister {
    public:
        virtual ~AEventRegister() {}

        virtual void registerKeyboardEvent(OIS::Keyboard *) = 0;
        virtual void registerMouseEvent(OIS::Mouse *) = 0;
    };
}

#endif //CPP_INDIE_STUDIO_AEVENTREGISTER_HH
